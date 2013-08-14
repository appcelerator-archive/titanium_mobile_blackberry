/*
 * TiProperty.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: penrique
 */

#include "Ti_Property.h"
#include "Ti_Proxy.h"
#include "Ti_Helper.h"
#include "Ti_Value.h"

Ti::TiProperty::TiProperty(QString _name) :
	name(_name),
	callback(NULL),
	setterCallback(NULL),
	getterCallback(NULL),
	proxy(NULL),
	isFunction(false)
{
	Local<FunctionTemplate> func = FunctionTemplate::New(TiProperty::onInvoke,  External::Wrap(this));
	value = Persistent<Function>::New(func->GetFunction());
}

Ti::TiProperty::~TiProperty()
{
//	TiHelper::Log(QString("Destroying property ").append(name));
	value.Clear();
	value.Dispose();
}


void Ti::TiProperty::createSetter(TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback)
{
	Ti::TiProperty *prop;
	if(_proxy->properties.contains(_name))
	{
		prop = _proxy->properties[_name];
	}
	else
	{
		prop = new TiProperty(_name);
		prop->proxy = _proxy;
		prop->proxy->properties[_name] = prop;
	}
	prop->isFunction = false;
	prop->setterCallback = _setterCallback;

	if(_name.startsWith("set")) {
		prop->isFunction = true;
		return;
	}

	QString setter = QString(_name);
	setter[0] = setter[0].toUpper();
	setter.prepend("set");

	Ti::TiProperty::createSetter(_proxy, setter, _setterCallback);

}

void Ti::TiProperty::createGetter(TiProxy* _proxy, QString _name, PROPERTY_GETTER _getterCallback)
{
	Ti::TiProperty *prop;
	if(_proxy->properties.contains(_name))
	{
		prop = _proxy->properties[_name];
	}
	else
	{
		prop = new TiProperty(_name);
		prop->proxy = _proxy;
		prop->proxy->properties[_name] = prop;
	}
	prop->getterCallback = _getterCallback;

	if(_name.startsWith("get")) {
		prop->isFunction = true;
		return;
	}

	QString getter = QString(_name);
	getter[0] = getter[0].toUpper();
	getter.prepend("get");

	Ti::TiProperty::createGetter(_proxy, getter, _getterCallback);
}


void Ti::TiProperty::createProperty(TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback,  PROPERTY_GETTER _getterCallback)
{
	Ti::TiProperty::createSetter(_proxy, _name, _setterCallback);
	Ti::TiProperty::createGetter(_proxy, _name, _getterCallback);
}

void Ti::TiProperty::createFunction(TiProxy* _proxy, QString _name, PROPERTY_FUNCTION _callback)
{
	Ti::TiProperty *prop;
	if(_proxy->properties.contains(_name))
	{
		prop = _proxy->properties[_name];
	}
	else
	{
		prop = new TiProperty(_name);
		prop->proxy = _proxy;
		prop->proxy->properties[_name] = prop;
	}
	prop->callback = _callback;
	prop->isFunction = true;
}


Handle<Value> Ti::TiProperty::onInvoke(const Arguments& args)
{
	HandleScope scope;
	Ti::TiProperty* obj = static_cast<Ti::TiProperty*>(External::Unwrap(args.Data()));
	Handle<Value> result;
	if(obj->callback != NULL)
	{
		result = obj->callback(obj->proxy, Ti::TiValue(args)).toJSValue();
	}
	else
	if (obj->getterCallback != NULL)
	{
		result = obj->getterCallback(obj->proxy).toJSValue();
	}
	else
	if (obj->setterCallback != NULL)
	{
		if(args.Length() == 0) {
			obj->setterCallback(obj->proxy, Handle<Value>());
		} else {
			obj->setterCallback(obj->proxy, args[0]);
		}
		result = Undefined();
	}
	return scope.Close(result);
}

Handle<Value> Ti::TiProperty::getValue()
{
	if(isFunction)
		return value;

	if(getterCallback != NULL)
	{
		return getterCallback(proxy).toJSValue();
	}
	return Undefined();
}

Handle<Value> Ti::TiProperty::setValue(Handle<Value>value)
{
	if(isFunction)
		return value;

	if(setterCallback != NULL)
		setterCallback(proxy, Ti::TiValue(value));

	return Undefined();
}
