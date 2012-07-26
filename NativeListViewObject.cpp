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
#include "TiEventContainerFactory.h"

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

int NativeListViewObject::setWidth(TiObject* obj)
{
    float width;
    int error = NativeControlObject::getFloat(obj, &width);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    listView_->setMaxWidth(width);
    listView_->setMinWidth(width);
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::setLeft(TiObject* obj)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    float left;
    int error = NativeControlObject::getFloat(obj, &left);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    left_ = left;
    pProp->setPositionX(left_);
    pProp->setPositionY(top_);
    listView_->setLayoutProperties(pProp);
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::setTop(TiObject* obj)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    float top;
    int error = NativeControlObject::getFloat(obj, &top);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    top_ = top;
    pProp->setPositionX(left_);
    pProp->setPositionY(top_);
    listView_->setLayoutProperties(pProp);
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
