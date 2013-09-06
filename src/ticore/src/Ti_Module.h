/*
 * TiModule.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIMODULE_H_
#define TI_TIMODULE_H_

#include <v8.h>
#include "Ti_Proxy.h"

using namespace v8;

#define CREATE_MODULE(NAME) \
	static Handle<Object> CreateModule() \
	{ \
		HandleScope scope; \
		NAME *module = new NAME(#NAME); \
		module->initStart(); \
		module->initEnd(); \
		Handle<Object> _jsObject = module->getJSObject()->NewInstance(); \
		_jsObject->SetHiddenValue(String::New("module"), External::New(module)); \
		return scope.Close(_jsObject); \
	}

#define GET_MODULE_FROM_CALLBACK(NAME, ARGS) \
		Local<Value> _a = ARGS.Holder()->GetHiddenValue(String::New("module")); \
		Handle<External> _b = Handle<External>::Cast(_a); \
		NAME* proxy = static_cast<TiUIWindowProxy*>(_b->Value());


namespace Ti
{
class TiModule : public Ti::TiProxy {
public:
	TiModule(const char*);
	CREATE_MODULE(Ti::TiModule)
	virtual ~TiModule();
	virtual void initStart();
	virtual void initEnd();
protected:
	virtual void addModule(const char* name, Handle<Object> obj);
	virtual void addNumber(QString name, double value);
	virtual void addString(QString, QString);

};
}
#endif /* TIMODULE_H_ */
