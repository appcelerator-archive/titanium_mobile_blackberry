/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiObject.h"
#include <malloc.h>

#define HIDDEN_TI_OBJECT_PROPERTY           "ti_"
#define HIDDEN_TEMP_OBJECT_PROPERTY         "globalTemplate_"

//init with app.js file path
string TiObject::jsFilePath = "app/native/assets/app.js";

TiObject::TiObject()
    : name_(""),
      isInitialized_(false),
      parentObject_(NULL),
      nativeObject_(NULL),
      nativeObjectFactory_(NULL),
      areEventsInitialized_(false)
{
#ifdef _TI_DEBUG_
    cstrName_ = name_.c_str();
    debugMembers_ = "";
    cstrdebugMembers_ = debugMembers_.c_str();
#endif // _TI_DEBUG_
}

TiObject::TiObject(const char* objectName)
    : name_(objectName),
      isInitialized_(false),
      parentObject_(NULL),
      nativeObject_(NULL),
      nativeObjectFactory_(NULL),
      areEventsInitialized_(false)
{
#ifdef _TI_DEBUG_
    cstrName_ = name_.c_str();
    debugMembers_ = "";
    cstrdebugMembers_ = debugMembers_.c_str();
#endif // _TI_DEBUG_
}

TiObject::TiObject(const char* objectName, Handle<Value> value)
    : value_(Persistent<Value>::New(value)),
      name_(objectName),
      isInitialized_(false),
      parentObject_(NULL),
      nativeObject_(NULL),
      nativeObjectFactory_(NULL),
      areEventsInitialized_(false)
{
#ifdef _TI_DEBUG_
    cstrName_ = name_.c_str();
    debugMembers_ = "";
    cstrdebugMembers_ = debugMembers_.c_str();
#endif // _TI_DEBUG_
}

TiObject::~TiObject()
{
    if (!value_.IsEmpty())
    {
        value_.Dispose();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
        nativeObject_ = NULL;
    }
}

char* TiObject::getStringFromObject(Handle<Value> value, const char* defaultString)
{
    char* str = NULL;
    HandleScope handleScope;
    if (value->IsString())
    {
        Handle<String> v8str = Handle<String>::Cast(value);
        String::Utf8Value v8utf8str(v8str);
        str = new char[strlen(*v8utf8str) + 1];
        strcpy(str, *v8utf8str);
    }
    // TODO: complete object "as string"
    /*
     else if(value->IsObject())
     {
     Handle<Object> v8obj=Handle<Object>::Cast(value);

     }
     */
    else
    {
        str = new char[strlen((defaultString == NULL) ? "" : defaultString) + 1];
        strcpy(str, (defaultString == NULL) ? "" : defaultString);

    }
    return str;
}

void TiObject::freeString(char* str)
{
    if (str != NULL)
    {
        delete[] str;
    }
}

TiObject* TiObject::getTiObjectFromJsObject(Handle<Value> value)
{
    if (!value->IsObject())
    {
        return NULL;
    }
    Handle<Object> obj = Handle<Object>::Cast(value);
    Handle<External> ext = Handle<External>::Cast(obj->GetHiddenValue(String::New(HIDDEN_TI_OBJECT_PROPERTY)));
    if (ext.IsEmpty())
    {
        return NULL;
    }
    TiObject* tiObj = (TiObject*) ext->Value();
    return tiObj;
}

void TiObject::setTiObjectToJsObject(Handle<Value> jsObject, TiObject* tiObj)
{
    if (!jsObject->IsObject())
    {
        return;
    }
    Handle<Object> obj = Handle<Object>::Cast(jsObject);
    obj->SetHiddenValue(String::New(HIDDEN_TI_OBJECT_PROPERTY), External::New(tiObj));
}

Handle<ObjectTemplate> TiObject::getObjectTemplateFromJsObject(Handle<Value> value)
{
    HandleScope handleScope;
    Handle<Object> obj = Handle<Object>::Cast(value);
    Handle<Context> context = obj->CreationContext();
    Handle<External> globalTemplateExternal = Handle<External>::Cast(
                context->Global()->GetHiddenValue(String::New(HIDDEN_TEMP_OBJECT_PROPERTY)));
    Handle<ObjectTemplate>temp = *((Handle<ObjectTemplate>*) globalTemplateExternal->Value());
    return handleScope.Close(temp);
}

void TiObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        isInitialized_ = true;
        parentObject_ = parentContext;
        onCreateStaticMembers();
    }
}

Handle<Value> TiObject::onFunctionCall(const Arguments&)
{
    // Default function call returns "Undefined"
    return Undefined();
}

void TiObject::onCreateStaticMembers()
{
    /* Nothing to do in the base class */
}

const char* TiObject::getName() const
{
    return name_.c_str();
}

