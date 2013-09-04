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

Ti::TiEvent::TiEvent(Handle<Function> func) {
	TiHelper::Log("Event Added");
	callback = Persistent<Function>::New(func);
}

Ti::TiEvent::~TiEvent() {
	// Ti::TiHelper::Log("Ti::TiEvent Destroyed!");
	callback.Clear();
	callback.Dispose();
}

void Ti::TiEvent::fireWithParameters(Handle<Object> owner, Ti::TiEventParameters *params)
{

	HandleScope scope;
    Context::Scope context_scope(owner->CreationContext());

	if(owner.IsEmpty())
	{
		Ti::TiHelper::Log("is empty");
		return;
	}
	Handle<Object> obj = Object::New();
	Ti::TiEventParameters::addParametersToObject(params, obj);
	obj->Set(String::New("source"), owner);

	Handle<Value> args[1];
	args[0] = obj;

	Handle<Value> result = callback->Call(owner, 1, args);

    scope.Close(result);
}
