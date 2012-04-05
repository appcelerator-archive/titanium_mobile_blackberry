/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"

TiUIBase::TiUIBase()
{
    cascadesApp_=NULL;
    container_=NULL;
}

TiUIBase::~TiUIBase()
{
	if(!createConfig_.IsEmpty())
	{
		createConfig_.Dispose();
	}
}

TiUIBase::TiUIBase(TiCascadesApp& app,const char* name):
        TiObject(name)
{
    cascadesApp_=&app;
    container_=NULL;
}

TiCascadesApp* TiUIBase::getCascadesApp() const
{
    return cascadesApp_;
}

void TiUIBase::onSetProperty(const char* propertyName,Local<Value> value)
{
    char* str=TiObject::getStringFromObject(value,"");
    if(strcmpi(propertyName,"backgroundColor")==0)
    {
        onSetBackgroundColor(str);
    }
    TiObject::freeString(str);
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

UIHANDLE TiUIBase::getContainerHandle() const
{
    return container_;
}

void TiUIBase::setContainerHandle(UIHANDLE container)
{
    container_=container;
}

void TiUIBase::setParametersFromObject(Local<Object> obj)
{
    HandleScope handleScope;
	Local<Value> value;
	char* str;
	value=obj->Get(String::New("backgroundColor"));
	if(!value.IsEmpty())
	{
		str=TiObject::getStringFromObject(value,"#000");
		onSetBackgroundColor(str);
		TiObject::freeString(str);
	}
}

void TiUIBase::onSetBackgroundColor(const char* color)
{
    getCascadesApp()->setBackgroundColor(getContainerHandle(),color);
}

Handle<Value> TiUIBase::setBackgroundColor_(void* userContext,
                                            TiObject* caller,
                                            const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj=(TiUIBase*)userContext;
    if(args.Length()<1)
    {
        // TODO: throw an exception
        return Undefined();
    }
    if(args[0]->IsString())
    {
        Handle < String > colStr=Handle<String>::Cast(args[0]);
        String::Utf8Value utfColStr(colStr);
        const char* c=(const char*)(*utfColStr);
        obj->onSetBackgroundColor(c);
    }
    else
    {
        // TODO: throw an exception
        return Undefined();
    }
    return Undefined();
}

