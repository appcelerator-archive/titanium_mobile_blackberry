/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiDatabase.h"
#include "TiDBObject.h"
#include "TiResultSetObject.h"
#include "V8Utils.h"
#include <QFile>
#include <QDir>
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "install", this, _install);
}

Handle<Value> TiDatabase::_install(void* userContext, TiObject* obj, const Arguments& args)
{
	if(args.Length() == 0) return Undefined();
	if(!args[0]->IsString()) return Undefined();
	QString realName = titanium::V8StringToQString(args[0]->ToString());
	QString givenName;
	if(args.Length() > 0 && args[1]->IsString())
	{
		givenName =  titanium::V8StringToQString(args[1]->ToString());
	}
	else
	{
		givenName =  titanium::V8StringToQString(args[0]->ToString());
	}

	QString dataFolder = "data";
	QString newFileName = dataFolder + "/" + givenName;
	QFile newFile(newFileName);

	if (!newFile.exists())
	{
		QString appFolder(QDir::homePath());
		appFolder.chop(4);

		QString originalFileName = appFolder + "app/native/assets/" + realName;
		QFile originalFile(originalFileName);

		if (originalFile.exists()) {
			originalFile.copy(newFileName);
		} else {
			return Undefined();
		}
	}

	return TiDatabase::_open(userContext, obj, args);
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

