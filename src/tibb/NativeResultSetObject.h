/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVERESULTSETOBJECT_H_
#define NATIVERESULTSETOBJECT_H_

#include "NativeProxyObject.h"
#include "TiConstants.h"
#include "TiV8Event.h"

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

class NativeBufferObject;
class TiObject;

using namespace Ti::Database::ResultSet;

enum FIELD_TYPE
{
    STRING_FIELD
    , NUMERIC_FIELD
    // ToDo Support Blob
};

enum NATIVE_RESULTSET_PROP
{
    N_RESULTSET_PROP_UNDEFINED
    , N_RESULTSET_PROP_ROWCOUNT
    , N_RESULTSET_PROP_FIELDCOUNT
    /* This MUST be the last element */
    , N_RESULTSET_PROP_LAST
};

#define NAME_NOT_FOUND -1

/*
 * NativeResultSetObject
 *
 * NativeResultSetObject methods
 */
class NativeResultSetObject : public NativeProxyObject
{
public:
    static NativeResultSetObject* createResultSet(TiObject* tiObject);
    int getObjectType() const;

    int setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);
    int getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);


    //int setPort(TiObject* obj, void* userContext);
    int getRowCount(TiObject* obj, void* userContext);
    int getFieldCount(TiObject* obj, void* userContext);

    bool isValidRow();
    int fieldIndexByName(string name /*, number type for cast*/);
    FIELD_TYPE fieldType(int index);
    string fieldByName(string name /*, number type for cast*/);
    string field(int index /*, number type for cast*/);
    bool next();
    void close();

    int effectedRows;
    sqlite3_stmt* statement;
    int  stepResult;
    vector<string> columnNames;

protected:
    virtual ~NativeResultSetObject();

private:
    explicit NativeResultSetObject(TiObject* tiObject);
    NativeResultSetObject(const NativeResultSetObject&);
    NativeResultSetObject& operator=(const NativeResultSetObject&);
};


#endif /* NATIVERESULTSETOBJECT_H_ */
