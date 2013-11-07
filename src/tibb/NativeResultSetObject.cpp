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
    : NativeProxyObject(tiObject), effectedRows(0) {
}

NativeResultSetObject::~NativeResultSetObject() {
}

NATIVE_TYPE NativeResultSetObject::getObjectType() const {
    return N_TYPE_RESULTSET;
}

NativeResultSetObject* NativeResultSetObject::createResultSet(TiObject* tiObject) {
    return new NativeResultSetObject(tiObject);
}

// Properties boiler plate
#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeResultSetObject* resultSet, TiObject* obj, void * userContext) \
    {\
        return resultSet->NAME(obj, userContext);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeResultSetObject*, TiObject*, void*);

struct NATIVE_PROPSETGET_SETTING
{
	NATIVE_RESULTSET_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetResultSetProperties
{
public:
    SetGetResultSetProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_RESULTSET_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_RESULTSET_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_RESULTSET_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_RESULTSET_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetResultSetProperties()
    {
        if (setters_ != NULL)
        {
            delete[] setters_;
            setters_ = NULL;
        }
        if (getters_ != NULL)
        {
            delete[] getters_;
            getters_ = NULL;
        }
    }
    NATIVE_PROPSETGET_CALLBACK GetSetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_RESULTSET_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_RESULTSET_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    SetGetResultSetProperties(const SetGetResultSetProperties&);
    SetGetResultSetProperties& operator=(const SetGetResultSetProperties&);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

// Property set/get method must be before NATIVE_PROPSETGET_SETTING definition
PROP_SETGET(getRowCount)
int NativeResultSetObject::getRowCount(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(effectedRows));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getFieldCount)
int NativeResultSetObject::getFieldCount(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(columnNames.size()));
    return NATIVE_ERROR_OK;
}

const static NATIVE_PROPSETGET_SETTING g_ResultSetPropsSetGet[] =
{
		{N_RESULTSET_PROP_ROWCOUNT, NULL, PROP_SETGET_FUNCTION(getRowCount)},
		{N_RESULTSET_PROP_FIELDCOUNT, NULL, PROP_SETGET_FUNCTION(getFieldCount)}
};

static SetGetResultSetProperties g_ResultSetProps(g_ResultSetPropsSetGet, GET_ARRAY_SIZE(g_ResultSetPropsSetGet));

int NativeResultSetObject::setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_ResultSetProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

int NativeResultSetObject::getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_ResultSetProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}
// End properties boiler plate

bool NativeResultSetObject::isValidRow() {

    if (stepResult == SQLITE_ROW) {
    	return true;
    }

    return false;
}

int NativeResultSetObject::fieldIndexByName(string name) {
	for (int i = 0; i < columnNames.size(); i++) {
		if (columnNames[i] == name) {
			return i;
		}
	}

	return NAME_NOT_FOUND;
}

FIELD_TYPE NativeResultSetObject::fieldType(int index) {
	if (sqlite3_column_type(statement, index) == SQLITE_TEXT) {
		return STRING_FIELD;
	}
	else {
		return NUMERIC_FIELD;
	}
}

string NativeResultSetObject::fieldByName(string name /*, number type for cast*/) {
	for (int i = 0; i < columnNames.size(); i++) {
		if (columnNames[i] == name) {

			int columnType = sqlite3_column_type(statement, i);
		    switch (columnType) {
		        case SQLITE_TEXT:
		            return (const char*)sqlite3_column_text(statement, i);

		        case SQLITE_INTEGER:
		            return QString::number(sqlite3_column_int(statement, i)).toStdString();

		        case SQLITE_FLOAT:
		            return QString::number(sqlite3_column_double(statement, i)).toStdString();

		        case SQLITE_BLOB:
		        	// TODO: create a Ti Blob from this
		            return ""; //sqlite3_column_blob(statement, i)

		        case SQLITE_NULL:
		            return ""; //
		    }
		}
	}

	return "";
}

string NativeResultSetObject::field(int index /*, number type for cast*/) {
	if (index <= sqlite3_column_count(statement) && strlen((const char*)sqlite3_column_text(statement, index)) > 0) {
		return (const char*)sqlite3_column_text(statement, index);
	}

	return "";
}

string NativeResultSetObject::fieldName(int index) {
	if (index <= sqlite3_column_count(statement) && strlen((const char*)sqlite3_column_text(statement, index)) > 0) {
		return (const char*)sqlite3_column_name(statement, index);
	}
	return "";
}

bool NativeResultSetObject::next() {
    stepResult = sqlite3_step(statement);
    if (stepResult == SQLITE_ROW) {
    	return true;
    }

   return false;
}

void NativeResultSetObject::close() {
	if(columnNames.size())
		sqlite3_finalize(statement);
}

#pragma GCC diagnostic warning "-Wdeprecated-declarations"


