/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTableViewObject.h"

#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/ListView>
#include "V8Utils.h"
#include "NativeTableViewRowObject.h"
#include "NativeTableViewObject.h"
#include "TableView/BasicTableViewRow.h"
#include "TableView/CustomTableViewRow.h"
#include "TableView/TableViewRowData.h"
#include "TableView/HeaderTableViewRow.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "TiProxy.h"
#include "TiUITableViewRow.h"
#include "TiUITableViewSection.h"
#include <bb/cascades/SnapMode>
#include <bb/cascades/GroupDataModel>

using namespace bb::cascades;
using namespace titanium;

NativeTableViewObject::NativeTableViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_TABLE_VIEW)
{
    tableView_ = NULL;
}

NativeTableViewObject::~NativeTableViewObject()
{
}

NativeTableViewObject* NativeTableViewObject::createTableView(TiObject* tiObject)
{
    return new NativeTableViewObject(tiObject);
}

int NativeTableViewObject::initialize()
{
    tableView_ = bb::cascades::ListView::create();
    setControl(tableView_);
    tableView_->setDataModel(new ArrayDataModel());
    tableView_->setSnapMode(bb::cascades::SnapMode::LeadingEdge);
    TableViewRowFactory* factory = new TableViewRowFactory(this);
    tableView_->setListItemProvider(factory);
    tableView_->setListItemTypeMapper(factory);

    return NATIVE_ERROR_OK;
}

TiObject* NativeTableViewObject::createRowObject(Local<Object> item)
{
    // Convert the dictionary object into a row object.
    NativeObjectFactory* factory = tiObject_->getNativeObjectFactory();
    TiUITableViewRow* row = TiUITableViewRow::createTableViewRow(factory);

    // Create a JavaScript proxy for the new row object.
    Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(tiObject_->getValue());
    Local<Object> proxy = templ->NewInstance();
    row->setValue(proxy);
    TiObject::setTiObjectToJsObject(proxy, row);

    // Apply the properties in the dictionary to the new row object.
    row->setParametersFromObject(row, item);

    return static_cast<TiObject*>(row);
}

int NativeTableViewObject::setData(TiObject* obj)
{
    HandleScope scope;

    Handle<Value> value = obj->getValue();
    if (!value->IsArray()) {
        return NATIVE_ERROR_INVALID_ARG;
    }



    ArrayDataModel* model = static_cast<ArrayDataModel*>(tableView_->dataModel());
    QVariantList allRows;
    Handle<Array> data = Handle<Array>::Cast(value);
    Handle<Array> newData;
    Handle<Array> sections = Array::New();
    for(uint32_t i = 0, len = data->Length(); i < len; i++)
    {
        TiObject* sectionObject = TiObject::getTiObjectFromJsObject(data->Get(i));
        if(sectionObject)
        {
        	TiUITableViewSection *sect = static_cast<TiUITableViewSection*>(sectionObject);
        	if(sect == NULL) continue;
        	Handle<Array> rowsInSection = sect->getRowsInSection();
    		int index = sections->Length();
        	for(int ii = 0, llen = rowsInSection->Length(); ii < llen; ii++) {
        		sections->Set(index, rowsInSection->Get(ii));
        		index++;
        	}
        }
    }

    if(sections->Length() > 0)
    {
    	newData = Handle<Array>::Cast(sections);
    }
    else
    {
    	newData = Handle<Array>::Cast(data);
    }
    int x = 0;
    for (uint32_t i = 0, len = newData->Length(); i < len; i++)
    {
        Local<Object> item = newData->Get(i)->ToObject();
        if (!item->IsObject()) {
            // Silently ignore any invalid data items.
            continue;
        }

        TiObject* itemObject = TiObject::getTiObjectFromJsObject(item);
        if (!itemObject)
        {
    		if(item->Has(String::New("header")) || item->Has(String::New("isHeader")))
        	{
        		TiObject* h = createRowObject(item);
        		// TODO: Pedro: something else for sections
        		newData->Set(x, h->getValue());
                NativeTableViewRowObject* listItem = static_cast<NativeTableViewRowObject*>(h->getNativeObject());
                allRows.append(listItem->data());
                item->Delete(String::New("header"));
                item->Delete(String::New("isHeader"));
        	}
    		if(!item->Has(String::New("title")))
    		{
    			continue;
    		}
			itemObject = createRowObject(item);
			// Replace the dictionary object in the data array with the row object.
			// This allows developers to later update properties on the row.
			// TODO: something else for sections
			newData->Set(x, itemObject->getValue());
        }

        NativeObject* native = itemObject->getNativeObject();
        if (native->getObjectType() != N_TYPE_TABLE_VIEW_ROW) {
            // Only allow row objects as table data.
            return NATIVE_ERROR_INVALID_ARG;
        }

        NativeTableViewRowObject* listItem = static_cast<NativeTableViewRowObject*>(native);
        TiObject o;
        o.setValue(String::New(""));
        listItem->setHeader(&o);
        allRows.append(listItem->data());
        x++;
    }
    model->clear();
    model->append(allRows);
    qDebug() << "all rows: " << allRows << "\n";
    return NATIVE_ERROR_OK;
}

