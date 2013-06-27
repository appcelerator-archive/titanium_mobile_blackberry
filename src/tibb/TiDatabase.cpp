/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiDatabase.h"
#include "TiDBObject.h"
#include "TiResultSetObject.h"

#include "TiGenericFunctionObject.h"

TiDatabase::TiDatabase()
    : TiProxy("Database")
{
    objectFactory_ = NULL;
}

TiDatabase::TiDatabase(NativeObjectFactory* objectFactory)
    : TiProxy("Database")
{
    objectFactory_ = objectFactory;
}

TiDatabase::~TiDatabase()
{
}

void TiDatabase::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiDatabase* obj = new TiDatabase(objectFactory);
    parent->addMember(obj);
    obj->setAttachedObject(parent);
    obj->release();
}

void TiDatabase::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiDBObject::addObjectToParent(this, objectFactory_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
}


Handle<Value> TiDatabase::_open(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiDatabase* obj = (TiDatabase*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();

    TiDBObject* newDB = TiDBObject::createDB(obj->objectFactory_, args);
    newDB->setValue(result);

    setTiObjectToJsObject(result, newDB);

    return handleScope.Close(result);
}

