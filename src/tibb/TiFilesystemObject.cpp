/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiFilesystemObject.h"
#include "TiFilesystemFileObject.h"
#include "TiGenericFunctionObject.h"
#include <QDir>
#include <iostream>

TiFilesystemObject::TiFilesystemObject(NativeObjectFactory* objectFactory)
    : TiProxy("Filesystem")
{
	_objectFactory = objectFactory;

}

TiFilesystemObject::~TiFilesystemObject()
{
}

void TiFilesystemObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiFilesystemObject* obj = new TiFilesystemObject(objectFactory);
    parent->addMember(obj);
}

Handle<Value> TiFilesystemObject::getResourcesDirectory() {

//	return String::New(QDir::rootPath().toUtf8().constData());
	return String::New("app/native/assets");
}

Handle<Value> TiFilesystemObject::getTempDirectory() {
	return String::New(QDir::tempPath().toUtf8().constData());
}

Handle<Value> TiFilesystemObject::getDataDirectory() {
	return  String::New(QDir::homePath().toUtf8().constData());
}

void TiFilesystemObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();

    ADD_STATIC_TI_VALUE("resourcesDirectory", TiFilesystemObject::getResourcesDirectory(), this);
    ADD_STATIC_TI_VALUE("tempDirectory", TiFilesystemObject::getTempDirectory(), this);
    ADD_STATIC_TI_VALUE("applicationDataDirectory", TiFilesystemObject::getDataDirectory(), this);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getFile", this, _getFile);
}

Handle<Value> TiFilesystemObject::_getFile(void* userContext, TiObject* , const Arguments& args)
{
	// Get the paths from the arguments
	QString path = "";
	for(int i = 0, len = args.Length(); i < len; i++) {
        String::Utf8Value v8UtfString(Handle<String>::Cast(args[i]));
        const char* cStr = *v8UtfString;
        path.append(cStr).append("/");
	}
	// remove the last "/"
	path.remove(path.length() - 1, 1);
	// in case there is double slashesh, remove them
	// Ti.Filesyste.getFile( Ti.Filestem.resourceDirectory, '/app.js')
	// or
	// Ti.Filesyste.getFile( Ti.Filestem.resourceDirectory, 'app.js')
	path.replace("//", "/");

    HandleScope handleScope;
    // Get the Filesystem object
    TiFilesystemObject* obj = (TiFilesystemObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();

    // Create a File object
    TiFilesystemFileObject* fileObject = new TiFilesystemFileObject(path);
    fileObject->setNativeObjectFactory(obj->_objectFactory);
    fileObject->setValue(result);

    // Return it
    setTiObjectToJsObject(result, fileObject);
    return handleScope.Close(result);
}
