/*
 * TiRuntime.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
 */

#include "Ti_Runtime.h"
#include "Ti_Helper.h"
#include "Ti_Timer.h"
#include "Ti_Constants.h"

static Persistent<Object> _modulesObject;
static Ti::TiRuntime* _instance;
static QMap<QString, Persistent<Value> > _commonJSModules;

static void ThrowJSException(TryCatch tryCatch)
{
	HandleScope scope;
    Context::Scope context_scope(_instance->getGlobalContext());
	Handle<Value> exception = tryCatch.Exception();
    
    qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(exception);
    if(tryCatch.HasCaught())
    {
    	Handle<Message> message = tryCatch.Message();
        
    	Handle<Value> filePath = message->GetScriptResourceName();
    	Handle<Value> sourceLine = message->GetSourceLine();
        
    	qDebug() << "[ERROR] File" << Ti::TiHelper::QStringFromValue(filePath);
    	qDebug() << "[ERROR] Line" << Ti::TiHelper::QStringFromValue(sourceLine);
    }
}

Ti::TiRuntime::TiRuntime(bb::cascades::Application* _app)
: app(_app)
{
	_instance = this;
    HandleScope handle_scope;
    
    globalTemplate = ObjectTemplate::New();
    globalTemplate->Set(String::New("log"), FunctionTemplate::New(Ti::TiHelper::Log));
    globalTemplate->Set(String::New("setTimeout"), FunctionTemplate::New(Ti::TiTimer::SetTimeout));
    globalTemplate->Set(String::New("clearTimeout"), FunctionTemplate::New(Ti::TiTimer::ClearTimeout));
    //    globalTemplate->Set(String::New("setInterval"), FunctionTemplate::New(Ti::TiTimer::SetInterval));
    globalTemplate->Set(String::New("require"), FunctionTemplate::New(Ti::TiRuntime::_require));
    globalTemplate->Set(String::New("_include"), FunctionTemplate::New(Ti::TiRuntime::_include));
    globalTemplate->Set(String::New("__gc__"), FunctionTemplate::New(Ti::TiRuntime::GC));
    
    globalContext = Context::New(NULL, globalTemplate);
    
    Local<Object> obj = globalContext->Global();
    Context::Scope context_scope(globalContext);
    _modulesObject = Persistent<Object>::New(Object::New());
}

Handle<Context> Ti::TiRuntime::getGlobalContext()
{
	return globalContext;
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
    
	for(int i = 0, len = args.Length(); i < len; i++)
	{
		QString filePath = Ti::TiHelper::QStringFromValue(args[i]);
		QFile file(Ti::TiHelper::getAssetPath(filePath));
        
	    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    	QString js = QString(file.readAll().data());
	    	instance->executeString(js, filePath);
	    	file.close();
	    } else {
	    	qDebug() << "[ERROR] Cannot open file" << filePath;
	    }
        
	}
    
	HandleScope scope;
	return scope.Close(Undefined());
}

Handle<Value> Ti::TiRuntime::_require(const Arguments & args)
{
	HandleScope scope;
	Handle<Value> nativeModule = _modulesObject->Get(args[0]);
	if(!nativeModule->IsUndefined())
	{
		return scope.Close(nativeModule);
	}
	QString fileName = Ti::TiHelper::QStringFromValue(args[0]);
	fileName.append(".js");
	QString filePath = Ti::TiHelper::getAssetPath(fileName);    
	if(_commonJSModules.contains(filePath))
	{
		return scope.Close(_commonJSModules.value(filePath));
	}
    
	QFile file(filePath);
	qDebug() << "Trying to require" << filePath;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    	QString js = QString(file.readAll().data());
        
    	js.prepend(
                   "(function () {"
                   "	var module = {\n"
                   "		exports: {}\n"
                   "	};\n"
                   "	var exports = module.exports;\n"
                   );
    	js.append(
                  "	\n"
                  "	return module.exports;\n"
                  "})();\n"
                  );
        
        
    	Handle<Script> script = Script::Compile(Ti::TiHelper::ValueFromQString(js)->ToString() , Ti::TiHelper::ValueFromQString(fileName));
    	qDebug() << "Compiling" << filePath;
    	TryCatch tryCatch;
    	if (script.IsEmpty())
    	{
    		ThrowJSException(tryCatch);
    		return scope.Close(tryCatch.ReThrow());
    	}
    	Persistent<Value> result = Persistent<Value>::New(script->Run());
    	qDebug() << "Running" << filePath;
    	if (result.IsEmpty())
    	{
    		ThrowJSException(tryCatch);
    		return scope.Close(tryCatch.ReThrow());
    	}
    	_commonJSModules.insert(filePath, result);
    	file.close();
    	return scope.Close(result);
    } else {
    	qDebug() << "[ERROR] Cannot open file" << Ti::TiHelper::QStringFromValue(args[0]);
		return scope.Close(Undefined());
    }
	return scope.Close(nativeModule);
    
}

void Ti::TiRuntime::executeString(QString str, QString filePath)
{
	HandleScope scope;
    Context::Scope context_scope(globalContext);
    
    TryCatch tryCatch;
    
    Local<Script> compiledScript  = Script::Compile(
                                                    Ti::TiHelper::ValueFromQString(str)->ToString(),
                                                    Ti::TiHelper::ValueFromQString(filePath)->ToString()
                                                    );
    if(compiledScript.IsEmpty()) {
		ThrowJSException(tryCatch);
        return;
    }
    
    Local<Value> result = compiledScript->Run();
    if(result.IsEmpty()) {
    	ThrowJSException(tryCatch);
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

