/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiUtility.h"
#include "TiCascadesApp.h"
#include "TiUIWindow.h"
#include <string.h>

TiUIObject::TiUIObject()
        : TiObject("UI")
{
    cascadesApp_=NULL;
}

TiUIObject::TiUIObject(TiCascadesApp& cascadesApp):TiObject("UI")
{
    cascadesApp_=&cascadesApp;
}

TiUIObject::~TiUIObject()
{
}

void TiUIObject::addObjectToParent(TiObject* parent,TiCascadesApp& cascadesApp)
{
    TiUIObject* obj = new TiUIObject(cascadesApp);
    parent->addMember(obj);
    obj->release();
}

void TiUIObject::onCreateStaticMembers()
{

    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTabGroup",
                                                        this, createTabGroup_);
    TiGenericFunctionObject::addGenericFunctionToParent(this,
                                                        "createWindow",this,createWindow_);
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller,
                                          const Arguments& args)
{
    return Undefined();
}

Handle<Value> TiUIObject::setBackgroundColor_(void* userContext,
                                            TiObject* caller,
                                            const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj=(TiUIObject*)userContext;
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
        obj->cascadesApp_->setBackgroundColor(NULL,c);
    }
    else
    {
        // TODO: throw an exception
        return Undefined();
    }
    return Undefined();
}

Handle<Value> TiUIObject::createWindow_(void* userContext, TiObject* caller,
                                        const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj=(TiUIObject*)userContext;
    Handle < Context > context = args.Holder()->CreationContext();
    Handle < External > globalTemplate =
            Handle < External
            > ::Cast(
                    context->Global()->GetHiddenValue(
                            String::New("globalTemplate_")));
    Handle < ObjectTemplate > *global =
            (Handle<ObjectTemplate>*) (globalTemplate->Value());
    Handle < Object > result;
    result=(*global)->NewInstance();
    TiUIWindow* wnd=TiUIWindow::createWindow(*(obj->cascadesApp_),"");
	if((args.Length()>0)&&(args[0]->IsObject()))
	{
		Local<Object> settingsObj=Local<Object>::Cast(args[0]);
		wnd->setParametersFromObject(settingsObj);
	}
    result->SetHiddenValue(String::New("ti_"), External::New(wnd));
    return handleScope.Close(result);
}

