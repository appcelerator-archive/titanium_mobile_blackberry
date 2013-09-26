/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Runtime.h"
#include "Ti_Helper.h"
#include "Ti_Timer.h"
#include "Ti_Constants.h"

static 	Persistent<Object> _modulesObject;
static Ti::TiRuntime* _instance;

Ti::TiRuntime::TiRuntime(bb::cascades::Application* _app)
: app(_app)
{
	_instance = this;
    HandleScope handle_scope;

    globalTemplate = ObjectTemplate::New();
    globalTemplate->Set(String::New("log"), FunctionTemplate::New(Ti::TiHelper::Log));
    globalTemplate->Set(String::New("setTimeout"), FunctionTemplate::New(Ti::TiTimer::SetTimeout));
//    globalTemplate->Set(String::New("setInterval"), FunctionTemplate::New(Ti::TiTimer::SetInterval));
    globalTemplate->Set(String::New("require"), FunctionTemplate::New(Ti::TiRuntime::_require));
    globalTemplate->Set(String::New("_include"), FunctionTemplate::New(Ti::TiRuntime::_include));
    globalTemplate->Set(String::New("__gc__"), FunctionTemplate::New(Ti::TiRuntime::GC));

    globalContext = Context::New(NULL, globalTemplate);

    Local<Object> obj = globalContext->Global();
    Context::Scope context_scope(globalContext);
    _modulesObject = Persistent<Object>::New(Object::New());
}

void Ti::TiRuntime::registerModule(QString name, ModuleStartup module)
{
	qDebug() << "[INFO] Registering module " << name;
	HandleScope scope;
    Context::Scope context_scope(globalContext);
	_modulesObject->Set(Ti::TiHelper::ValueFromQString(name), module());
}

Handle<Value> Ti::TiRuntime::GC(const Arguments &)
{
	HandleScope scope;
	V8::LowMemoryNotification();
	Ti::TiHelper::Log("----- Force GC ------");
	return Undefined();
}

Handle<Value> Ti::TiRuntime::_include(const Arguments & args)
{
	Ti::TiRuntime* instance = Ti::TiRuntime::Instance();
	QString resources = Ti::TiConstants::ResourcesDir;

	for(int i = 0, len = args.Length(); i < len; i++)
	{
		QString fileName = Ti::TiHelper::QStringFromValue(args[i]);
		QFile file(fileName.prepend(resources.append("/")).replace("//", "/"));

	    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    	QString js = QString(file.readAll().data());
	    	instance->executeString(js, fileName);
	    	file.close();
	    } else {
	    	qDebug() << "[ERROR] Cannot open file" << fileName;
	    }

	}

	HandleScope scope;
	return scope.Close(Undefined());
}

Handle<Value> Ti::TiRuntime::_require(const Arguments & args)
{
	HandleScope scope;
	return scope.Close(_modulesObject->Get(args[0]));
}

void Ti::TiRuntime::executeString(QString str, QString fileName)
{
	HandleScope scope;
    Context::Scope context_scope(globalContext);

    TryCatch tryCatch;

    Local<Script> compiledScript  = Script::Compile(
    		Ti::TiHelper::ValueFromQString(str)->ToString(),
    		Ti::TiHelper::ValueFromQString(fileName)->ToString()
    );
    if(compiledScript.IsEmpty()) {
    	Handle<Value> exception = tryCatch.Exception();
    	Handle<Message> message = tryCatch.Message();
        int lineNumber = message->GetLineNumber();
        Handle<Value> fileName = message->GetScriptResourceName();
        Handle<Value> sourceLine = message->GetSourceLine();
    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(exception);
    	qDebug() << "[ERROR] Line" << lineNumber << "File" << Ti::TiHelper::QStringFromValue(fileName);
    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(sourceLine);
        return;
    }

    Local<Value> result = compiledScript->Run();
    if(result.IsEmpty()) {
    	Handle<Value> exception = tryCatch.Exception();
        Handle<Message> message = tryCatch.Message();
        int lineNumber = message->GetLineNumber();
        Handle<Value> fileName = message->GetScriptResourceName();
        Handle<Value> sourceLine = message->GetSourceLine();
    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(exception);
    	qDebug() << "[ERROR] Line" << lineNumber << "File" << Ti::TiHelper::QStringFromValue(fileName);
    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(sourceLine);
        return;
    }

}


int Ti::TiRuntime::start() {
	return app->exec();
}
Ti::TiRuntime* Ti::TiRuntime::Instance()
{
	return _instance;
}

Ti::TiRuntime::~TiRuntime()
{
	_instance = NULL;
	_modulesObject.Dispose();
}

