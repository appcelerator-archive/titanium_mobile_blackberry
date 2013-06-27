/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiHTTPClientObject.h"

#include <QUrl>

#include "NativeHTTPClientObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "NativeException.h"
#include "TiMessageStrings.h"
#include "V8Utils.h"

using namespace titanium;

const static TiProperty g_tiProperties[] =
{
    {
        "allResponseHeaders", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ALLRESPONSEHEADERS
    },

    {
        "autoEncodeUrl", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_AUTOENCODEURL
    },

    {
        "autoRedirect", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_AUTOREDIRECT
    },

    {
        "cache", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_CACHE
    },

    {
        "connected", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_CONNECTED
    },

    {
        "connectionType", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_CONNECTIONTYPE
    },

    {
        "enableKeepAlive", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ENABLEKEEPALIVE
    },

    {
        "file", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_FILE
    },

    {
        "location", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_LOCATION
    },

    {
        "ondatastream", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ONDATASTREAM
    },

    {
        "onerror", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ONERROR
    },

    {
        "onload", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ONLOAD
    },

    {
        "onreadystatechange", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ONREADYSTATECHANGE
    },

    {
        "onsendstream", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_ONSENDSTREAM
    },

    {
        "readyState", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_READYSTATE
    },

    {
        "responseText", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_RESPONSETEXT
    },

    {
        "responseData", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_RESPONSEDATA
    },

    {
        "responseXML", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_RESPONSEXML
    },

    {
        "status", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_STATUS
    },

    {
        "statusText", TI_PROP_PERMISSION_READ, N_HTTPCLIENT_PROP_STATUSTEXT
    },

    {
        "timeout", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_TIMEOUT
    },

    {
        "tlsVersion", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_TLSVERSION
    },

    {
        "validatesSecureCertificate", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_VALIDATESSECURECERTIFICATE
    },

    {
        "withCredentials", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_HTTPCLIENT_PROP_WITHCREDENTIALS
    }

};

TiHTTPClientObject::TiHTTPClientObject()
    : TiProxy("HTTPClient")
{
    objectFactory_ = NULL;
}

TiHTTPClientObject::TiHTTPClientObject(NativeObjectFactory* objectFactory)
    : TiProxy("HTTPClient")
{
    objectFactory_ = objectFactory;
}

TiHTTPClientObject::~TiHTTPClientObject()
{
}

void TiHTTPClientObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
	/*TiHTTPClientObject* obj = new TiHTTPClientObject(objectFactory);
    parent->addMember(obj);
    obj->setAttachedObject(parent);
    obj->release();*/
}

TiHTTPClientObject* TiHTTPClientObject::createHTTPClient(NativeObjectFactory* objectFactory)
{
	TiHTTPClientObject* obj = new TiHTTPClientObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiHTTPClientObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_HTTPCLIENT, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiHTTPClientObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    setTiHTTPClientMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "send", this, _send);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "abort", this, _abort);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearCookies", this, _clearCookies);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setRequestHeader", this, _setRequestHeader);

    // Socket state constant from Titanium.Network.Socket namespace
    ADD_STATIC_TI_VALUE("UNSENT", Number::New(Ti::Network::HTTPClient::HTTPCLIENT_STATE_UNSENT), this);
    ADD_STATIC_TI_VALUE("OPENED", Number::New(Ti::Network::HTTPClient::HTTPCLIENT_STATE_OPENED), this);
    ADD_STATIC_TI_VALUE("HEADERS_RECEIVED", Number::New(Ti::Network::HTTPClient::HTTPCLIENT_STATE_HEADERS_RECEIVED), this);
    ADD_STATIC_TI_VALUE("LOADING", Number::New(Ti::Network::HTTPClient::HTTPCLIENT_STATE_LOADING), this);
    ADD_STATIC_TI_VALUE("DONE", Number::New(Ti::Network::HTTPClient::HTTPCLIENT_STATE_DONE), this);
}

