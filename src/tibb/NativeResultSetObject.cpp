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

	effectedRows = 0;
}

NativeResultSetObject::~NativeResultSetObject() {
}

int NativeResultSetObject::getObjectType() const {
    return N_TYPE_RESULTSET;
}

NativeResultSetObject* NativeResultSetObject::createResultSet(TiObject* tiObject) {
    return new NativeResultSetObject(tiObject);
}

bool NativeResultSetObject::isValidRow() {

    if (stepResult == SQLITE_ROW) {
    	return true;
    }

    return false;
}

string NativeResultSetObject::fieldByName(string name /*, number type for cast*/) {
	return "";
}

string NativeResultSetObject::field(int index /*, number type for cast*/) {
	string value = (const char*)sqlite3_column_text(statement, index);
	return value;
}

bool NativeResultSetObject::next() {
    stepResult = sqlite3_step(statement);
    if (stepResult == SQLITE_ROW) {
    	return true;
    }

   return false;
}

#pragma GCC diagnostic warning "-Wdeprecated-declarations"


