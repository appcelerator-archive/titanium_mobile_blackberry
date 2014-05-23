/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMODULEREGISTRY_H_
#define TIMODULEREGISTRY_H_

#include <v8.h>
#include <QObject>
using namespace v8;

typedef Handle<Object> (*ModuleStartup)();

class TiModuleRegistry {
public:
	static void RegisterModule(QString, ModuleStartup);
	static Handle<Value> GetModule(QString);
private:
	TiModuleRegistry();
	static TiModuleRegistry* Instance();
	Persistent<Object> _moduleObject;
};

#endif /* TIMODULEREGISTRY_H_ */
