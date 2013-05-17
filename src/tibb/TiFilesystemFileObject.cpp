/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiFilesystemFileObject.h"
#include "TiGenericFunctionObject.h"
#include "TiBlobObject.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

TiFilesystemFileObject::~TiFilesystemFileObject()
{
}

TiFilesystemFileObject::TiFilesystemFileObject(QString path)
: TiProxy("File")
{
	initializeTiObject(NULL);
	_path = path;
}

QString TiFilesystemFileObject::getPath()
{
	return _path;
}

void TiFilesystemFileObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "write", this, _write);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "append", this, _append);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "read", this, _read);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "exists", this, _exists);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getNativePath", this, _getNativePath);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isDirectory", this, _isDirectory);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isFile", this, _isFile);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getWritable", this, _writable);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createDirectory", this, _createDirectory);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createFile", this, _createFile);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "deleteFile", this, _deleteFile);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "deleteDirectory", this, _deleteDirectory);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getDirectoryListing", this, _getDirectoryListing);

    ADD_STATIC_TI_VALUE("writable", TiFilesystemFileObject::getIsWritable(this), this);
}

Handle<Value> TiFilesystemFileObject::getIsWritable(TiFilesystemFileObject *file)
{
	QFileInfo fileInfo(file->getPath());
	return Boolean::New(fileInfo.isWritable());
}

Handle<Value> TiFilesystemFileObject::_writable(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	return TiFilesystemFileObject::getIsWritable(obj);
}

Handle<Value> TiFilesystemFileObject::_deleteFile(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFile file(obj->getPath());
	file.remove();
	return Undefined();
}

Handle<Value> TiFilesystemFileObject::_getDirectoryListing(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;

	QDir directory(obj->getPath());
	QStringList list = directory.entryList();

	Local<Array> array = Array::New(list.length());
	for(uint32_t i = 0, len = list.length(); i < len; i++) {
		QString str = list.at(i);
		array->Set(i, String::New(str.toUtf8().constData()));
	}
	return array;
}

Handle<Value> TiFilesystemFileObject::_deleteDirectory(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFileInfo fileInfo(obj->getPath());
	QDir dir = fileInfo.path();
	return Boolean::New(dir.rmdir(obj->getPath()));
}

Handle<Value> TiFilesystemFileObject::_createFile(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFile file(obj->getPath());

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return Boolean::New(false);
	}
	file.write(0);
	file.close();
	return Boolean::New(true);
}

Handle<Value> TiFilesystemFileObject::_createDirectory(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	// Geth the directory info
	QFileInfo fileInfo(obj->getPath());
	// Geth the path directory
	QDir dir = fileInfo.path();
	// create it return true or false
	return Boolean::New(dir.mkdir(obj->getPath()));
}

Handle<Value> TiFilesystemFileObject::_isDirectory(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFileInfo fileInfo(obj->getPath());
	return Boolean::New(fileInfo.isDir());
}

Handle<Value> TiFilesystemFileObject::_isFile(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFileInfo fileInfo(obj->getPath());
	return Boolean::New(fileInfo.isFile());
}

Handle<Value> TiFilesystemFileObject::_exists(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFile file(obj->getPath());
	return Boolean::New(file.exists());
}

Handle<Value> TiFilesystemFileObject::_getNativePath(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFile file(obj->getPath());
	if(!file.exists()) {
		return Undefined();
	}
	QFileInfo fileInfo(file);
	Handle<Value> result = String::New(fileInfo.absolutePath().toUtf8().constData());
	return result;
}

Handle<Value> TiFilesystemFileObject::_write(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
	QFile file(obj->getPath());
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return Boolean::New(false);
	}

	if(args[0]->IsString()) {
	    const String::Utf8Value utf8(args[0]);
	    QString str = QString::fromUtf8(*utf8);
	    file.write(str.toUtf8());
	    file.close();
	    return Undefined();
	} else if(args[0]->IsObject()) {
        TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
       	TiBlobObject *blob =  (TiBlobObject*)tiObj;
      	file.write(blob->data());
	}

	return Boolean::New(true);
}

Handle<Value> TiFilesystemFileObject::_append(void* userContext, TiObject* tiObject, const Arguments& args)
{

	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
    QString str = "";

    QFile file(obj->getPath());
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
    	return Undefined();
    }

    HandleScope handleScope;
    QByteArray a;
    if(args[0]->IsString()) {
	    const String::Utf8Value utf8(args[0]);
	    QString str = QString::fromUtf8(*utf8);
	    a.append(str.toUtf8());
	    file.write(a);
	} else if(args[0]->IsObject()) {
        TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
       	TiBlobObject *blob =  (TiBlobObject*)tiObj;
       	a.append(blob->data());
       	file.write(a);
	}

    file.close();

	return Boolean::New(true);
}

Handle<Value> TiFilesystemFileObject::_read(void* userContext, TiObject*, const Arguments& args)
{
	TiFilesystemFileObject* obj = (TiFilesystemFileObject*) userContext;
    QString str = "";
	QFile file(obj->getPath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    	return Undefined();
    }

    HandleScope handleScope;

    TiBlobObject* blob = TiBlobObject::createBlob(obj->getNativeObjectFactory());
    Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(obj->getValue());
    Local<Object> proxy = templ->NewInstance();
    blob->setValue(proxy);
    TiObject::setTiObjectToJsObject(proxy, blob);

    QByteArray a = file.readAll();
    // TODO: figure out mime type
    blob->setData(a, "text/plain");
    file.close();

    return handleScope.Close(proxy);
}
