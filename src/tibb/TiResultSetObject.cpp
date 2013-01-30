/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiResultSetObject.h"

#include "NativeResultSetObject.h"
#include "TiResultSetObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "NativeException.h"
#include "TiMessageStrings.h"


TiResultSetObject::TiResultSetObject()
    : TiProxy("ResultSet") {
    objectFactory_ = NULL;
    effectedRows = 0;
}

TiResultSetObject::TiResultSetObject(NativeObjectFactory* objectFactory)
    : TiProxy("ResultSet") {
    objectFactory_ = objectFactory;
    effectedRows = 0;
}

TiResultSetObject::~TiResultSetObject() {
}

void TiResultSetObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory) {
}

TiResultSetObject* TiResultSetObject::createResultSet(NativeObjectFactory* objectFactory) {
	TiResultSetObject* obj = new TiResultSetObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiResultSetObject::initializeTiObject(TiObject* parentContext) {
    if (!isInitialized()) {
        TiProxy::initializeTiObject(parentContext);
        NativeResultSetObject* obj = (NativeResultSetObject*)getNativeObjectFactory()->createNativeObject(N_TYPE_RESULTSET, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiResultSetObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fieldByName", this, _fieldByName);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "rowCount", this, _rowCount);
}

Handle<Value> TiResultSetObject::_rowCount(void* userContext, TiObject*, const Arguments& args)
{
	//HandleScope handleScope;
    if (args.Length() < 1) {
     //   return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    //return handleScope.Close(result);

    return Undefined();
}

Handle<Value> TiResultSetObject::_fieldByName(void* userContext, TiObject*, const Arguments& args)
{
	HandleScope handleScope;
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    //return handleScope.Close(result);

    return Undefined();
}



