/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLabelObject.h"
#include <bb/cascades/TextAlignment>
#include <bb/cascades/Color>
#include <qtgui/QColor>

NativeLabelObject::NativeLabelObject()
{
    label_ = NULL;
}

NativeLabelObject::~NativeLabelObject()
{
}

NativeLabelObject* NativeLabelObject::createLabel()
{
    return new NativeLabelObject;
}

int NativeLabelObject::getObjectType() const
{
    return N_TYPE_LABEL;
}

int NativeLabelObject::initialize(TiEventContainerFactory*)
{
    label_ = bb::cascades::Label::create();
    setTextControl(label_);
    // TODO: Set label layout here
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeLabelObject::getNativeHandle() const
{
    return label_;
}