void TiHTTPClientObject::setTiHTTPClientMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueModify, _getValue, this);
        // For all properties that have write permissions, add a setter method, e.g., myLabel.text=<my text>; myLabel.setText(<my text>);
        if (props[i].permissions & TI_PROP_PERMISSION_WRITE)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "set";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertySetFunctionObject::addPropertySetter(this, value, name.c_str());
        }
        // For all properties that have read permissions, add a getter method, e.g., var test=myLabel.text; var test=myLabel.getText();
        if (props[i].permissions & TI_PROP_PERMISSION_READ)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "get";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
        }
        value->release();
    }
}

Handle<Value> TiHTTPClientObject::_getValue(int propertyNumber, void* context)
{
    TiHTTPClientObject* self = (TiHTTPClientObject*) context;
    NativeHTTPClientObject* object = (NativeHTTPClientObject*)self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value, context);
    }
    return value.getValue();
}

VALUE_MODIFY TiHTTPClientObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
	TiHTTPClientObject* self = (TiHTTPClientObject*) context;
	NativeHTTPClientObject* object = (NativeHTTPClientObject*)self->getNativeObject();
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value, self))
    {
    case NATIVE_ERROR_OK:
        modify = VALUE_MODIFY_ALLOW;
        break;
    case NATIVE_ERROR_NOTSUPPORTED:
        modify = VALUE_MODIFY_NOT_SUPPORTED;
        break;
    default:
        modify = VALUE_MODIFY_INVALID;
        break;
    }
    object->release();
    return modify;
}

Handle<Value> TiHTTPClientObject::_open(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiHTTPClientObject* obj = (TiHTTPClientObject*) userContext;
    NativeHTTPClientObject* nhttp = (NativeHTTPClientObject*) obj->getNativeObject();

    // The URL is expected to be valid and percent encoded.
    String::AsciiValue url(args[1]);
    QUrl encodedUrl = QUrl::fromEncoded(QByteArray::fromRawData(*url, url.length()));
    Q_ASSERT(encodedUrl.isValid());

    try {
        nhttp->open(V8ValueToQString(args[0]), encodedUrl);
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiHTTPClientObject::_abort(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiHTTPClientObject* obj = (TiHTTPClientObject*) userContext;
    NativeHTTPClientObject* nhttp = (NativeHTTPClientObject*) obj->getNativeObject();
    try
    {
        nhttp->abort();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiHTTPClientObject::_send(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiHTTPClientObject* obj = (TiHTTPClientObject*) userContext;
    NativeHTTPClientObject* nhttp = (NativeHTTPClientObject*) obj->getNativeObject();

    QString data;
    if (args.Length() > 0) {
        if (args[0]->IsObject()) {
            // Convert objects into form-encoded data.
            QUrl url;
            Local<Object> formData = args[0]->ToObject();
            Local<Array> propertyNames = formData->GetOwnPropertyNames();
            uint32_t propertyCount = propertyNames->Length();
            for (uint32_t i = 0; i < propertyCount; i++) {
                Local<Value> key = propertyNames->Get(i);
                Local<Value> value = formData->Get(key);
                url.addQueryItem(QString::fromUtf8(*String::Utf8Value(key)),
                                 QString::fromUtf8(*String::Utf8Value(value)));
            }
            data = url.toString().mid(1);  // exclude the '?' character
        } else {
            data = QString::fromUtf8(*String::Utf8Value(args[0]));
        }
    }

    try
    {
        nhttp->send(data);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiHTTPClientObject::_setRequestHeader(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiHTTPClientObject* obj = (TiHTTPClientObject*) userContext;
    NativeHTTPClientObject* nhttp = (NativeHTTPClientObject*) obj->getNativeObject();
    try
    {
        nhttp->setRequestHeader(V8ValueToQString(args[0]), V8ValueToQString(args[1]));
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiHTTPClientObject::_clearCookies(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiHTTPClientObject* obj = (TiHTTPClientObject*) userContext;
    NativeHTTPClientObject* nhttp = (NativeHTTPClientObject*) obj->getNativeObject();
    try
    {
        nhttp->clearCookies(V8ValueToQString(args[0]));
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

