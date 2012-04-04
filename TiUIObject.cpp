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
    TiGenericFunctionObject::addGenericFunctionToParent(this,
                                                        "setBackgroundColor",
                                                        this,
                                                        setBackgroundColor_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTabGroup",
                                                        this, createTabGroup_);
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
    unsigned int col;
    if(args[0]->IsString())
    {
        Handle < String > colStr=Handle<String>::Cast(args[0]);
        String::Utf8Value utfColStr(colStr);
        const char* c=(const char*)(*utfColStr);
        obj->cascadesApp_->setBackgroundColor(c);
    }
    else if(args[0]->IsNumber())
    {
        Handle<Number> colInt=Handle<Number>::Cast(args[0]);
        col=colInt->Value();
        obj->cascadesApp_->setBackgroundColor(col);
    }
    else
    {
        // TODO: throw an exception
        return Undefined();
    }
    return Undefined();
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller,
                                          const Arguments& args)
{
    return Undefined();
}
