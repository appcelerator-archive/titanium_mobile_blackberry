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
#include <QObject>
#include <v8.h>

Ti::TiProxy::TiProxy(const char* name) :
__data__(NULL),
_proxyName(QString(name))
{
	HandleScope scope;
	_jsObjectTemplate = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
	_jsObjectTemplate->SetNamedPropertyHandler(Ti::TiProxy::_Getter, Ti::TiProxy::_Setter);
	_jsObject = Persistent<Object>::New(_jsObjectTemplate->NewInstance());

	createPropertyFunction("addEventListener", _addEventListener);
	createPropertyFunction("removeEventListener", _removeEventListener);
	createPropertyFunction("fireEvent", _fireEvent);
	createPropertyFunction("toString", _getToString);
	createPropertyFunction("applyProperties", _applyProperties);
}

Ti::TiProxy::~TiProxy()
{
	qDeleteAll(properties);
	properties.clear();

	_jsObject.Clear();
	_jsObject.Dispose();
	_jsObjectTemplate.Clear();
	_jsObjectTemplate.Dispose();
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
		_jsObject->Set(key, val);
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

Handle<ObjectTemplate> Ti::TiProxy::getJSObjectTemplate() {
	return _jsObjectTemplate;
}

void Ti::TiProxy::addFunction(const char* name, InvocationCallback callback)
{
	_jsObject->ForceSet(String::New(name), FunctionTemplate::New(callback)->GetFunction(), DontDelete);

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

void Ti::TiProxy::onEventAdded(QString str)
{
	events.append(str);
	// for subclass
}
void Ti::TiProxy::onEventRemoved(QString str)
{
	if(events.contains(str)) {
		events.removeOne(str);
	}
	// for subclass
}


Ti::TiValue Ti::TiProxy::addEventListener(Ti::TiValue value)
{
	QString eventName;

	Ti::TiValue nameValue = value.toList().at(0);
	Ti::TiValue functionValue = value.toList().at(1);

	eventName = nameValue.toString();

	onEventAdded(eventName);

	Ti::TiEvent::AddEventToObject(_jsObject, eventName, Handle<Function>::Cast(functionValue.toJSValue()));

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

	Ti::TiEvent::RemoveEventFromObject(_jsObject, eventName, func);
	Ti::TiValue res;
	res.setUndefined();
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
	Ti::TiEvent::FireCallbackIfNeeded(eventName, _jsObject, &params);
}
void Ti::TiProxy::fireEvent(QString eventName, Ti::TiEventParameters params)
{
	HandleScope scope;
	if(events.contains(eventName)) {
		if(!params.contains("source"))
		{
			params.addParam("source", this);
		}
		Ti::TiEvent::FireEventOnObject(_jsObject, eventName, &params);
	}
	if(eventName == Ti::TiConstants::EventClose)
	{
		Ti::TiHelper::LogInternal("Forcing GC");
		V8::LowMemoryNotification();
	}
}

Ti::TiValue Ti::TiProxy::getToString(Ti::TiValue)
{
	Ti::TiValue val;
	val.setString(QString("[object ").append(_proxyName).append("]"));
	return val;
}

Ti::TiValue Ti::TiProxy::getTiValueForKey(QString key)
{
	Handle<Value> val = _jsObject->Get(Ti::TiHelper::ValueFromQString(key));
	if(val.IsEmpty())
	{
		val = Undefined();
	}
	return Ti::TiValue(val);
}
void Ti::TiProxy::setTiValueForKey(Ti::TiValue value, QString key)
{
	_jsObject->Set(TiHelper::ValueFromQString(key), value.toJSValue());
}

void Ti::TiProxy::makeWeak()
{
	// if(_jsObject.IsEmpty()) return;
	// Ti::TiHelper::LogInternal(QString("Make weak ").append(QString(_proxyName)));
	_jsObject.MakeWeak(this, _WeakCallback);
}
void Ti::TiProxy::clearWeak()
{
	// if(_jsObject.IsEmpty()) return;
	// Ti::TiHelper::LogInternal(QString("Clear weak ").append(QString(_proxyName)));
	_jsObject.ClearWeak();
	_jsObjectTemplate.ClearWeak();
	_jsObject.MarkIndependent();
}

Handle<Value> Ti::TiProxy::_Getter (Local<String> property, const AccessorInfo& info)
{
	HandleScope handleScope;
	Handle<Object> obj = Handle<Object>::Cast(info.Holder());
	Handle<External> proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("module")));

	if(proxyObject.IsEmpty())
		proxyObject = Handle<External>::Cast(obj->GetHiddenValue(String::New("proxy")));

	if(proxyObject.IsEmpty())
		return handleScope.Close(Handle<Value>());

	Ti::TiProxy* tiProxy = static_cast<Ti::TiProxy*>(proxyObject->Value());

	if(tiProxy->properties.contains(Ti::TiHelper::QStringFromValue(property)))
	{
		Ti::TiProperty *prop = tiProxy->properties[Ti::TiHelper::QStringFromValue(property)];
		Handle<Value> r = prop->getValue();
		if(r.IsEmpty() || r->IsUndefined())
			return handleScope.Close(Handle<Value>());
		return handleScope.Close(r);
	}
	return handleScope.Close(Handle<Value>());
}

Handle<Value> Ti::TiProxy::_Setter (Local<String> property, Local<Value> value, const AccessorInfo& info)
{
	HandleScope handleScope;
	// Ti::TiHelper::LogInternal(QString("Property Setter: ").append(Ti::TiHelper::QStringFromValue(property)));

	// Todo: Come back to this later
	// if(value == info.Holder()->Get(property)) {
	//	 Ti::TiHelper::LogInternal(QString("Already set: ").append(Ti::TiHelper::QStringFromValue(property)));
	//	 return value;
	// }


	Handle<Object> obj = Handle<Object>::Cast(info.Holder());
	// Todo: come back to this - might not be allowing GC to collect proxies
	obj->ForceSet(property, value);
	// for example. scrollView.views = [a,b,c]
	// scrollView.remove(a) <--- removed from view, but still in array
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

void Ti::TiProxy::_WeakCallback(Persistent<Value>, void* parameter)
{
	Ti::TiProxy* obj = static_cast<Ti::TiProxy*>(parameter);
	delete obj;
	obj = NULL;
}
