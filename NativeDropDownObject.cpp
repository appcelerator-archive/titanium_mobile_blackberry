/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDropDownObject.h"
#include "NativeOptionObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/DropDown>
#include <qt4/QtCore/qvector.h>

NativeDropDownObject::NativeDropDownObject()
{
    dropdown_ = NULL;
}

NativeDropDownObject::~NativeDropDownObject()
{
}

NativeDropDownObject* NativeDropDownObject::createDropDown()
{
    return new NativeDropDownObject();
}

int NativeDropDownObject::getObjectType() const
{
    return N_TYPE_DROPDOWN;
}

int NativeDropDownObject::initialize(TiEventContainerFactory* containerFactory)
{
    dropdown_ = bb::cascades::DropDown::create();
    setControl(dropdown_);
    eventClick_ = containerFactory->createEventContainer();
    eventHandler_ = new DropDownEventHandler(eventClick_);
    QObject::connect(dropdown_, SIGNAL(selectedIndexChanged(int selectedIndex)), eventHandler_, SLOT(selectedIndexChanged(int selectedIndex)));
    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setTitle(TiObject* obj)
{
    QString title;
    int error = NativeControlObject::getString(obj, title);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
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
        NativeOptionObject* option = NativeOptionObject::createOption();
        option->initialize(NULL);
        option->setText(options[i].toStdString().c_str());
        dropdown_->add((bb::cascades::Option*)option->getNativeHandle());
        option->release();
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

int NativeDropDownObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "click") == 0)
    {
        eventClick_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeDropDownObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
}
