/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiObject.h"
#include <malloc.h>

#define HIDDEN_TI_OBJECT_PROPERTY			"ti_"
#define HIDDEN_TEMP_OBJECT_PROPERTY         "globalTemplate_"

TiObject::TiObject()
{
    refCount_ = 1;
    name_ = NULL;
    childObject_ = NULL;
    childObjectCount_ = 0;
    hasInitialized_ = false;
    parentObject_ = NULL;
}

TiObject::TiObject(const char* objectName)
{
    refCount_ = 1;
    name_ = new char[strlen((objectName == NULL) ? "" : objectName) + 1];
    strcpy(name_, (objectName == NULL) ? "" : objectName);
    childObject_ = NULL;
    childObjectCount_ = 0;
    if (!value_.IsEmpty())
    {
        value_.Dispose();
    }
    hasInitialized_ = false;
    parentObject_ = NULL;
}

TiObject::TiObject(const char* objectName, Handle<Value> value)
{
    refCount_ = 1;
    name_ = new char[strlen((objectName == NULL) ? "" : objectName) + 1];
    strcpy(name_, (objectName == NULL) ? "" : objectName);
    childObject_ = NULL;
    childObjectCount_ = 0;
    value_ = Persistent < Value > ::New(value);
    parentObject_ = NULL;
}

TiObject::~TiObject()
{
    if (name_ != NULL)
    {
        delete[] name_;
        name_ = NULL;
    }
    int i;
    for (i = 0; i < childObjectCount_; i++)
    {
        delete childObject_[i];
    }
}

