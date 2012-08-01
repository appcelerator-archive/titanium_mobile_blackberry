/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewObject.h"

#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DataModel>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/ListItemManager>
#include <bb/cascades/VisualNode>
#include "NativeListViewObject.h"
#include "PersistentV8Value.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"

NativeListViewObject::NativeListViewObject()
{
    listView_ = NULL;
    top_ = 0;
    left_ = 0;
}

NativeListViewObject::~NativeListViewObject()
{
}

NativeListViewObject* NativeListViewObject::createListView()
{
    return new NativeListViewObject;
}

int NativeListViewObject::initialize()
{
    listView_ = bb::cascades::ListView::create();
    setControl(listView_);
    listView_->setListItemManager(new ListViewItemFactory());
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::setData(TiObject* obj)
{
    QVector<QVariant> dataModel;
    int error = NativeControlObject::getDataModel(obj, dataModel);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    QList<QVariant> dataList;
    for (int i = 0; i < dataModel.size(); ++i)
    {
        dataList.append(dataModel[i]);
    }
    listView_->setDataModel(new bb::cascades::QListDataModel<QVariant>(dataList));
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
    QObject::connect(listView_, SIGNAL(selectionChanged(QVariantList, bool)), events_[tetCLICK]->handler, SLOT(selectionChanged(QVariantList, bool)));
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
    // Trying to parse the title from v8 object
    if (data.canConvert<PersistentV8Value>())
    {
        PersistentV8Value v8Value = data.value<PersistentV8Value>();
        Persistent<Value> propValue = v8Value.getValue();
        if (propValue->IsObject())
        {
            Local<Value> titleValue = propValue->ToObject()->Get(String::New("title"));
            Local<String> valueStr = titleValue->ToString();
            String::Utf8Value valueUTF(valueStr);
            ((bb::cascades::StandardListItem*)listItem)->setTitle(*valueUTF);
        }
    }
}

/*********** ListViewEventHandler class *************/
void ListViewEventHandler::selectionChanged(QVariantList var, bool)
{
    eventContainer_->setDataProperty("index", var[0].toString().toStdString().c_str());
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
