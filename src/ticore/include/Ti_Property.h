/*
 * TiProperty.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIPROPERTY_H_
#define TI_TIPROPERTY_H_

#include <v8.h>
#include <QString>

namespace Ti
{
class TiProxy;
class TiValue;
}

using namespace v8;

typedef void (*PROPERTY_SETTER)(Ti::TiProxy*, Ti::TiValue);
typedef Ti::TiValue (*PROPERTY_GETTER)(Ti::TiProxy*);
typedef Ti::TiValue (*PROPERTY_FUNCTION)(Ti::TiProxy*, Ti::TiValue);


namespace Ti
{
class TiProperty
{
public:
	virtual ~TiProperty();
	TiProperty(QString _name);
	static void createFunction(Ti::TiProxy* _proxy, QString _name, PROPERTY_FUNCTION _callback);
	static void createSetter(Ti::TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback);
	static void createGetter(Ti::TiProxy* _proxy, QString _name, PROPERTY_GETTER _getterCallback);
	static void createProperty(Ti::TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback,  PROPERTY_GETTER _getterCallback);

	static Handle<Value> onInvoke(const Arguments& args);
	Handle<Value> getValue();
	Handle<Value> setValue(Handle<Value>);

	QString name;
	PROPERTY_FUNCTION callback;
	PROPERTY_SETTER setterCallback;
	PROPERTY_GETTER getterCallback;
	Persistent<Function> value;
	Ti::TiProxy* proxy;
	bool isFunction;
};
}
#endif /* TIPROPERTY_H_ */
