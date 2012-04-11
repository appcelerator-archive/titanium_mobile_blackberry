/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCascadesApp.h"
#include "NativeObjectFactory.h"
#include "NativeContainerObject.h"
#include "NativeLabelObject.h"
#include <bb/cascades/Container>

using namespace bb::cascades;

NativeObjectFactory::NativeObjectFactory(TiCascadesApp* cascadesApp)
{
    cascadesApp_ = cascadesApp;
    NativeContainerObject* root = new NativeContainerObject(cascadesApp->appContainer_);
    rootContainer_ = root;
}

NativeObjectFactory::~NativeObjectFactory()
{
    if (rootContainer_ != NULL)
    {
        rootContainer_->release();
        rootContainer_ = NULL;
    }
}

NativeObject* NativeObjectFactory::createNativeObject(int type)
{
    NativeObject* obj = NULL;
    switch (type)
    {
    case NO_TYPE_CONTAINER:
    case NO_TYPE_WINDOW:
        obj = NativeContainerObject::createContainer(rootContainer_);
        break;
    case NO_TYPE_LABEL:
        obj = new NativeLabelObject;
        break;
    }
    if (obj != NULL)
    {
        obj->initialize();
    }
    return obj;
}

NativeObject* NativeObjectFactory::getRootContainer() const
{
    rootContainer_->addRef();
    return rootContainer_;
}
