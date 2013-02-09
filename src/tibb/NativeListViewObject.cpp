/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewObject.h"

#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/VisualNode>

#include "NativeListItemObject.h"
#include "NativeListViewObject.h"
#include "PersistentV8Value.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "TiProxy.h"
#include "TiUITableViewRow.h"

using namespace bb::cascades;

NativeListViewObject::NativeListViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
{
    listView_ = NULL;
}

NativeListViewObject::~NativeListViewObject()
{
}

NativeListViewObject* NativeListViewObject::createListView(TiObject* tiObject)
{
    return new NativeListViewObject(tiObject);
}

int NativeListViewObject::initialize()
{
    listView_ = bb::cascades::ListView::create();
    setControl(listView_);
    listView_->setDataModel(new ArrayDataModel());
    listView_->setListItemProvider(new ListViewItemFactory());
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::setData(TiObject* obj)
{
    HandleScope scope;

    Handle<Value> value = obj->getValue();
    if (!value->IsArray()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    ArrayDataModel* model = static_cast<ArrayDataModel*>(listView_->dataModel());

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
        if (native->getObjectType() != N_TYPE_LIST_ITEM) {
            // Only allow row objects as table data.
            return NATIVE_ERROR_INVALID_ARG;
        }

        NativeListItemObject* listItem = static_cast<NativeListItemObject*>(native);
        model->append(listItem->data());
    }

    return NATIVE_ERROR_OK;
}

int NativeListViewObject::getObjectType() const
{
    return N_TYPE_LIST_VIEW;
}

NAHANDLE NativeListViewObject::getNativeHandle() const
{
    return listView_;
}

QVariant NativeListViewObject::getListViewElementFromIndex(QVariantList var)
{
    bb::cascades::DataModel* dataM = listView_->dataModel();
    QVariant property = dataM->data(var);
    return property;
}

int NativeListViewObject::scrollToIndex(int index)
{
    QVariant variant(index);
    QVariantList scroll;
    scroll.append(variant);
    listView_->scrollToItem(scroll);
    return NATIVE_ERROR_OK;
}

void NativeListViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClicked = containerFactory->createEventContainer();
    eventClicked->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClicked, new ListViewEventHandler(eventClicked, this)));
    QObject::connect(listView_, SIGNAL(triggered(QVariantList)), events_[tetCLICK]->handler(), SLOT(triggered(QVariantList)));
}

/*********** ListViewItemFactory class *************/
bb::cascades::VisualNode* ListViewItemFactory::createItem(bb::cascades::ListView*, const QString&)
{
    bb::cascades::StandardListItem* item = new bb::cascades::StandardListItem();
    return item;
}

void ListViewItemFactory::updateItem(bb::cascades::ListView*, bb::cascades::VisualNode* listItem, const QString&,
                                     const QVariantList&, const QVariant& data)
{
    StandardListItem* standardItem = static_cast<StandardListItem*>(listItem);
    QVariantMap map = data.value<QVariantMap>();
    standardItem->setTitle(map["title"].toString());
}

/*********** ListViewEventHandler class *************/
void ListViewEventHandler::triggered(QVariantList var)
{
    eventContainer_->setDataProperty("index", var[0].toInt());
    Persistent<Value> propValue;
    if (owner_)
    {
        QVariant property = owner_->getListViewElementFromIndex(var);
        if (property.canConvert<PersistentV8Value>())
        {
            PersistentV8Value v8Value = property.value<PersistentV8Value>();
            propValue = v8Value.getValue();
        }
    }
    eventContainer_->setV8ValueProperty("rowData", propValue);
    eventContainer_->fireEvent();
}
