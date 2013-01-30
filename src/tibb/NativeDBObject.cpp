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
#include "TiLogger.h"

#define N_FILEPATH "app/native/"
#define N_SQLITE_ERROR 1

#pragma GCC diagnostic ignored "-Wunused-parameter"

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
	int error;
    string dbFile = N_FILEPATH + name;

	error = sqlite3_open_v2(dbFile.c_str(), &_db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	if (error) {
		TiLogger::getInstance().log(sqlite3_errmsg(_db));
		sqlite3_close(_db);
		return error;
	}

	return NATIVE_ERROR_OK;
}

int NativeDBObject::execute(TiResultSetObject* resultSet, string command, vector<string> bindings) {
	int error;
	sqlite3_stmt* statement;
	int stepResult;

	error = sqlite3_prepare_v2(_db, command.c_str(), strlen(command.c_str()) + 1, &statement, NULL);
	if(error) {
		TiLogger::getInstance().log(sqlite3_errmsg(_db));
		sqlite3_finalize(statement);
		sqlite3_close(_db);
		return error;
	}

	for (int i = 0; i < bindings.size(); i++) {
		error = sqlite3_bind_text(statement, i + 1, bindings[i].c_str(), strlen(bindings[i].c_str()), 0);
		if(error) {
			TiLogger::getInstance().log(sqlite3_errmsg(_db));
			sqlite3_finalize(statement);
			sqlite3_close(_db);
			return error;
		}
	}

	stepResult = sqlite3_step(statement);

	if (stepResult == SQLITE_DONE) {
		sqlite3_finalize(statement);
		return NATIVE_ERROR_OK;
	}

	int effectedRows = 0;
	while (true) {
		if (stepResult == SQLITE_ROW) {
			effectedRows++;
		}
		else if (stepResult == SQLITE_DONE) {
			break;
		}
		else {
			sqlite3_finalize(statement);
			TiLogger::getInstance().log("While stepping through statement, an error has occurred");
			return  N_SQLITE_ERROR;
		}
		stepResult = sqlite3_step(statement);
	}

	resultSet->effectedRows = effectedRows;

	return NATIVE_ERROR_OK;
}

int NativeDBObject::close() {

    sqlite3_close(_db);

	return NATIVE_ERROR_OK;
}

#pragma GCC diagnostic warning "-Wdeprecated-declarations"