NATIVE_TYPE NativeTableViewObject::getObjectType() const
{
    return N_TYPE_TABLE_VIEW;
}

NAHANDLE NativeTableViewObject::getNativeHandle() const
{
    return tableView_;
}

QVariant NativeTableViewObject::getTableViewElementFromIndex(QVariantList var)
{
    bb::cascades::DataModel* dataM = tableView_->dataModel();
    QVariant property = dataM->data(var);
    return property;
}

int NativeTableViewObject::scrollToIndex(int index)
{
    QVariant variant(index);
    QVariantList scroll;
    scroll.append(variant);
    tableView_->scrollToItem(scroll);
    return NATIVE_ERROR_OK;
}

void NativeTableViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClicked = containerFactory->createEventContainer();
    eventClicked->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClicked, new TableViewEventHandler(eventClicked, this)));
    QObject::connect(tableView_, SIGNAL(triggered(QVariantList)), events_[tetCLICK]->handler(), SLOT(triggered(QVariantList)));
}

/*********** TableViewRowFactory class *************/
bb::cascades::VisualNode* TableViewRowFactory::createItem(bb::cascades::ListView*, const QString& type)
{
    if (type == "custom") {
        return new CustomTableViewRow(tableView_->layout());
    } else if(type == "header") {
    	return new HeaderTableViewRow();
    }
    return new BasicTableViewRow();
}

void TableViewRowFactory::updateItem(bb::cascades::ListView*, bb::cascades::VisualNode* listItem, const QString&,
                                     const QVariantList&, const QVariant& data)
{
    Q_ASSERT(data.canConvert<QObject*>());
    AbstractTableViewRow* item = static_cast<AbstractTableViewRow*>(listItem);
    item->setData(data.value<QObject*>());
}

QString TableViewRowFactory::itemType(const QVariant &data, const QVariantList &indexPath)
{
    Q_ASSERT(data.canConvert<QObject*>());
    return data.value<QObject*>()->property("dataType").toString();
}

/*********** TableViewEventHandler class *************/
void TableViewEventHandler::triggered(QVariantList var)
{
    int index = var[0].toInt();
    QVariant data = owner_->getTableViewElementFromIndex(var);
    TableViewRowData* itemData = static_cast<TableViewRowData*>(data.value<QObject*>());
    Handle<Value> row = itemData->row()->getValue();

    eventContainer_->setDataProperty("index", index);
    eventContainer_->setV8ValueProperty("rowData", row);
    eventContainer_->setV8ValueProperty("row", row);
    eventContainer_->fireEvent();
}
