/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTitaniumObject.h"
#include "TiAPIObject.h"
#include "TiPlatformObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
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
    // TODO: remove hard coded version number
    ADD_STATIC_TI_VALUE("version", Number::New(2.0), this);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "include", this, _include);
    TiUIObject::addObjectToParent(this, objectFactory_);
    TiAPIObject::addObjectToParent(this);
    TiPlatformObject::addObjectToParent(this);
}

bool TiTitaniumObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiTitaniumObject::_include(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    Local<Value> javaScript = args[0];
    if (!javaScript->IsString())
    {
        javaScript = javaScript->ToString();
    }

    static string sRelDir = "";

    // TODO: Add functionality to grab all this information from userContext
    static const string base = "app/native/assets/";
    string filename = *String::Utf8Value(javaScript);
    string fullPath = base + sRelDir + filename;

    // TODO: Check this against url and event handlers
    // Get the directory before slash
    std::string::size_type slash_pos = filename.rfind("/");
    if (slash_pos != std::string::npos)
    {
        slash_pos++;
        sRelDir += filename.substr(0, slash_pos);
    }

    ifstream ifs(fullPath.c_str());

    if (!ifs)
    {
        return ThrowException(String::Concat(String::New(fullPath.c_str()), String::New(Ti::Msg::Include_file_not_found)));
    }

    string buffer;
    getline(ifs, buffer, string::traits_type::to_char_type(string::traits_type::eof()));
    ifs.close();

    TryCatch tryCatch;
    Handle<Script> compiledScript = Script::Compile(String::New(buffer.c_str()), String::New(fullPath.c_str()));
    if (compiledScript.IsEmpty())
    {
        return ThrowException(tryCatch.Exception());
    }
    Handle<Value>result = compiledScript->Run();
    if (result.IsEmpty())
    {
        return ThrowException(tryCatch.Exception());
    }

    // Reset relative path
    sRelDir = "";

    return Undefined();
}
