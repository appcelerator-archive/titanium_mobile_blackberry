/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTitaniumObject.h"
#include "TiAPIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiUIObject.h"

#include <fstream>

TiTitaniumObject::TiTitaniumObject()
    : TiObject("Titanium")
{
    objectFactory_ = NULL;
}

TiTitaniumObject::~TiTitaniumObject()
{
}

TiObject* TiTitaniumObject::createObject(NativeObjectFactory* objectFactory)
{
    TiTitaniumObject* obj = new TiTitaniumObject;
    obj->objectFactory_ = objectFactory;
    return obj;
}

void TiTitaniumObject::onCreateStaticMembers()
{
    ADD_STATIC_TI_VALUE("buildDate", String::New(__DATE__), this);
    ADD_STATIC_TI_VALUE("version", Number::New(2.0), this);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "include", this, _include);
    // TODO: remove hard coded version number
    TiUIObject::addObjectToParent(this, objectFactory_);
    TiAPIObject::addObjectToParent(this);
}

bool TiTitaniumObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiTitaniumObject::_include(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return Undefined();
    }

    Local<Value> javaScript = args[0];
    if (!javaScript->IsString())
    {
        javaScript = javaScript->ToString();
    }

    string fileName = "app/native/assets/";
    fileName += *String::Utf8Value(javaScript);

    ifstream ifs(fileName.c_str());

    if (ifs.bad())
    {
        return Undefined();
    }

    string buffer;
    getline(ifs, buffer, string::traits_type::to_char_type(string::traits_type::eof()));
    ifs.close();

    TryCatch tryCatch;
    Handle<Script> compiledScript = Script::Compile(String::New(buffer.c_str()));
    if (compiledScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(string(*error) + "\n");
        return Undefined();
    }
    Handle<Value>result = compiledScript->Run();
    if (result.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(string(*error) + "\n");
        return Undefined();
    }

    return Undefined();
}
