/*
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Value.h"
#include "Ti_Proxy.h"
#include <bb/cascades/Color>
#include <Qt/qcolor.h>

Ti::TiValue::TiValue(Handle<Value> value) :
		_proxy(NULL),
		_string(""),
		_number(0),
		_bool(false),
		_jsValue(NULL)
{
	setValue(value);
}

Ti::TiValue::TiValue(const Arguments& args) :
	_proxy(NULL),
	_string(""),
	_number(0),
	_bool(false),
	_jsValue(NULL)
{

	if(args.Length() == 0 || args.Length() == 1)
	{
		setValue(args[0]);
	}
	else
	{
		Handle<Array> array = Array::New(args.Length());
		for(uint32_t i = 0, len = args.Length(); i < len; i++)
		{
			array->Set(i, args[i]);
		}
		setValue(array);
	}
}

Ti::TiValue::TiValue() :
	_proxy(NULL),
	_string(""),
	_number(0),
	_bool(false),
	_jsValue(NULL)
{
}
void Ti::TiValue::setValue(Handle<Value> value)
{
	_jsValue = value;
	_bool = value->ToBoolean()->Value();
	_number = value->ToNumber()->Value();
	_string = QString(*String::Utf8Value(value->ToString()));
	if(value->IsArray())
	{
		Handle<Array> ar = Handle<Array>::Cast(value);
		uint32_t len = ar->Length();
		for(uint32_t i = 0; i < len; i++) {
			_list.append(Ti::TiValue(ar->Get(i)));
		}
		return;
	}
	if(value->IsObject())
	{
		Local<Object> obj = value->ToObject();
		Handle<Value> _a = obj->GetHiddenValue(String::New("proxy"));
		if(_a.IsEmpty())
		{
			_a = obj->GetHiddenValue(String::New("module"));
		}
		if(_a.IsEmpty())
		{
			Local<Array> props = obj->GetPropertyNames();
			for(int i = 0, len = props->Length(); i < len; i++) {
				Local<String> key = props->Get(i)->ToString();
				Local<Value> val = obj->Get(key);
				_map[QString(*String::Utf8Value(key))] = Ti::TiValue(val);
			}
			return;
		}

		Handle<External> _b = Handle<External>::Cast(_a);
		if(_b->Value())
		{
			_proxy = static_cast<Ti::TiProxy*>(_b->Value());
		}
	}

}

void Ti::TiValue::setMap(QMap<QString, Ti::TiValue> map)
{
	Local<Object> jsObject = Object::New();
	foreach(QString key, map.keys())
	{
		Ti::TiValue val = map[key];
		jsObject->Set(Ti::TiHelper::ValueFromQString(key), val.toJSValue());
	}
	setValue(jsObject);
}


bb::cascades::Color Ti::TiValue::toColor() {
	if (!QColor::isValidColor(_string))
	{
		return bb::cascades::Color::Yellow;
	}
	QColor qcolor(_string);
	qreal qr, qg, qb, qa;
	qcolor.getRgbF(&qr, &qg, &qb, &qa);
	float r = qr;
	float g = qg;
	float b = qb;
	float a = qa;
	return bb::cascades::Color::fromRGBA(r, g, b, a);
}

Handle<Value> Ti::TiValue::toJSValue()
{
	return _jsValue;
}
QString Ti::TiValue::toString()
{
	return _string;
}
Ti::TiProxy *Ti::TiValue::toProxy()
{
	return _proxy;
}
bool Ti::TiValue::toBool()
{
	return _bool;
}
double Ti::TiValue::toNumber()
{
	return _number;
}
QList<Ti::TiValue> Ti::TiValue::toList()
{
	return _list;
}

QMap<QString, Ti::TiValue> Ti::TiValue::toMap()
{
	return _map;
}

void Ti::TiValue::setList(QList<Ti::TiValue> list)
{
	Handle<Array> ar = Array::New(list.size());
	for(int i = 0, len = list.size(); i < len; i++)
	{
		Ti::TiValue currentValue = list.at(i);
		ar->Set( i, currentValue.toJSValue());
	}
	_jsValue = ar;
}

void Ti::TiValue::setString(QString val)
{
	_string = val;
	_jsValue = String::New(_string.toLocal8Bit().constData());
}
void Ti::TiValue::setNumber(double val)
{
	_number = val;
	_jsValue = Number::New(_number);
}
void Ti::TiValue::setBool(bool val)
{
	_bool = val;
	_jsValue = Boolean::New(_bool);
}
void Ti::TiValue::setProxy(Ti::TiProxy* val)
{
	_proxy = val;
	_jsValue = _proxy->realJSObject;
}

void Ti::TiValue::setNull()
{
	_jsValue = Null();
}

void Ti::TiValue::setUndefined()
{
	_jsValue = Undefined();
}

bool Ti::TiValue::isList()
{
	return _jsValue->IsArray();
}

bool Ti::TiValue::isProxy()
{
	return _proxy != NULL;
}

bool Ti::TiValue::isNumber()
{
	return (_jsValue->IsNumber() || _jsValue->IsNumberObject());
}

bool Ti::TiValue::isUndefined()
{
	return _jsValue->IsUndefined();
}

bool Ti::TiValue::isNull()
{
	return _jsValue->IsNull();
}

bool Ti::TiValue::isMap()
{
	return _map.size() != 0;
}

bool Ti::TiValue::isString()
{
	return _jsValue->IsString();
}

Ti::TiValue::~TiValue()
{

}
