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
#include "V8Utils.h"

using namespace bb::system;
using namespace titanium;

#define MIME_TEXT_PLAIN "text/plain"

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

    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearData", this, _clearData);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearText", this, _clearText);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getData", this, _getData);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getText", this, _getText);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hasData", this, _hasData);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hasText", this, _hasText);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setData", this, _setData);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setText", this, _setText);
}

Handle<Value> TiUIClipboardObject::getData(const QString& type) const {
    HandleScope scope;
    Clipboard clipboard;

    QByteArray data = clipboard.value(type, 0);
    if (data.isEmpty()) {
        return Undefined();
    }

    if (type == MIME_TEXT_PLAIN) {
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

Handle<Value> TiUIClipboardObject::_clearData(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    Clipboard clipboard;

    if (args.Length() == 0) {
        clipboard.clear();
    } else {
        QString type = V8ValueToQString(args[0]);
        clipboard.remove(type);
    }

    return Undefined();
}

Handle<Value> TiUIClipboardObject::_clearText(void* userContext, TiObject* caller, const Arguments& args) {
    Clipboard clipboard;
    clipboard.remove(MIME_TEXT_PLAIN);
    return Undefined();
}

Handle<Value> TiUIClipboardObject::_getData(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    TiUIClipboardObject* self = static_cast<TiUIClipboardObject*>(userContext);

    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    QString type = V8ValueToQString(args[0]);
    Handle<Value> data = self->getData(type);

    return scope.Close(data);
}

Handle<Value> TiUIClipboardObject::_getText(void* userContext, TiObject* caller, const Arguments& args) {
    TiUIClipboardObject* self = static_cast<TiUIClipboardObject*>(userContext);
    return self->getData(MIME_TEXT_PLAIN);
}

Handle<Value> TiUIClipboardObject::_hasData(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    Clipboard clipboard;

    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    QString type = V8ValueToQString(args[0]);
    return clipboard.contains(type, 0) ? True() : False();
}

Handle<Value> TiUIClipboardObject::_hasText(void* userContext, TiObject* caller, const Arguments& args) {
    Clipboard clipboard;
    return clipboard.contains(MIME_TEXT_PLAIN, 0) ? True() : False();
}

Handle<Value> TiUIClipboardObject::_setData(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    Clipboard clipboard;

    if (args.Length() < 2) {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    Local<Value> dataValue = args[1];
    QByteArray data;
    if (dataValue->IsObject()) {
        // Insert data from a blob object.
        TiObject* object = TiObject::getTiObjectFromJsObject(dataValue);
        if (object && strcmp(object->getName(), "Blob") == 0) {
            data = static_cast<TiBlobObject*>(object)->data();
        }
    } else {
        // Convert and insert data as a string.
      String::Utf8Value uf8Str(dataValue);
      data = QByteArray(*uf8Str, uf8Str.length());
    }

    QString type = V8ValueToQString(args[0]);
    clipboard.insert(type, data);

    return Undefined();
}

Handle<Value> TiUIClipboardObject::_setText(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    Clipboard clipboard;

    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    String::Utf8Value text(args[0]);
    QByteArray data = QByteArray::fromRawData(*text, text.length());
    clipboard.insert(MIME_TEXT_PLAIN, data);

    return Undefined();
}

