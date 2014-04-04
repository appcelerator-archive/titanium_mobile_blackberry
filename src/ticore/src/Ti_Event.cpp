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
#include "Ti_ErrorScreen.h"
#include <v8.h>


Ti::TiEvent::TiEvent() {
}

Ti::TiEvent::~TiEvent() {
}

void Ti::TiEvent::AddEventToObject(Handle<Object> proxy, QString eventName, Handle<Function> func)
{
	/*
	 * var eventName = 'click';
	 * var func = function() {};
	 * var eventMap;
	 * var tEventMap = proxy.eventMap;
	 * if(!tEventMap) {
	 * 		eventMap = {};
	 * 		proxy.eventMap = eventMap;
	 * } else {
	 * 		eventMap = tEventMap;
	 * }
	 * var eventArray;
	 * var tEventArray = proxy.eventArray;
	 * if(!tEventArray) {
	 * 		eventArray = [];
	 * 		proxy.eventMap[eventName] = eventArray;
	 * } else {
	 * 		eventArray = tEventArray;
	 * }
	 * eventArray.push(func);
	 */

	Local<Object> eventMap;
	Local<Value> tEventMap = proxy->GetHiddenValue(String::New("eventMap"));
	if(tEventMap.IsEmpty() || tEventMap->IsUndefined()) {
		eventMap = Object::New();
		proxy->SetHiddenValue(String::New("eventMap"), eventMap);
	} else {
		eventMap = tEventMap->ToObject();
	}

	Local<Array> eventArray;
	Local<Value> tEventArray = eventMap->Get(Ti::TiHelper::ValueFromQString(eventName));
	if(tEventArray.IsEmpty() || tEventArray->IsUndefined()) {
		eventArray = Array::New();
		eventMap->Set(Ti::TiHelper::ValueFromQString(eventName), eventArray);
	} else {
		eventArray = Local<Array>::Cast(tEventArray);
	}
	eventArray->Set(eventArray->Length(), func);
}

void Ti::TiEvent::RemoveEventFromObject(Handle<Object> proxy, QString eventName, Handle<Function> func)
{
	Local<Value> tEventMap = proxy->GetHiddenValue(String::New("eventMap"));
	if(tEventMap.IsEmpty() || tEventMap->IsUndefined()) {
		return;
	}
	Local<Value> tEventArray = tEventMap->ToObject()->Get(Ti::TiHelper::ValueFromQString(eventName));
	if(tEventArray.IsEmpty() || tEventArray->IsUndefined()) {
		return;
	}
	Local<Array> eventArray = Local<Array>::Cast(tEventArray);

	for(uint32_t i = 0, len = eventArray->Length(); i < len; i++) {
		Local<Value> v = eventArray->Get(i);
		if(v.IsEmpty() && !v->IsFunction()) continue;
		Local<Function> f = Local<Function>::Cast(v);
		if(func == f) {
			eventArray->Set(i, Undefined());
		}
	}
}


void Ti::TiEvent::FireEventOnObject(Handle<Object> proxy, QString eventName, Ti::TiEventParameters* params)
{
	Local<Value> tEventMap = proxy->GetHiddenValue(String::New("eventMap"));
	if(tEventMap.IsEmpty() || tEventMap->IsUndefined()) {
		return;
	}
	Local<Value> tEventArray = tEventMap->ToObject()->Get(Ti::TiHelper::ValueFromQString(eventName));
	if(tEventArray.IsEmpty() || tEventArray->IsUndefined()) {
		return;
	}
	Local<Array> eventArray = Local<Array>::Cast(tEventArray);

	for(uint32_t i = 0, len = eventArray->Length(); i < len; i++) {

		Local<Value> v = eventArray->Get(i);
		if((v.IsEmpty() && !v->IsFunction()) || v->IsUndefined()) continue;
		Local<Function> func = Local<Function>::Cast(v);
		{
		    TryCatch tryCatch;
		    Local<Object> obj = Object::New();
			Ti::TiEventParameters::addParametersToObject(params, obj);
			obj->Set(String::New("source"), proxy);
			Local<Value> args[] = { obj };
			Local<Value> result = func->Call(proxy, 1, args);
		    if (result.IsEmpty())
		    {
		    	Ti::TiErrorScreen::ShowWithTryCatch(tryCatch);
		    }

		}
	}
}

void Ti::TiEvent::FireCallbackIfNeeded(QString eventName, Handle<Object> owner, Ti::TiEventParameters *params)
{
	HandleScope scope;
    Context::Scope context_scope(owner->CreationContext());
	if(owner->Get(Ti::TiHelper::ValueFromQString(eventName))->IsFunction())
	{
		Handle<Function> callback = Handle<Function>::Cast(owner->Get(Ti::TiHelper::ValueFromQString(eventName)));

		Handle<Object> obj = Object::New();
		Ti::TiEventParameters::addParametersToObject(params, obj);
		obj->Set(String::New("source"), owner);

		Handle<Value> args[1];
		args[0] = obj;
		TryCatch tryCatch;
		Handle<Value> result = callback->Call(owner, 1, args);
		if(result.IsEmpty())
		{
			Ti::TiErrorScreen::ShowWithTryCatch(tryCatch);
		}
	}
}
