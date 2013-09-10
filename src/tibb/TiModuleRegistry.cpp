/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiModuleRegistry.h"
#include "TitaniumRuntime.h"

static TiModuleRegistry* _instance = NULL;

TiModuleRegistry::TiModuleRegistry()
{
	HandleScope scope;
	_moduleObject = Persistent<Object>::New(Object::New());
}

TiModuleRegistry* TiModuleRegistry::Instance()
{
	if(_instance == NULL)
	{
		_instance = new TiModuleRegistry();
	}
	return _instance;
}

Handle<Value> TiModuleRegistry::GetModule(QString str)
{
	HandleScope scope;
	return scope.Close(Instance()->_moduleObject->Get(String::New(str.toLocal8Bit().constData())));
}

void TiModuleRegistry::RegisterModule(QString name, ModuleStartup mod)
{
	HandleScope scope;
    Context::Scope context_scope(TitaniumRuntime::getContenxt());
	Instance()->_moduleObject->ForceSet(String::New(name.toLocal8Bit().constData()), mod());
}
