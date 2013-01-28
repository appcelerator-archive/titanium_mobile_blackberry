/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDBObject.h"

#include "NativeException.h"
#include "NativeMessageStrings.h"
#include "TiObject.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

NativeDBObject::NativeDBObject(TiObject* tiObject)
    : NativeProxyObject(tiObject) {
}

NativeDBObject::~NativeDBObject() {
}

int NativeDBObject::getObjectType() const {
    return N_TYPE_DB;
}

NativeDBObject* NativeDBObject::createDB(TiObject* tiObject) {
    return new NativeDBObject(tiObject);
}

int NativeDBObject::_open(string name) {
	int rc;
    string dbFile = "app/native/" + name;

	rc = sqlite3_open_v2(dbFile.c_str(), &_db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
		sqlite3_close(_db);
		return(1);
	}

	return NATIVE_ERROR_OK;
}

int NativeDBObject::execute(string command) {
	int rc;
	char *zErrMsg = 0;

	rc = sqlite3_exec(_db, command.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
	}

	return NATIVE_ERROR_OK;
}

int NativeDBObject::close() {

    sqlite3_close(_db);

	return NATIVE_ERROR_OK;
}

#pragma GCC diagnostic warning "-Wdeprecated-declarations"


