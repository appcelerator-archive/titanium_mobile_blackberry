/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/system/Clipboard>

#include "TiBlobObject.h"
#include "TiGenericFunctionObject.h"
#include "TiMessageStrings.h"
#include "TiUIClipboardObject.h"

using namespace bb::system;

TiUIClipboardObject::TiUIClipboardObject()
    : TiProxy("Clipboard") {
}

TiUIClipboardObject::~TiUIClipboardObject() {
}

void TiUIClipboardObject::addObjectToParent(TiObject* parent, NativeObjectFactory* factory) {
    TiUIClipboardObject* obj = new TiUIClipboardObject();
    obj->setNativeObjectFactory(factory);
    parent->addMember(obj);
    obj->release();
}

void TiUIClipboardObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "getData", this, _getData);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getText", this, _getText);
}

Handle<Value> TiUIClipboardObject::clipboardData(const QString& type) const {
    HandleScope scope;
    Clipboard clipboard;

    QByteArray data = clipboard.value(type, 0);
    if (data.isEmpty()) {
        return Undefined();
    }

    if (type == "text/plain") {
        return String::New(data.constData(), data.size());
    }

    // Create a new blob to wrap the clipboard data.
    TiBlobObject* blob = TiBlobObject::createBlob(getNativeObjectFactory());
    Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(getValue());
    Local<Object> proxy = templ->NewInstance();
    blob->setValue(proxy);
    TiObject::setTiObjectToJsObject(proxy, blob);
    blob->setData(data, type);

    return scope.Close(proxy);
}

Handle<Value> TiUIClipboardObject::_getData(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    TiUIClipboardObject* self = static_cast<TiUIClipboardObject*>(userContext);

    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    Local<String> type = args[0]->ToString();
    Handle<Value> data = self->clipboardData(TiObject::getStringFromValue(type));

    return scope.Close(data);
}

Handle<Value> TiUIClipboardObject::_getText(void* userContext, TiObject* caller, const Arguments& args) {
    TiUIClipboardObject* self = static_cast<TiUIClipboardObject*>(userContext);
    return self->clipboardData("text/plain");
}

