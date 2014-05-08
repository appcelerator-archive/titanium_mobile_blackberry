
#include "Ti_Constants.h"
#include "Ti_Proxy.h"
#include "Ti_Value.h"
#include "Ti_EventParameters.h"
#include "Ti_Callback.h"
#include "Ti_ErrorScreen.h"

#include "TitaniumRuntime.h"

namespace Ti
{

TiCallback::TiCallback(Ti::TiProxy* proxy, Ti::TiValue val)
{
	HandleScope scope;
	_proxy = proxy;
	Local<Value> hiddenValue = proxy->_jsObject->GetHiddenValue(String::New("callbacks"));
	Local<Array> callbacks;
	if(hiddenValue.IsEmpty() || hiddenValue->IsUndefined())
	{
		callbacks = Array::New();
		proxy->_jsObject->SetHiddenValue(String::New("callbacks"), callbacks);
	}
	else
	{
		callbacks = Local<Array>::Cast(hiddenValue);
	}
	_id = callbacks->Length();
	callbacks->Set(_id, Handle<Function>::Cast(val.toJSValue()));
}
TiCallback::~TiCallback()
{
	Local<Array> callbacks = Local<Array>::Cast(_proxy->_jsObject->GetHiddenValue(String::New("callbacks")));
	callbacks->Set(_id, Null());
}
void TiCallback::fire(Ti::TiEventParameters params)
{
	HandleScope scope;
	Context::Scope context_scope(TitaniumRuntime::getContenxt());

	TryCatch tryCatch;

	Local<Array> callbackArray = Local<Array>::Cast(_proxy->_jsObject->GetHiddenValue(String::New("callbacks")));
	Local<Function> callbackFunction = Local<Function>::Cast(callbackArray->Get(_id));
	Local<Object> eventObject = Object::New();
	Ti::TiEventParameters::addParametersToObject(&params, eventObject);

	eventObject->Set(String::New("source"), _proxy->_jsObject);
	Local<Value> args[] = { eventObject };
	Local<Value> result = callbackFunction->Call(_proxy->_jsObject, 1, args);
	if (result.IsEmpty())
	{
		Ti::TiErrorScreen::ShowWithTryCatch(tryCatch);
	}
}
}
