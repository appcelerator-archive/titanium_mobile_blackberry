/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBufferObject.h"

#include "TiBlobObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiMessageStrings.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "NativeBufferObject.h"
#include "NativeException.h"

const static TiProperty g_tiProperties[] =
{
    {
        "byteOrder", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_BYTEORDER
    },

    {
        "length", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_BUFFER_PROP_LENGTH
    },

    {
        "type", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_TYPE
    },

    {
        "value", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_VALUE
    }
};


TiBufferObject::TiBufferObject()
    : TiProxy("Buffer")
{
}

TiBufferObject::~TiBufferObject()
{
}

void TiBufferObject::addObjectToParent(TiObject* parent)
{
    TiBufferObject* obj = new TiBufferObject;
    obj->setAttachedObject(parent);
    parent->addMember(obj);
}

TiBufferObject* TiBufferObject::createBuffer(NativeObjectFactory* objectFactory)
{
    TiBufferObject* obj = new TiBufferObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiBufferObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_BUFFER, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiBufferObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "append", this, _append);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "copy", this, _copy);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fill", this, _fill);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "insert", this, _insert);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clone", this, _clone);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clear", this, _clear);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "toString", this, _toString);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "release", this, _release);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "toBlob", this, _toBlob);
}

Handle<Value> TiBufferObject::_append(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();

    NativeBufferObject* nboSource = NULL;
    if (args[0]->IsObject())
    {
        TiBufferObject* objSource = (TiBufferObject*) getTiObjectFromJsObject(args[0]);
        nboSource = (NativeBufferObject*) objSource->getNativeObject();
    }

    // Invalid argument passed
    if (nboSource == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Optional arguments provided
    int sourceOffset = -1, sourceLength = -1;
    if (args.Length() > 1)
    {
        // Should provided both sourceOffset and sourceLength
        if (args.Length() < 3)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> sourceOffsetNum = Handle<Number>::Cast(args[1]);
        Handle<Number> sourceLengthNum = Handle<Number>::Cast(args[2]);
        sourceOffset = (int)sourceOffsetNum->Value();
        sourceLength = (int)sourceLengthNum->Value();
    }

    int bytesWritten = 0;
    try
    {
        bytesWritten = nbo->append(nboSource, sourceOffset, sourceLength);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    Handle<Number> result = Number::New(bytesWritten);
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_copy(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    // Required sourceBuffer and offset
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();

    NativeBufferObject* nboSource = NULL;
    if (args[0]->IsObject())
    {
        TiBufferObject* objSource = (TiBufferObject*) getTiObjectFromJsObject(args[0]);
        nboSource = (NativeBufferObject*) objSource->getNativeObject();
    }

    // Invalid argument passed
    if (nboSource == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Get the offset parameter
    Handle<Number> offsetNum = Handle<Number>::Cast(args[1]);
    if (offsetNum.IsEmpty() || (!offsetNum->IsNumber() && !offsetNum->IsNumberObject()))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Optional arguments provided
    int sourceOffset = -1, sourceLength = -1;
    if (args.Length() > 2)
    {
        // Should provided both sourceOffset and sourceLength
        if (args.Length() < 4)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> sourceOffsetNum = Handle<Number>::Cast(args[2]);
        Handle<Number> sourceLengthNum = Handle<Number>::Cast(args[3]);
        sourceOffset = (int)sourceOffsetNum->Value();
        sourceLength = (int)sourceLengthNum->Value();
    }

    int bytesWritten = 0;
    try
    {
        bytesWritten = nbo->copy(nboSource, offsetNum->Value(), sourceOffset, sourceLength);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    Handle<Number> result = Number::New(bytesWritten);
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_fill(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();

    Handle<Number> fillByteNum = Handle<Number>::Cast(args[0]);
    if (fillByteNum.IsEmpty() || (!fillByteNum->IsNumber() && !fillByteNum->IsNumberObject()))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    int offset = -1, length = -1;
    if (args.Length() > 1)
    {
        // Should provided both offset and length
        if (args.Length() < 3)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> offsetNum = Handle<Number>::Cast(args[1]);
        Handle<Number> lengthNum = Handle<Number>::Cast(args[2]);
        offset = (int)offsetNum->Value();
        length = (int)lengthNum->Value();
    }

    try
    {
        nbo->fill(fillByteNum->Value(), offset, length);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiBufferObject::_insert(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    // Required sourceBuffer and offset
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();

    NativeBufferObject* nboSource = NULL;
    if (args[0]->IsObject())
    {
        TiBufferObject* objSource = (TiBufferObject*) getTiObjectFromJsObject(args[0]);
        nboSource = (NativeBufferObject*) objSource->getNativeObject();
    }

    // Invalid argument passed
    if (nboSource == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Get the offset parameter
    Handle<Number> offsetNum = Handle<Number>::Cast(args[1]);
    if (offsetNum.IsEmpty() || (!offsetNum->IsNumber() && !offsetNum->IsNumberObject()))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Optional arguments provided
    int sourceOffset = -1, sourceLength = -1;
    if (args.Length() > 2)
    {
        // Should provided both sourceOffset and sourceLength
        if (args.Length() < 4)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> sourceOffsetNum = Handle<Number>::Cast(args[2]);
        Handle<Number> sourceLengthNum = Handle<Number>::Cast(args[3]);
        sourceOffset = (int)sourceOffsetNum->Value();
        sourceLength = (int)sourceLengthNum->Value();
    }

    int bytesWritten = 0;
    try
    {
        bytesWritten = nbo->insert(nboSource, offsetNum->Value(), sourceOffset, sourceLength);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }

    Handle<Number> result = Number::New(bytesWritten);
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_clone(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();

    int offset = -1, length = -1;
    if (args.Length() > 0)
    {
        // Should provided both offset and length
        if (args.Length() < 2)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> offsetNum = Handle<Number>::Cast(args[1]);
        Handle<Number> lengthNum = Handle<Number>::Cast(args[2]);
        offset = (int)offsetNum->Value();
        length = (int)lengthNum->Value();
    }

    // Create new Ti.Buffer
    NativeObjectFactory* factory = obj->getNativeObjectFactory();
    TiBufferObject* newBuffer = createBuffer(factory);
    NativeBufferObject* cloneBuffer = NULL;
    try
    {
        cloneBuffer = nbo->clone(newBuffer, offset, length);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(obj->getValue());
    newBuffer->setNativeObject(cloneBuffer);
    cloneBuffer->release();
    Handle<Object> result = global->NewInstance();
    setTiObjectToJsObject(result, newBuffer);
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_clear(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();
    nbo->clear();
    return Undefined();
}

Handle<Value> TiBufferObject::_toString(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();
    const char* data = nbo->toString();
    Handle<String> result = String::New(data);
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_release(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    return ThrowException(String::New(Ti::Msg::Not_implemented));
}

Handle<Value> TiBufferObject::_toBlob(void* userContext, TiObject* caller, const Arguments& args) {
    HandleScope scope;
    TiBufferObject* buffer = static_cast<TiBufferObject*>(userContext);

    // Create a new empty blob instance.
    TiBlobObject* blob = TiBlobObject::createBlob(buffer->getNativeObjectFactory());
    Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(buffer->getValue());
    Local<Object> proxy = templ->NewInstance();
    blob->setValue(proxy);
    TiObject::setTiObjectToJsObject(proxy, blob);

    // Initialize the blob with the buffer's data.
    blob->setData(static_cast<NativeBufferObject*>(buffer->getNativeObject())->data(),
                  "application/octet-stream");

    return scope.Close(proxy);
}

