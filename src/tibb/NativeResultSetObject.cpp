/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeResultSetObject.h"

#include "NativeException.h"
#include "NativeMessageStrings.h"
#include "TiObject.h"
#include "TiLogger.h"


#define N_SQLITE_ERROR 1

#pragma GCC diagnostic ignored "-Wunused-parameter"

NativeResultSetObject::NativeResultSetObject(TiObject* tiObject)
    : NativeProxyObject(tiObject) {
}

NativeResultSetObject::~NativeResultSetObject() {
}

int NativeResultSetObject::getObjectType() const {
    return N_TYPE_RESULTSET;
}

NativeResultSetObject* NativeResultSetObject::createResultSet(TiObject* tiObject) {
    return new NativeResultSetObject(tiObject);
}

int NativeResultSetObject::fieldByName() {


	return NATIVE_ERROR_OK;
}

#pragma GCC diagnostic warning "-Wdeprecated-declarations"


