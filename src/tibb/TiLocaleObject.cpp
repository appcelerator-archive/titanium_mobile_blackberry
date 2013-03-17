/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiLocaleObject.h"
#include "TiGenericFunctionObject.h"
#include <bb/data/XmlDataAccess>

TiLocaleObject::TiLocaleObject()
    : TiProxy("Locale")
{
}

TiLocaleObject::~TiLocaleObject()
{
}

void TiLocaleObject::addObjectToParent(TiObject* parent)
{
    TiLocaleObject* obj = new TiLocaleObject;
    parent->addMember(obj);
}

void TiLocaleObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getString", this, _getString);

    TiGenericFunctionObject::addGenericFunctionToParent(this, "getCurrentLanguage", this, _getCurrentLanguage);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getCurrentCountry", this, _getCurrentCountry);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getCurrentLocale", this, _getCurrentLocale);

    // void ADD_STATUS_TI_VALUE(const char* name, Handle<Value> value, TiObject* parent)
    ADD_STATIC_TI_VALUE("currentLanguage", TiLocaleObject::_getCurrentLanguage(), this);
    ADD_STATIC_TI_VALUE("currentCountry", TiLocaleObject::_getCurrentCountry(), this);
    ADD_STATIC_TI_VALUE("currentLocale", TiLocaleObject::_getCurrentLocale(), this);
}

Handle<Value> TiLocaleObject::_getCurrentCountry()
{
	QString value = LocaleParser::sharedInstance()->getLocaleCountry();
    Handle<String> result = String::New(value.toUtf8());
    return result;
}

Handle<Value> TiLocaleObject::_getCurrentLocale()
{
	QString value = LocaleParser::sharedInstance()->getLocale();
    Handle<String> result = String::New(value.toUtf8());
    return result;
}

Handle<Value> TiLocaleObject::_getCurrentLanguage()
{
	QString value = LocaleParser::sharedInstance()->getLocaleLanguage();
    Handle<String> result = String::New(value.toUtf8());
    return result;
}

Handle<Value> TiLocaleObject::_getCurrentCountry(void*, TiObject*, const Arguments& args) {
	return TiLocaleObject::_getCurrentCountry();
}
Handle<Value> TiLocaleObject::_getCurrentLocale(void*, TiObject*, const Arguments& args)
{
	return TiLocaleObject::_getCurrentLocale();
}
Handle<Value> TiLocaleObject::_getCurrentLanguage(void*, TiObject*, const Arguments& args)
{
	return TiLocaleObject::_getCurrentLanguage();
}
Handle<Value> TiLocaleObject::_getString(void*, TiObject*, const Arguments& args)
{
	Handle<String> arg1 = Handle<String>::Cast(args[0]);
	Handle<String> arg2 = Handle<String>::Cast(args[1]);

    String::Utf8Value arg1string(arg1);
    String::Utf8Value arg2string(arg2);

    QString value1 = QString(*arg1string);
    QString value2 = QString(*arg2string);
    QString returnedString;

   	returnedString = LocaleParser::sharedInstance()->getString(value1, value2);

    Handle<String> result = String::New(returnedString.toUtf8());
    return result;

}
