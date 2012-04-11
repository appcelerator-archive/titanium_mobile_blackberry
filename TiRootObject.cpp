/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"
#include "TiTitaniumObject.h"

TiRootObject::TiRootObject()
        : TiObject("")
{

}

TiRootObject::~TiRootObject()
{
    if (!context_.IsEmpty())
    {
        context_.Dispose();
    }
}

void TiRootObject::onCreateStaticMembers()
{
    TiObject* ti = TiTitaniumObject::createObject(objectFactory_);
    addMember(ti);
    addMember(ti, "Ti");
}

TiRootObject* TiRootObject::createRootObject()
{
    TiRootObject* obj = new TiRootObject;
    return obj;
}

int TiRootObject::executeScript(NativeObjectFactory* objectFactory, const char* javaScript)
{
    HandleScope handleScope;
    objectFactory_ = objectFactory;
    initializeTiObject (NULL);
    globalTemplate_ = ObjectTemplate::New();
    globalTemplate_->SetInternalFieldCount(2);
    onSetGetPropertyCallback(&globalTemplate_);
    onSetFunctionCallback(&globalTemplate_);
    context_ = Context::New(NULL, globalTemplate_);
    context_->Global()->SetHiddenValue(String::New("globalTemplate_"), External::New(&globalTemplate_));
    setTiObjectToJsObject(context_->Global(), this);
    Context::Scope context_scope(context_);

    TryCatch tryCatch;
    Handle < Script > compiledScript = Script::Compile(String::New(javaScript));
    if (compiledScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        printf("%s\n", *error);
        // TODO: log
        return -1;
    }
    Handle < Value > result = compiledScript->Run();
    if (result.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        printf("%s\n", *error);
        return -1;
    }
    onStartMessagePump();
    return 0;
}

