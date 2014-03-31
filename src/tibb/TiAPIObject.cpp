/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAPIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "TiCore.h"

static TiAPIObject* _instance = NULL;

TiAPIObject::TiAPIObject()
    : TiProxy("API")
{
	_instance = this;
	QString ipAddress = Ti::TiHelper::getAppSetting("current_ip").toString();
	bool hasPort = true;
	int port = Ti::TiHelper::getAppSetting("current_port").toInt(&hasPort);
    _socket = new QTcpSocket();
    if(hasPort) {
    	_socket->connectToHost(ipAddress, port);
        _socket->waitForConnected(3000);
    }
}

TiAPIObject::~TiAPIObject()
{
	delete _socket;
}

void TiAPIObject::Log(QString str)
{
	_instance->_socket->write(str.toLocal8Bit().constBegin());
    TiLogger::getInstance().log(str);
}

void TiAPIObject::addObjectToParent(TiObject* parent)
{
    TiAPIObject* obj = new TiAPIObject;
    obj->setAttachedObject(parent);
    parent->addMember(obj);
}

void TiAPIObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "debug", this, _debug);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "info", this, _info);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "warn", this, _warn);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "error", this, _error);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "log", this, _log);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "timestamp", this, _timestamp);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "trace", this, _trace);
}

Handle<Value> TiAPIObject::_debug(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with DEBUG severity-level
    TiLogger::getInstance().log("DEBUG", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
    _socket->write(QString("[DEBUG] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());

    return Undefined();
}

Handle<Value> TiAPIObject::_info(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with INFO severity-level
    TiLogger::getInstance().log("INFO", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[INFO] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());
    return Undefined();
}

Handle<Value> TiAPIObject::_warn(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with WARNING severity-level
    TiLogger::getInstance().log("WARN", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[WARN] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());
    return Undefined();
}

Handle<Value> TiAPIObject::_error(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with ERROR severity-level
    TiLogger::getInstance().log("ERROR", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[ERROR] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());
    return Undefined();
}

// log([level], msg)
Handle<Value> TiAPIObject::_log(void* self, TiObject*, const Arguments& args)
{
    HandleScope scope;

    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    TiLogger& logger = TiLogger::getInstance();

    if (args.Length() > 1) {
        logger.log(*String::Utf8Value(args[0]),
                   *String::Utf8Value(args[1]));
    } else {
        // If no log level is provided default to "INFO".
        logger.log("INFO", *String::Utf8Value(args[0]));
    }
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[INFO] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());

    return Undefined();
}

Handle<Value> TiAPIObject::_timestamp(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    TiLogger::getInstance().log("TIMESTAMP", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[TIMESTAMP] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());
    return Undefined();
}

Handle<Value> TiAPIObject::_trace(void* self, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with TRACE severity-level
    TiLogger::getInstance().log("TRACE", *String::Utf8Value(args[0]));
	static_cast<TiAPIObject*>(self)->
	_socket->write(QString("[TRACE] ").append(*String::Utf8Value(args[0])).append("\n").toLocal8Bit().constData());
    return Undefined();
}

