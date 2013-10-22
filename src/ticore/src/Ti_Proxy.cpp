/*
 * TiProxy.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Proxy.h"
#include "Ti_Helper.h"
#include "Ti_Constants.h"

Ti::TiProxy::TiProxy(const char* name) : _proxyName(QString(name))
{
	HandleScope scope;
	jsObject = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
	jsObject->SetNamedPropertyHandler(Ti::TiProxy::_Getter, Ti::TiProxy::_Setter);

	createPropertyFunction("addEventListener", _addEventListener);
	createPropertyFunction("removeEventListener", _removeEventListener);
	createPropertyFunction("fireEvent", _fireEvent);
	createPropertyFunction("toString", _getToString);
//	Ti::TiHelper::Log(QString(_proxyName).append(" Created"));
}

Ti::TiProxy::~TiProxy()
{
//	qDebug() << "[DELETE] TiProxy" << getProxyName();
	foreach(QString key, events.keys())
	{
		qDeleteAll(events[key]);
		events[key].clear();
	}
	events.clear();
	qDeleteAll(properties);
	properties.clear();
}

void Ti::TiProxy::initStart()
{

}

void Ti::TiProxy::initWithObject(Handle<Object> obj)
{
	HandleScope scope;
	Local<Array> props = obj->GetPropertyNames();
	for(int i = 0, len = props->Length(); i < len; i++) {
		Local<String> key = props->Get(i)->ToString();
		Local<Value> val = obj->Get(key);
		realJSObject->Set(key, val);
	}
}

Ti::TiValue Ti::TiProxy::applyProperties(Ti::TiValue value)
{
	if(value.isMap())
	{
		initWithObject(value.toJSValue()->ToObject());
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

void Ti::TiProxy::initEnd()
{

}

const char* Ti::TiProxy::getProxyName()
{
	return _proxyName.toLocal8Bit().constData();
}

Handle<ObjectTemplate> Ti::TiProxy::getJSObject() {
	return jsObject;
}

void Ti::TiProxy::addFunction(const char* name, InvocationCallback callback)
{
	jsObject->Set(name, FunctionTemplate::New(callback));
}
void Ti::TiProxy::createPropertyFunction(QString name, PROPERTY_FUNCTION callback)
{
	Ti::TiProperty::createFunction(this, name, callback);
}
void Ti::TiProxy::createPropertySetter(QString name, PROPERTY_SETTER callback)
{
	Ti::TiProperty::createSetter(this, name, callback);
}
void Ti::TiProxy::createPropertyGetter(QString name, PROPERTY_GETTER callback)
{
	Ti::TiProperty::createGetter(this, name, callback);
}
void Ti::TiProxy::createPropertySetterGetter(QString name, PROPERTY_SETTER setter, PROPERTY_GETTER getter)
{
	Ti::TiProperty::createProperty(this, name, setter, getter);
}

void Ti::TiProxy::onEventAdded(QString)
{
	// for subclass
}
void Ti::TiProxy::onEventRemoved(QString)
{
	// for subclass
}


Ti::TiValue Ti::TiProxy::addEventListener(Ti::TiValue value)
{
	QString eventName;

	Ti::TiValue nameValue = value.toList().at(0);
	eventName = nameValue.toString();

	onEventAdded(eventName);
	Ti::TiValue functionValue = value.toList().at(1);
	Handle<Function> func = Handle<Function>::Cast(functionValue.toJSValue());

	Ti::TiEvent *newEvent = new Ti::TiEvent(func);
	if(events.contains(eventName))
	{
		events[eventName].append(newEvent);
	}
	else
	{
		QList<Ti::TiEvent*> list;
		list.append(newEvent);
		events.insert(eventName, list);
	}


	Ti::TiValue res;
	res.setUndefined();
	return res;
}

Ti::TiValue Ti::TiProxy::removeEventListener(Ti::TiValue value)
{
	Ti::TiValue nameValue = value.toList().at(0);
	QString eventName = nameValue.toString();

	Ti::TiValue functionValue = value.toList().at(1);
	Handle<Function> func = Handle<Function>::Cast(functionValue.toJSValue());

	Ti::TiValue res;
	res.setUndefined();

	if(events.contains(eventName))
	{
		QList<Ti::TiEvent*> list = events[eventName];
		for(int i = 0, len = list.length(); i < len; i++)
		{
			Ti::TiEvent *event = list.at(i);
			if(event->callback == func)
			{
//				Ti::TiHelper::Log("Remove this event");
				delete event;
				events[eventName].removeAt(i);
				onEventRemoved(eventName);
				return res;
			}
		}
	}
	return res;
}

// TODO: Finish this
Ti::TiValue Ti::TiProxy::fireEvent(Ti::TiValue value)
{
	QString eventName;
	Ti::TiEventParameters eventParams;
	if(value.isList()) {

		Ti::TiValue eName = value.toList().at(0);
		Ti::TiValue eParams = value.toList().at(1);
		eventName = eName.toString();

		if(eParams.isMap())
		{
			QMap<QString, Ti::TiValue> map = eParams.toMap();
			QList<QString> keys = map.keys();
			int len = keys.size();
			while(len--)
			{
				QString 	name 	= keys.at(len);
				Ti::TiValue val 	= map[name];

				if(val.isNumber())
				{
					eventParams.addParam(name, val.toNumber());
				}
				else if (val.isProxy())
				{
					eventParams.addParam(name, val.toProxy());
				}
				else // if(val.isString())
				{
					eventParams.addParam(name, val.toString());
				}
			}
		}
	}
	else
	{
		eventName = value.toString();
	}

	fireEvent(eventName, eventParams);

	return Ti::TiValue(Undefined());
}

void Ti::TiProxy::fireCallback(QString eventName, Ti::TiEventParameters params)
{
	Ti::TiEvent::fireCallbackIfNeeded(eventName, realJSObject, &params);
}
void Ti::TiProxy::fireEvent(QString eventName, Ti::TiEventParameters params)
{
	HandleScope scope;
	if(events.contains(eventName))
	{
		QList<Ti::TiEvent*> list = events[eventName];
		for(int i = 0, len = list.length(); i < len; i++)
		{
			Ti::TiEvent *event = list.at(i);
			event->fireWithParameters(realJSObject, &params);
		}
	}
	if(eventName == Ti::TiConstants::EventClose)
	{
		V8::LowMemoryNotification();
	}
}

Ti::TiValue Ti::TiProxy::getToString(Ti::TiValue)
{
	Ti::TiValue val;
	val.setString(QString("[object ").append(_proxyName).append("]"));
	return val;
}


void Ti::TiProxy::makeWeak()
{
	realJSObject.MakeWeak(this, _WeakCallback);

}
void Ti::TiProxy::clearWeak()
{
	realJSObject.ClearWeak();
}

Handle<Value> Ti::TiProxy::_Getter (Local<String> property, const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle<Object> result;
    Handle<Object> obj = Handle<Object>::Cast(info.Holder());
    Handle<External> proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("module")));

//	Ti::TiHelper::Log(QString("Property Getter ").append(Ti::TiHelper::QStringFromValue(property)));

    if(proxyObject.IsEmpty())
		proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("proxy")));

	if(proxyObject.IsEmpty())
		return result;

	Ti::TiProxy* tiProxy = static_cast<Ti::TiProxy*>(proxyObject->Value());

	if(tiProxy->properties.contains(Ti::TiHelper::QStringFromValue(property)))
	{

		Ti::TiProperty *prop = tiProxy->properties[Ti::TiHelper::QStringFromValue(property)];
		return handleScope.Close(prop->getValue());
	}

	return handleScope.Close(result);
}

Handle<Value> Ti::TiProxy::_Setter (Local<String> property, Local<Value> value, const AccessorInfo& info)
{
	HandleScope handleScope;

	// Todo: come back to this - might not be allowing GC to collect proxies
	info.Holder()->ForceSet(property, value);
	// for example. scrollView.views = [a,b,c]
	// scrollView.remove(a) <--- removed from view, but still in array

    Handle<Object> obj = Handle<Object>::Cast(info.Holder());
    Handle<External> proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("module")));
	if(proxyObject.IsEmpty())
		proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("proxy")));

	if(proxyObject.IsEmpty())
		return value;

	Ti::TiProxy* tiProxy = static_cast<Ti::TiProxy*>(proxyObject->Value());

	if(tiProxy->properties.contains(Ti::TiHelper::QStringFromValue(property)))
	{

		Ti::TiProperty *prop = tiProxy->properties[Ti::TiHelper::QStringFromValue(property)];
		return handleScope.Close(prop->setValue(value));
	}

	return value;
}

void Ti::TiProxy::_WeakCallback(Persistent<Value> object, void* parameter)
{
	Ti::TiProxy* obj = static_cast<Ti::TiProxy*>(parameter);
	delete obj;
	object.ClearWeak();
	object.Clear();
	object.Dispose();
}
