/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeOptionObject.h"
#include "TiEventContainerFactory.h"
#include "TiCascadesEventHandler.h"
#include <bb/cascades/Option>

NativeOptionObject::NativeOptionObject()
{
    option_ = NULL;
}

NativeOptionObject::~NativeOptionObject()
{
}

NativeOptionObject* NativeOptionObject::createOption()
{
    return new NativeOptionObject();
}

int NativeOptionObject::getObjectType() const
{
    return N_TYPE_OPTION;
}

int NativeOptionObject::initialize(TiEventContainerFactory* containerFactory)
{
    option_ = bb::cascades::Option::create();
    return NATIVE_ERROR_OK;
}

int NativeOptionObject::setText(const char* text)
{
    QString str = text;
    option_->setText(str);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeOptionObject::getNativeHandle() const
{
    return option_;
}
