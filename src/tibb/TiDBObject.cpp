/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiDBObject.h"

#include "NativeDBObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "NativeException.h"
#include "TiMessageStrings.h"

TiDBObject::TiDBObject()
    : TiProxy("DB") {
    objectFactory_ = NULL;
}

TiDBObject::TiDBObject(NativeObjectFactory* objectFactory)
    : TiProxy("DB") {
    objectFactory_ = objectFactory;
}

TiDBObject::~TiDBObject() {
}

void TiDBObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory) {
}

TiDBObject* TiDBObject::createDB(NativeObjectFactory* objectFactory, const Arguments& args) {
	TiDBObject* obj = new TiDBObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL,args);
    return obj;
}

void TiDBObject::initializeTiObject(TiObject* parentContext, const Arguments& args ) {
    if (!isInitialized()) {
        TiProxy::initializeTiObject(parentContext);
        NativeDBObject* obj = (NativeDBObject*)getNativeObjectFactory()->createNativeObject(N_TYPE_DB, this);
        obj->_open(TiObject::getSTDStringFromValue(args[0]));
        setNativeObject(obj);
        obj->release();
    }
}

void TiDBObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "execute", this, _execute);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
}

Handle<Value> TiDBObject::_execute(void* userContext, TiObject*, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiDBObject* obj = (TiDBObject*) userContext;
    NativeDBObject* ndb = (NativeDBObject*) obj->getNativeObject();

    try {
    	// create and pass in the result set object fill it in if callback
        ndb->execute(TiObject::getSTDStringFromValue(args[0]));
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }

    // like socket create tcp returning the tcp object return the result set object
    return Undefined();
}

Handle<Value> TiDBObject::_close(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiDBObject* obj = (TiDBObject*) userContext;
    NativeDBObject* ndb = (NativeDBObject*) obj->getNativeObject();

    try {
        ndb->close();
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}


