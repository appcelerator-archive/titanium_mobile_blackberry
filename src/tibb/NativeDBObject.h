/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEDBOBJECT_H_
#define NATIVEDBOBJECT_H_

#include "NativeProxyObject.h"
//#include <QtCore/QObject>
#include "TiConstants.h"
#include "TiV8Event.h"
#include "TiDBObject.h"
#include "TiResultSetObject.h"

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

class NativeBufferObject;
class TiObject;

using namespace Ti::Database::DB;


/*
 * NativeDBObject
 *
 * NativeDBObject methods
 */
class NativeDBObject : public NativeProxyObject
{
public:
    static NativeDBObject* createDB(TiObject* tiObject);
    int getObjectType() const;

    // DB methods
    int execute(TiResultSetObject* resultSet, string command, vector<string> bindings);
    int close();

protected:
    virtual ~NativeDBObject();

private:
    explicit NativeDBObject(TiObject* tiObject);
    NativeDBObject(const NativeDBObject&);
    NativeDBObject& operator=(const NativeDBObject&);

    friend class TiDBObject;
    int _open(string name);

    sqlite3* _db;
};


#endif /* NATIVEDBOBJECT_H_ */
