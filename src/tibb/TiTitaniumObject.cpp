/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTitaniumObject.h"

#include "TiAPIObject.h"
#include "TiAppObject.h"
#include "TiBufferObject.h"
#include "TiBufferStreamObject.h"
#include "TiCodecObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "TiPlatformObject.h"
#include "TiLocaleObject.h"
#include "TiStreamObject.h"
#include "TiUIObject.h"
#include "TiMap.h"
#include "TiNetwork.h"
#include "TiDatabase.h"
#include "TiV8EventContainerFactory.h"
#include "V8Utils.h"

#include <fstream>

static const string rootFolder = "app/native/assets/";

TiTitaniumObject::TiTitaniumObject()
    : TiProxy("Titanium")
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
    TiProxy::onCreateStaticMembers();

    ADD_STATIC_TI_VALUE("buildDate", String::New(__DATE__), this);
    // TODO: remove hard coded version number
    ADD_STATIC_TI_VALUE("version", Number::New(2.0), this);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "globalInclude", this, _globalInclude);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "include", this, _globalInclude);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createBuffer", this, _createBuffer);
    TiUIObject::addObjectToParent(this, objectFactory_);
    TiMap::addObjectToParent(this, objectFactory_);
    TiAPIObject::addObjectToParent(this);
    TiAppObject::addObjectToParent(this);
    TiPlatformObject::addObjectToParent(this);
    TiCodecObject::addObjectToParent(this);
    TiNetwork::addObjectToParent(this, objectFactory_);
    TiDatabase::addObjectToParent(this, objectFactory_);
    TiBufferStreamObject::addObjectToParent(this);
    TiStreamObject::addObjectToParent(this);
    TiLocaleObject::addObjectToParent(this);
}

bool TiTitaniumObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiTitaniumObject::_globalInclude(void*, TiObject*, const Arguments& args)
{
	if (args.Length() < 2)
	{
		return ThrowException(String::New(Ti::Msg::Missing_argument));
	}

	string id = *String::Utf8Value(args[0]->ToString());

	string parentFolder = *String::Utf8Value(args[1]->ToString());

	// CommonJS path rules
	if (id.find("/") == 0) {
		id.replace(id.find("/"), std::string("/").length(), rootFolder);
	}
	else if (id.find("./") == 0) {
		id.replace(id.find("./"), std::string("./").length(), parentFolder);
	}
	else if (id.find("../") == 0) {
		// count ../../../ in id and strip off back of parentFolder
		int count = 0;
		size_t idx = 0;
		size_t pos = 0;
		while (true) {
			idx = id.find("../", pos);
			if (idx == std::string::npos) {
				break;
			} else {
				pos = idx + 3;
				count++;
			}
		}

		// strip leading ../../ off module id
		id = id.substr(pos);

		// strip paths off the parent folder
		idx = 0;
		pos = parentFolder.size();
		for (int i = 0; i < count; i++) {
			idx = parentFolder.find_last_of("/", pos);
			pos = idx - 1;
		}

		if (idx == std::string::npos) {
			return ThrowException(String::New("Unable to find module"));
		}

		parentFolder = parentFolder.substr(0, idx + 1);

		id = parentFolder + id;
	}
	else {
		string tempId = rootFolder + id;

		ifstream ifs((tempId).c_str());
		if (!ifs) {
			id = parentFolder + id;
		}
		else {
			id = rootFolder + id;
		}
	}

	string filename = id;

	string javascript;
	{
		ifstream ifs((filename).c_str());
		if (!ifs)
		{
			Local<Value> taggedMessage = String::New((string(Ti::Msg::No_such_native_module) + " " + id).c_str());
			return ThrowException(taggedMessage);
		}
		getline(ifs, javascript, string::traits_type::to_char_type(string::traits_type::eof()));
		ifs.close();
	}

	// wrap the module
	{
		size_t idx = filename.find_last_of("/");
		parentFolder = filename.substr(0, idx + 1);
		static const string preWrap = "Ti.include = function (id) { Ti.globalInclude(id, '" + parentFolder + "')};\n";
		javascript = preWrap + javascript;
	}

	TryCatch tryCatch;
	Handle<Script> compiledScript = Script::Compile(String::New(javascript.c_str()), String::New(filename.c_str()));
	if (compiledScript.IsEmpty())
	{
		DisplayExceptionLine(tryCatch);
		return tryCatch.ReThrow();
	}

	Persistent<Value> result = Persistent<Value>::New(compiledScript->Run());
	if (result.IsEmpty())
	{
		return tryCatch.ReThrow();
	}


    return Undefined();
}

Handle<Value> TiTitaniumObject::_createBuffer(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiTitaniumObject* obj = (TiTitaniumObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiBufferObject* newBuffer = TiBufferObject::createBuffer(obj->objectFactory_);
    newBuffer->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newBuffer->setParametersFromObject(newBuffer, settingsObj);
    }
    setTiObjectToJsObject(result, newBuffer);
    return handleScope.Close(result);
}
