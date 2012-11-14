/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiNetwork.h"

#include "TiSocketObject.h"
#include "TiHTTPClientObject.h"
#include "TiGenericFunctionObject.h"

TiNetwork::TiNetwork()
    : TiProxy("Network")
{
    objectFactory_ = NULL;
}

TiNetwork::TiNetwork(NativeObjectFactory* objectFactory)
    : TiProxy("Network")
{
    objectFactory_ = objectFactory;
}

TiNetwork::~TiNetwork()
{
}

void TiNetwork::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiNetwork* obj = new TiNetwork(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiNetwork::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiSocketObject::addObjectToParent(this, objectFactory_);
    TiHTTPClientObject::addObjectToParent(this, objectFactory_);
    // TODO: Add class methods, constants, properties
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createHTTPClient", this, _createHTTPClient);

}

Handle<Value> TiNetwork::_createHTTPClient(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiNetwork* obj = (TiNetwork*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiHTTPClientObject* newHTTP = TiHTTPClientObject::createHTTPClient(obj->objectFactory_);
    newHTTP->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newHTTP->setParametersFromObject(newHTTP, settingsObj);
    }
    setTiObjectToJsObject(result, newHTTP);
    return handleScope.Close(result);
}

