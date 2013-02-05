/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiDBObject.h"

#include "NativeDBObject.h"
#include "NativeResultSetObject.h"
#include "TiResultSetObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "NativeException.h"
#include "TiMessageStrings.h"
#include <vector>


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
	TiDBObject* obj = new TiDBObject(objectFactory);
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

    // create ResultSet object
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiResultSetObject* newResultSet = TiResultSetObject::createResultSet(obj->objectFactory_);
    newResultSet->setValue(result);
    NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) newResultSet->getNativeObject();

    vector<string> bindings;
    if (args.Length() > 1) {
		if (args[1]->IsArray()) {
			Handle<Array> array = Handle<Array>::Cast(args[1]);
			for (int i = 0; i < array->Length(); i++) {
				Handle<Value> element = array->Get(i);
				bindings.push_back(TiObject::getSTDStringFromValue(element));
			}
		}
		else {
			for (int i = 1; i < args.Length(); i++) {
				bindings.push_back(TiObject::getSTDStringFromValue(args[i]));
			}
		}
    }


    try {

      ndb->execute(nativeResultSet, TiObject::getSTDStringFromValue(args[0]), bindings);
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }


    if (nativeResultSet->effectedRows > 0) {
    	setTiObjectToJsObject(result, newResultSet);
    	return handleScope.Close(result);
    }

    return Undefined();
}

Handle<Value> TiDBObject::_close(void* userContext, TiObject*, const Arguments& args)
{
    TiDBObject* obj = (TiDBObject*) userContext;
    NativeDBObject* ndb = (NativeDBObject*) obj->getNativeObject();

    try {
        ndb->close();
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}


