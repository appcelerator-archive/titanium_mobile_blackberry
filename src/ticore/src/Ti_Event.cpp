/*
 * TiEvent.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Event.h"
#include "Ti_EventParameters.h"
#include "Ti_Constants.h"

Ti::TiEvent::TiEvent(Handle<Function> func) {
	TiHelper::Log("Event Added");
	callback = Persistent<Function>::New(func);
}

Ti::TiEvent::~TiEvent() {
	// Ti::TiHelper::Log("Ti::TiEvent Destroyed!");
	callback.Clear();
	callback.Dispose();
}

void Ti::TiEvent::fireCallbackIfNeeded(QString eventName, Handle<Object> owner, Ti::TiEventParameters *params)
{
	HandleScope scope;
    Context::Scope context_scope(owner->CreationContext());
	if(owner->Get(Ti::TiHelper::ValueFromQString(eventName))->IsFunction())
	{
		Handle<Function> callback = Handle<Function>::Cast(owner->Get(Ti::TiHelper::ValueFromQString(eventName)));

		Handle<Object> obj = Object::New();
		if(!params->contains(Ti::TiConstants::EventType)) {
			params->addParam(Ti::TiConstants::EventType, eventName);
		}
		Ti::TiEventParameters::addParametersToObject(params, obj);
		obj->Set(String::New("source"), owner);

		Handle<Value> args[1];
		args[0] = obj;
		TryCatch tryCatch;
		Handle<Value> result = callback->Call(owner, 1, args);
		if(result.IsEmpty())
		{
			qDebug() << "[TIEVENT] Something bad happened";

	    	Handle<Value> exception = tryCatch.Exception();
	    	Handle<Message> message = tryCatch.Message();
	        int lineNumber = message->GetLineNumber();
	        Handle<Value> fileName = message->GetScriptResourceName();
	        Handle<Value> sourceLine = message->GetSourceLine();
	    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(exception);
	    	qDebug() << "[ERROR] Line" << lineNumber << "File" << Ti::TiHelper::QStringFromValue(fileName);
	    	qDebug() << "[ERROR] " << Ti::TiHelper::QStringFromValue(sourceLine);
		}

	}

}

void Ti::TiEvent::fireWithParameters(QString eventName, Handle<Object> owner, Ti::TiEventParameters *params)
{
	HandleScope scope;
	if(owner.IsEmpty())
	{
		Ti::TiHelper::Log("is empty");
		return;
	}
    Context::Scope context_scope(owner->CreationContext());
	Handle<Object> obj = Object::New();
	if(!params->contains(Ti::TiConstants::EventType)) {
		params->addParam(Ti::TiConstants::EventType, eventName);
	}
	Ti::TiEventParameters::addParametersToObject(params, obj);
	obj->Set(String::New("source"), owner);

	Handle<Value> args[1];
	args[0] = obj;

	Handle<Value> result = callback->Call(owner, 1, args);

    scope.Close(result);
}