void TiObject::addMember(TiObject* object, const char* name/*=NULL*/)
{
    HandleScope handleScope;
    map<string, ObjectEntry>::iterator it;
    ObjectEntry entry(object);
    if (name == NULL)
    {
        name = object->getName();
    }
    it = childObjectMap_.find(name);
    if (it != childObjectMap_.end())
    {
        childObjectMap_.erase(it);
    }
    childObjectMap_[name] = entry;
    object->initializeTiObject(this);
#ifdef _TI_DEBUG_
    // This debug code will create a string containing a list of properties and
    // functions. This may be required for Titanium debugging.
    debugMembers_ += "\n";
    debugMembers_ += name;
    cstrdebugMembers_ = debugMembers_.c_str();
#endif
}

Handle<Value> TiObject::getValue() const
{
    HandleScope handleScope;
    return value_;
}

Handle<Value> TiObject::evaluate() const
{
    // TODO: complete this
    HandleScope handleScope;
    return value_;
}

TiObject* TiObject::onLookupMember(const char* memberName)
{
    map<string, ObjectEntry>::iterator it;
    it = childObjectMap_.find(memberName);
    if (it == childObjectMap_.end())
    {
        return NULL;
    }
    TiObject* obj = it->second.getObject();
    return obj;
}

void TiObject::onSetGetPropertyCallback(Handle<ObjectTemplate>* objTemplate)
{
    HandleScope handleScope;
    (*objTemplate)->SetNamedPropertyHandler(_propGetter, _propSetter);
}

void TiObject::onSetFunctionCallback(Handle<ObjectTemplate>* objTemplate)
{
    HandleScope handleScope;
    (*objTemplate)->SetCallAsFunctionHandler(_functCallback);
}

void TiObject::onSetProperty(const char*, Local<Value>)
{
    /* Nothing to do in the base class */
}

void TiObject::onStartMessagePump()
{
    map<string, ObjectEntry>::iterator it;
    for (it = childObjectMap_.begin(); it != childObjectMap_.end(); it++)
    {
        TiObject* obj = it->second.getObject();
        if (obj != NULL)
        {
            obj->onStartMessagePump();
            obj->release();
        }
    }
}

VALUE_MODIFY TiObject::onValueChange(Handle<Value>, Handle<Value>)
{
    return VALUE_MODIFY_ALLOW;
}

VALUE_MODIFY TiObject::onChildValueChange(TiObject*, Handle<Value>, Handle<Value>)
{
    return VALUE_MODIFY_ALLOW;
}

/*
 * setValue calls onValueChange which will determine how
 * the value is handled. If the value VALUE_MODIFY_IGNORE
 * is returned, the value is silently discarded without
 * changing the value of the JavaScript object. This is
 * useful in the case where the value has already been changed
 * by calling forceSetValue in the overridden onValueChange.
 */
VALUE_MODIFY TiObject::setValue(Handle<Value> value)
{
    VALUE_MODIFY modify = onValueChange(value_, value);
    if (modify != VALUE_MODIFY_ALLOW)
    {
        if (modify == VALUE_MODIFY_IGNORE)
        {
            modify = VALUE_MODIFY_ALLOW;
        }
        return modify;
    }
    TiObject* parent = getParentObject();
    if (parent != NULL)
    {
        modify = parent->onChildValueChange(this, value_, value);
        parent->release();
        if (modify != VALUE_MODIFY_ALLOW)
        {
            if (modify == VALUE_MODIFY_IGNORE)
            {
                modify = VALUE_MODIFY_ALLOW;
            }
            return modify;
        }
    }
    value_ = Persistent<Value>::New(value);
    return modify;
}

VALUE_MODIFY TiObject::forceSetValue(Handle<Value> value)
{
    value_ = Persistent<Value>::New(value);
    return VALUE_MODIFY_ALLOW;
}

bool TiObject::userCanAddMember(const char*) const
{
    return true;
}

Handle<Value> TiObject::_propGetter(Local<String> prop, const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle<Object> result;
    TiObject* obj = getTiObjectFromJsObject(info.Holder());
    if (obj == NULL)
    {
        // Returns "empty". This will cause V8 to go back to default lookup.
        return result;
    }
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(info.Holder());
    String::Utf8Value propName(prop);
    const char* propString = (const char*)(*propName);
    TiObject* propObject = obj->onLookupMember(propString);
    if (propObject == NULL)
    {
        // TODO: Fix the following block of commented out code. Currently it breaks
        // Titanium runtime.
        /*
        if(obj->canAddMembers())
        {
            // If we're allowed to add members, return an "empty" result
            // so V8 will handle it. V8 will set the value internally so
            // we can ignore non-Titanium objects.
            return result;
        }
        */
        return Handle<Value>();
    }
    Handle<Value> ret = propObject->getValue();
    if (!ret.IsEmpty())
    {
        return handleScope.Close(ret);
    }
    if ((propObject->hasMembers()) || (propObject->isFunction()))
    {
        result = global->NewInstance();
        propObject->setValue(result);
        setTiObjectToJsObject(result, propObject);
    }
    else
    {
        propObject->release();
        return handleScope.Close(propObject->getValue());
    }
    propObject->release();
    return handleScope.Close(result);
}

