/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDropDownObject.h"

#include <bb/cascades/DropDown>
#include <QVector>

#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

NativeDropDownObject::NativeDropDownObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_DROPDOWN)
{
    dropdown_ = NULL;
}

NativeDropDownObject::~NativeDropDownObject()
{
}

NativeDropDownObject* NativeDropDownObject::createDropDown(TiObject* tiObject)
{
    return new NativeDropDownObject(tiObject);
}

NATIVE_TYPE NativeDropDownObject::getObjectType() const
{
    return N_TYPE_DROPDOWN;
}

int NativeDropDownObject::initialize()
{
    dropdown_ = bb::cascades::DropDown::create();
    setControl(dropdown_);
    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setTitle(TiObject* obj)
{
    QString title = V8ValueToQString(obj->getValue());
    dropdown_->setTitle(title);
    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setOptions(TiObject* obj)
{
    QVector<QString> options;
    int error = NativeControlObject::getStringArray(obj, options);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    for (int i = 0; i < options.size(); ++i)
    {
        dropdown_->add(bb::cascades::Option::create().text(options[i]));
    }

    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setSelectedIndex(TiObject* obj)
{
    int value = 0;
    int error = NativeControlObject::getInteger(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    dropdown_->setSelectedIndex(value);
    return NATIVE_ERROR_OK;
}

void NativeDropDownObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new DropDownEventHandler(eventClick)));
    QObject::connect(dropdown_, SIGNAL(selectedIndexChanged(int selectedIndex)), events_[tetCLICK]->handler(), SLOT(selectedIndexChanged(int selectedIndex)));
}
