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

    bool isValidRow();
    string fieldByName(string name /*, number type for cast*/);
    string field(int index /*, number type for cast*/);
    bool next();

    int effectedRows;
    sqlite3_stmt* statement;
    int  stepResult;

protected:
    virtual ~NativeResultSetObject();

private:
    explicit NativeResultSetObject(TiObject* tiObject);
    NativeResultSetObject(const NativeResultSetObject&);
    NativeResultSetObject& operator=(const NativeResultSetObject&);
};


#endif /* NATIVERESULTSETOBJECT_H_ */
