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

	createPropertyFunction("addEventListener", _addEventListener);
	createPropertyFunction("removeEventListener", _removeEventListener);
	createPropertyFunction("fireEvent", _fireEvent);
	createPropertyFunction("toString", _getToString);
    //	Ti::TiHelper::Log(QString(_proxyName).append(" Created"));
}

Ti::TiProxy::~TiProxy()
{
	qDebug() << "[INTERNAL] DELETING PROXY" << getProxyName();
	qDeleteAll(properties);
	properties.clear();

	_jsObject.Clear();
	_jsObject.Dispose();
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
	_jsObjectTemplate->Set(name, FunctionTemplate::New(callback));
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
	qDebug() << "Event Added" << str;
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
	Ti::TiEvent::FireEventOnObject(_jsObject, eventName, &params);
	if(eventName == Ti::TiConstants::EventClose)
	{
		qDebug() << "[TIPROXY] force GC";
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
	return Ti::TiValue(_jsObject->Get(Ti::TiHelper::ValueFromQString(key)));
}
void Ti::TiProxy::setTiValueForKey(Ti::TiValue value, QString key)
{
	_jsObject->Set(TiHelper::ValueFromQString(key), value.toJSValue());
}

void Ti::TiProxy::makeWeak()
{
	//if(_jsObject.IsEmpty()) return;
	qDebug() << "TiProxy: Make weak" << _proxyName;
	_jsObject.MakeWeak(this, _WeakCallback);
}
void Ti::TiProxy::clearWeak()
{
	//if(_jsObject.IsEmpty()) return;
	qDebug() << "TiProxy: Clear weak" << _proxyName;
	_jsObject.ClearWeak();
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
    //	Ti::TiHelper::Log(QString("Property Setter ").append(Ti::TiHelper::QStringFromValue(property)));

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
	obj = NULL;
}