char* TiObject::getStringFromObject(Handle<Value> value, const char* defaultString)
{
    char* str = NULL;
    HandleScope handleScope;
    if (value->IsString())
    {
        Handle < String > v8str = Handle < String > ::Cast(value);
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
    Handle < Object > obj = Handle < Object > ::Cast(value);
    Handle < External > ext = Handle < External > ::Cast(obj->GetHiddenValue(String::New(HIDDEN_TI_OBJECT_PROPERTY)));
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
    Handle < Object > obj = Handle < Object > ::Cast(jsObject);
    obj->SetHiddenValue(String::New(HIDDEN_TI_OBJECT_PROPERTY), External::New(tiObj));
}

Handle<ObjectTemplate> TiObject::getObjectTemplateFromJsObject(Handle<Value> value)
{
    HandleScope handleScope;
    Handle < Object > obj = Handle < Object > ::Cast(value);
    Handle < Context > context = obj->CreationContext();
    Handle < External > globalTemplateExternal = Handle < External
                                                 > ::Cast(
                                                         context->Global()->GetHiddenValue(
                                                                 String::New(HIDDEN_TEMP_OBJECT_PROPERTY)));
    Handle < ObjectTemplate > temp = *((Handle<ObjectTemplate>*) globalTemplateExternal->Value());
    return handleScope.Close(temp);
}

void TiObject::addRef()
{
    // TODO: protect in multi-threaded environment
    refCount_++;
}

void TiObject::release()
{
    // TODO: protect in multi-threaded environment
    if ((--refCount_) == 0)
    {
        delete this;
    }
}

void TiObject::initializeTiObject(TiObject* parentContext)
{
    if (!hasInitialized())
    {
        hasInitialized_ = true;
        parentObject_ = parentContext;
        onCreateStaticMembers();
    }
}

Handle<Value> TiObject::onFunctionCall(const Arguments& args)
{
    // Default function call returns "Undefined"
    return Undefined();
}

void TiObject::onCreateStaticMembers()
{
}

const char* TiObject::getName() const
{
    return (name_ == NULL) ? "" : name_;
}

void TiObject::addMember(TiObject* object, const char* name/*=NULL*/)
{
    HandleScope handleScope;
    int i;
    OBJECT_ENTRY* entry = NULL;
    const char* memberName = (name == NULL) ? object->getName() : name;
    object->addRef();
    for (i = 0; i < childObjectCount_; i++)
    {
        if (strcmp(childObject_[i]->getObjectName(), memberName) == 0)
        {
            delete childObject_[i];
            childObject_[i] = new OBJECT_ENTRY;
            entry = childObject_[i];
        }
    }
    if (entry == NULL)
    {
        childObjectCount_++;
        childObject_ = (OBJECT_ENTRY**) realloc(childObject_, sizeof(OBJECT_ENTRY*) * childObjectCount_);
        childObject_[childObjectCount_ - 1] = new OBJECT_ENTRY;
        entry = childObject_[childObjectCount_ - 1];
    }
    entry->setObjectName(memberName);
    entry->obj_ = object;
    object->initializeTiObject(this);
}

Handle<Value> TiObject::getValue()
{
    HandleScope handleScope;
    return value_;
}

TiObject* TiObject::onLookupMember(const char* memberName)
{
    int i;
    HandleScope handleScope;
    Handle < Object > obj;
    for (i = 0; i < childObjectCount_; i++)
    {
        if (strcmp(childObject_[i]->objectName_, memberName) == 0)
        {
            childObject_[i]->obj_->addRef();
            return childObject_[i]->obj_;
        }
    }
    return NULL;
}

void TiObject::onSetGetPropertyCallback(Handle<ObjectTemplate>* objTemplate)
{
    HandleScope handleScope;
    (*objTemplate)->SetNamedPropertyHandler(propGetter_, propSetter_);
}

void TiObject::onSetFunctionCallback(Handle<ObjectTemplate>* objTemplate)
{
    HandleScope handleScope;
    (*objTemplate)->SetCallAsFunctionHandler(functCallback_);
}

void TiObject::onSetProperty(const char* propertyName, Local<Value> value)
{
}

void TiObject::onStartMessagePump()
{
    int i;
    for (i = 0; i < childObjectCount_; i++)
    {
        childObject_[i]->obj_->onStartMessagePump();
    }
}

VALUE_MODIFY TiObject::onValueChange(Handle<Value> oldValue, Handle<Value> newValue)
{
    return VALUE_MODIFY_ALLOW;
}

VALUE_MODIFY TiObject::onChildValueChange(TiObject* childObject, Handle<Value> oldValue, Handle<Value> newValue)
{
    return VALUE_MODIFY_ALLOW;
}

VALUE_MODIFY TiObject::setValue(Handle<Value> value)
{
    VALUE_MODIFY modify = onValueChange(value_, value);
    if (modify != VALUE_MODIFY_ALLOW)
    {
        return modify;
    }
    TiObject* parent = getParentObject();
    if (parent != NULL)
    {
        modify = onChildValueChange(this, value_, value);
        parent->release();
        if (modify != VALUE_MODIFY_ALLOW)
        {
            return modify;
        }
    }
    value_ = Persistent < Value > ::New(value);
    return modify;
}

bool TiObject::userCanAddMember(const char* propertyName) const
{
    return true;
}

Handle<Value> TiObject::propGetter_(Local<String> prop, const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle < Object > result;
    TiObject* obj = getTiObjectFromJsObject(info.Holder());
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(info.Holder());
    String::Utf8Value propName(prop);
    const char* propString = (const char*) (*propName);
    TiObject* propObject = obj->onLookupMember(propString);
    if (propObject == NULL)
    {
        // TODO: lookup
        return Undefined();
    }
    Handle < Value > ret = propObject->getValue();
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
Handle<Value> TiObject::propSetter_(Local<String> prop, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle < Object > result;
    TiObject* obj = getTiObjectFromJsObject(info.Holder());
    String::Utf8Value propName(prop);
    const char* propString = (const char*) (*propName);
    TiObject* destObj = obj->onLookupMember(propString);
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
        if ((!obj->canAddMembers()) || (!obj->userCanAddMember(propString)))
        {
            srcObj->release();
            return Undefined();
        }
        destObj = srcObj;
    }
    destObj->setValue(value);
    setTiObjectToJsObject(value, destObj);
    obj->addMember(destObj, propString);
    obj->onSetProperty(propString, value);
    srcObj->release();
    return value;
}
Handle<Value> TiObject::functCallback_(const Arguments& args)
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
    return (childObjectCount_ == 0) ? false : true;
}

bool TiObject::isFunction() const
{
    return false;
}

bool TiObject::canAddMembers() const
{
    return true;
}

bool TiObject::hasInitialized() const
{
    return hasInitialized_;
}

bool TiObject::isUIObject() const
{
    return false;
}

void TiObject::setTiMappingProperties(const TI_PROPERTY* prop, int propertyCount)
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

OBJECT_ENTRY::OBJECT_ENTRY()
{
    obj_ = NULL;
    userContext_ = NULL;
    objectName_ = NULL;
}

OBJECT_ENTRY::~OBJECT_ENTRY()
{
    if (objectName_ != NULL)
    {
        delete[] objectName_;
        objectName_ = NULL;
    }
    if (obj_ != NULL)
    {
        obj_->release();
        obj_ = NULL;
    }
}

void OBJECT_ENTRY::setObjectName(const char* objectName)
{
    if (objectName_ != NULL)
    {
        delete[] objectName_;
    }
    const char* name = (objectName == NULL) ? "" : objectName;
    objectName_ = new char[strlen(name) + 1];
    strcpy(objectName_, name);
}

const char* OBJECT_ENTRY::getObjectName() const
{
    return (objectName_ == NULL) ? "" : objectName_;
}

