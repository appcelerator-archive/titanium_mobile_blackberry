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
}

TiResultSetObject::TiResultSetObject(NativeObjectFactory* objectFactory)
    : TiProxy("ResultSet") {
    objectFactory_ = objectFactory;
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isValidRow", this, _isValidRow);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fieldByName", this, _fieldByName);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "field", this, _field);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "next", this, _next);
}

Handle<Value> TiResultSetObject::_isValidRow(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	bool isVaildRow = nativeResultSet->isValidRow();

    return handleScope.Close(Boolean::New(isVaildRow));
}

Handle<Value> TiResultSetObject::_fieldByName(void* userContext, TiObject*, const Arguments& args) {
    return Undefined();
}

Handle<Value> TiResultSetObject::_field(void* userContext, TiObject*, const Arguments& args) {

	HandleScope handleScope;
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	int index  = Handle<Integer>::Cast(args[0])->Value();
	string value = nativeResultSet->field(index);

    return handleScope.Close(String::New(value.c_str()));

    return Undefined();
}

Handle<Value> TiResultSetObject::_next(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	bool isVaildRow = nativeResultSet->next();

	return handleScope.Close(Boolean::New(isVaildRow));
}


