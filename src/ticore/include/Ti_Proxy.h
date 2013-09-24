/*
 * TiProxy.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIPROXY_H_
#define TI_TIPROXY_H_

#include <v8.h>
#include <QHash>
#include <QMap>
#include <QObject>
#include "Ti_Helper.h"
#include "Ti_Property.h"
#include "Ti_Event.h"
#include "Ti_EventParameters.h"
#include "Ti_Value.h"
#include <iostream>

/**
 * Helper macro to expose Proxy.
 * Place it in the public section of the class declaration
 * Example:
 * class MyProxy : public TiProxy
 * {
 * 	public:
 * 		CREATE_PROXY(MyProxy)
 * 		MyProxy(const char*)
 * 		virtual ~MyProxy()
 * }
 */

#define GENERATE_PROXY(NAME) \
		HandleScope scope; \
		NAME *proxy = new NAME(#NAME); \
		proxy->realJSObject = Persistent<Object>::New(proxy->jsObject->NewInstance()); \
		proxy->realJSObject->SetHiddenValue(String::New("proxy"), External::New(proxy)); \
		proxy->realJSObject.MakeWeak(proxy, _WeakCallback);

#define CREATE_PROXY(NAME) \
	static Handle<Value> CreateProxy(const Arguments &args) \
	{ \
		GENERATE_PROXY(NAME) \
		proxy->initStart(); \
 		if(args.Length() > 0 && args[0]->IsObject()) \
		{ \
 			proxy->initWithObject(args[0]->ToObject()); \
		} \
		proxy->jsObject.Dispose(); \
		proxy->initEnd(); \
		return scope.Close(proxy->realJSObject); \
	} \
	static NAME* CreateProxy() \
	{ \
		GENERATE_PROXY(NAME) \
		proxy->jsObject.Dispose(); \
		return proxy; \
	}
//#undef GENERATE_PROXY
/**
 * Creates a static version of this setter function, this is used with the TiProperty class
 * 		void someSetter(TiValue);
 * 		EXPOSE_SETTER(MyProxy, someSetter)
 *
 * The static version has an `_` at the begining!
 * 		addPropertySetter("someSetter", _someSetter);
 */
#define EXPOSE_SETTER(PROXY_CLASS, METHOD) \
	static void _##METHOD(TiProxy* proxy, Ti::TiValue value) \
	{ 	\
			PROXY_CLASS* mProxy = static_cast<PROXY_CLASS*>(proxy);	\
			mProxy->METHOD(value);	\
	}

/**
 * Creates a static version of this getter function, this is used with the TiProperty class
 * 		TiValue someGetter();
 * 		EXPOSE_GETTER(MyProxy, someGetter)
 *
 * The static version has an `_` at the begining!
 * 		addPropertyGetter("someGetter", _someGetter);
 */
#define EXPOSE_GETTER(PROXY_CLASS, METHOD) \
	static Ti::TiValue _##METHOD(Ti::TiProxy* proxy) \
	{ 	\
			PROXY_CLASS* mProxy = static_cast<PROXY_CLASS*>(proxy);	\
			return mProxy->METHOD();	\
	}

/**
 * Creates a static version of this method function, this is used with the TiProperty class
 * 		TiValue someMethod(TiValue);
 * 		EXPOSE_METHOD(MyPoxy, someMethod)
 *
 * The static version has an `_` at the begining!
 * 		addPropertyFunction("someMethod", _someMethod);
 */
#define EXPOSE_METHOD(PROXY_CLASS, METHOD) \
	static Ti::TiValue _##METHOD(Ti::TiProxy *proxy, Ti::TiValue args) \
	{ 	\
			PROXY_CLASS* mProxy = static_cast<PROXY_CLASS*>(proxy);	\
			return mProxy->METHOD(args);	\
	}

using namespace v8;

namespace Ti
{
class TiProxy;
}


typedef Ti::TiValue (*PROPERTY_FUNCTION)(Ti::TiProxy*, Ti::TiValue);
typedef Ti::TiValue (*PROPERTY_GETTER)(Ti::TiProxy*);
typedef void (*PROPERTY_SETTER)(Ti::TiProxy*, Ti::TiValue);

namespace Ti
{
class TiProxy
{
public:
	CREATE_PROXY(Ti::TiProxy)
	TiProxy(const char*);
	virtual ~TiProxy();

	virtual void initStart();
	virtual void initWithObject(Handle<Object>);
	virtual void initEnd();

	virtual Ti::TiValue addEventListener(Ti::TiValue);
	virtual Ti::TiValue removeEventListener(Ti::TiValue);
	virtual Ti::TiValue fireEvent(Ti::TiValue);
	virtual Ti::TiValue getToString(Ti::TiValue);

	virtual void onEventAdded(QString);
	virtual void fireEvent(QString, Ti::TiEventParameters);
	virtual void fireCallback(QString, Ti::TiEventParameters);

	virtual const char* getProxyName();
	virtual Handle<ObjectTemplate> getJSObject();

	virtual void makeWeak();
	virtual void clearWeak();

	QMap<QString, Ti::TiProperty*> properties;
	QMap<QString, QList<Ti::TiEvent*> > events;
	Persistent<Object> realJSObject;
	Persistent<ObjectTemplate> jsObject;

	EXPOSE_METHOD(Ti::TiProxy, addEventListener)
	EXPOSE_METHOD(Ti::TiProxy, removeEventListener)
	EXPOSE_METHOD(Ti::TiProxy, fireEvent)
	EXPOSE_METHOD(Ti::TiProxy, getToString)


protected:
	virtual void addFunction(const char* name, InvocationCallback);
	virtual void createPropertyFunction(QString name, PROPERTY_FUNCTION callback);
	virtual void createPropertySetter(QString name, PROPERTY_SETTER callback);
	virtual void createPropertyGetter(QString name, PROPERTY_GETTER callback);
	virtual void createPropertySetterGetter(QString name, PROPERTY_SETTER setter, PROPERTY_GETTER getter);

	static void _WeakCallback(Persistent<Value> object, void* parameter);
private:
	QString _proxyName;
	static Handle<Value> _Getter (Local<String> property, const AccessorInfo& info);
	static Handle<Value> _Setter (Local<String> property, Local<Value> value, const AccessorInfo& info);

};
}
#endif /* TIPROXY_H_ */