Handle<Value> TiObject::_propSetter(Local<String> prop, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle<Object> result;
    TiObject* obj = getTiObjectFromJsObject(info.Holder());
    if (obj == NULL)
    {
        // We are not tracking this object so let V8 handle it.
        info.Holder()->ForceSet(prop, value);
        return value;
    }
    String::Utf8Value propName(prop);
    const char* propString = (const char*)(*propName);
    return obj->setPropHelper(propString, value, &TiObject::setValue);
}

void TiObject::forceSetProp(const char* propString, Local<Value> value)
{
    setPropHelper(propString, value, &TiObject::forceSetValue);
}

Handle<Value> TiObject::setPropHelper(const char* propString, Local<Value> value, SET_VALUE_CALLBACK cb)
{
    TiObject* destObj = onLookupMember(propString);
    TiObject* srcObj = getTiObjectFromJsObject(value);
    if (srcObj == NULL)
    {
        srcObj = new TiObject(propString);
        srcObj->initializeTiObject(NULL);
        srcObj->setValue(value);
        setTiObjectToJsObject(value, srcObj);
    }
    if (destObj == NULL)
    {
        if ((!canAddMembers()) || (!userCanAddMember(propString)))
        {
            srcObj->release();
            return Undefined();
        }
        destObj = srcObj;
    }
    (destObj->*cb)(value);
    setTiObjectToJsObject(value, destObj);
    addMember(destObj, propString);
    onSetProperty(propString, value);
    srcObj->release();
    return value;
}

Handle<Value> TiObject::_functCallback(const Arguments& args)
{
    HandleScope handleScope;
    TiObject* obj = getTiObjectFromJsObject(args.Holder());
    if (obj == NULL)
    {
        return Undefined();
    }
    return handleScope.Close(obj->onFunctionCall(args));
}

bool TiObject::hasMembers() const
{
    return (childObjectMap_.empty() ? false : true);
}

bool TiObject::isFunction() const
{
    return false;
}

bool TiObject::canAddMembers() const
{
    return true;
}

bool TiObject::isInitialized() const
{
    return isInitialized_;
}

bool TiObject::isUIObject() const
{
    return false;
}

void TiObject::setTiMappingProperties(const TiProperty*, int)
{
}

TiObject* TiObject::getParentObject() const
{
    if (parentObject_ != NULL)
    {
        parentObject_->addRef();
    }
    return parentObject_;
}

NativeObjectFactory* TiObject::getNativeObjectFactory() const
{
    return nativeObjectFactory_;
}

NativeObject* TiObject::getNativeObject() const
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->addRef();
    }
    return nativeObject_;
}

void TiObject::setNativeObject(NativeObject* nativeObject)
{
    if (nativeObject != NULL)
    {
        nativeObject->addRef();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
    }
    nativeObject_ = nativeObject;
}

void TiObject::setupEvents()
{
    if (!areEventsInitialized_)
    {
        onSetupEvents();
        areEventsInitialized_ = true;
    }
}

void TiObject::onSetupEvents()
{
    NativeObject* nativeObject = getNativeObject();
    if (nativeObject != NULL)
    {
        nativeObject->completeInitialization();
        nativeObject->release();
    }
}

void TiObject::setNativeObjectFactory(NativeObjectFactory* objectFactory)
{
    nativeObjectFactory_ = objectFactory;
}

ObjectEntry::ObjectEntry()
{
    obj_ = NULL;
    userContext_ = NULL;
}

ObjectEntry::ObjectEntry(const ObjectEntry& entry)
{
    if (entry.obj_ != NULL)
    {
        entry.obj_->addRef();
    }
    obj_ = entry.obj_;
}

ObjectEntry::ObjectEntry(TiObject* obj)
{
    if (obj != NULL)
    {
        obj->addRef();
    }
    obj_ = obj;
}

ObjectEntry::~ObjectEntry()
{
    if (obj_ != NULL)
    {
        obj_->release();
        obj_ = NULL;
    }
}

const ObjectEntry& ObjectEntry::operator =(const ObjectEntry& entry)
{
    if (entry.obj_ != NULL)
    {
        entry.obj_->addRef();
    }
    if (obj_ != NULL)
    {
        obj_->release();
    }
    obj_ = entry.obj_;
    return (*this);
}

TiObject* ObjectEntry::getObject() const
{
    if (obj_ != NULL)
    {
        obj_->addRef();
    }
    return obj_;
}

TiObject* ObjectEntry::operator ->() const
{
    return obj_;
}

bool ObjectEntry::isSameInstance(const TiObject* obj) const
{
    return obj == obj_;
}
