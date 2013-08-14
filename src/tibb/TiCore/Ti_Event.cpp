/*
 * TiEvent.cpp
 *
 *  Created on: Jul 12, 2013
 *      Author: penrique
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
