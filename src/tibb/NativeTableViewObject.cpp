/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTableViewObject.h"

#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/ListView>

#include "NativeTableViewRowObject.h"
#include "NativeTableViewObject.h"
#include "TableView/BasicTableViewRow.h"
#include "TableView/CustomTableViewRow.h"
#include "TableView/TableViewRowData.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "TiProxy.h"
#include "TiUITableViewRow.h"

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

    TableViewRowFactory* factory = new TableViewRowFactory(this);
    tableView_->setListItemProvider(factory);
    tableView_->setListItemTypeMapper(factory);

    return NATIVE_ERROR_OK;
}

int NativeTableViewObject::setData(TiObject* obj)
{
    HandleScope scope;

    Handle<Value> value = obj->getValue();
    if (!value->IsArray()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    ArrayDataModel* model = static_cast<ArrayDataModel*>(tableView_->dataModel());

    Handle<Array> data = Handle<Array>::Cast(value);
    uint32_t length = data->Length();
    for (uint32_t i = 0; i < length; i++) {
        Local<Value> item = data->Get(i);
        if (!item->IsObject()) {
            // Silently ignore any invalid data items.
            continue;
        }

        TiObject* itemObject = TiObject::getTiObjectFromJsObject(item);
        if (!itemObject) {
            // Convert the dictionary object into a row object.
            NativeObjectFactory* factory = tiObject_->getNativeObjectFactory();
            TiUITableViewRow* row = TiUITableViewRow::createTableViewRow(factory);
            itemObject = static_cast<TiObject*>(row);

            // Create a JavaScript proxy for the new row object.
            Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(tiObject_->getValue());
            Local<Object> proxy = templ->NewInstance();
            row->setValue(proxy);
            TiObject::setTiObjectToJsObject(proxy, row);

            // Apply the properties in the dictionary to the new row object.
            row->setParametersFromObject(row, item->ToObject());

            // Replace the dictionary object in the data array with the row object.
            // This allows developers to later update properties on the row.
            data->Set(i, itemObject->getValue());
        }

        NativeObject* native = itemObject->getNativeObject();
        if (native->getObjectType() != N_TYPE_TABLE_VIEW_ROW) {
            // Only allow row objects as table data.
            return NATIVE_ERROR_INVALID_ARG;
        }

        NativeTableViewRowObject* listItem = static_cast<NativeTableViewRowObject*>(native);
        model->append(listItem->data());
    }

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

QString TableViewRowFactory::itemType(const QVariant &data, const QVariantList &indexPat)
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
