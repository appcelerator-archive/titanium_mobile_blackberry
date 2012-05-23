/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DataModel>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>
#include "NativeListViewObject.h"
#include "TiCascadesEventHandler.h"
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

int NativeListViewObject::initialize(TiEventContainerFactory* containerFactory)
{
    listView_ = bb::cascades::ListView::create();
    eventClicked_ = containerFactory->createEventContainer();
    eventClicked_->setDataProperty("type", "click");
    eventHandler_ = new TiCascadesEventHandler(eventClicked_, this);
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
    std::multimap<QString, QString> dictionary;
    int error = NativeControlObject::getDictionaryData(obj, dictionary);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    QList<QString> dataList;
    for (std::multimap<QString, QString>::const_iterator iter = dictionary.begin(); iter != dictionary.end(); ++iter)
    {
        //TODO define const var, for title string
        if (iter->first == "title")
        {
            dataList.append(iter->second);
        }
    }
    listView_->setDataModel(new bb::cascades::QListDataModel<QString>(dataList));
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

void NativeListViewObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(listView_, SIGNAL(selectionChanged(QVariantList, bool)), eventHandler_, SLOT(selectionChanged(QVariantList, bool)));
}

QString NativeListViewObject::getListViewElementFromIndex(QVariantList var)
{
    bb::cascades::DataModel* dataM = listView_->dataModel();
    QVariant tmp = dataM->data(var);
    QString str = tmp.toString();
    return str;
}

int NativeListViewObject::setEventHandler(const char* eventName, TiEvent* event)
{
    //TODO define const var instead of using string value
    if (strcmp(eventName, "click") == 0)
    {
        eventClicked_->addListener(event);
    }
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::scrollToIndex(const char* index)
{
    QVariant variant(index);
    QVariantList scroll;
    scroll.append(variant);
    listView_->scrollToItem(scroll);
    return NATIVE_ERROR_OK;
}
