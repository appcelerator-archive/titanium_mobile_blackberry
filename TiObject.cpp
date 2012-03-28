/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiObject.h"
#include <malloc.h>

TiObject::TiObject()
{
    refCount_ = 1;
    name_ = NULL;
    childObject_ = NULL;
    childObjectCount_ = 0;
    hasInitialized_ = false;
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
}

TiObject::TiObject(const char* objectName, Handle<Value> value)
{
    refCount_ = 1;
    name_ = new char[strlen((objectName == NULL) ? "" : objectName) + 1];
    strcpy(name_, (objectName == NULL) ? "" : objectName);
    childObject_ = NULL;
    childObjectCount_ = 0;
    value_ = Persistent < Value > ::New(value);
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
        onCreateStaticMembers();
    }
}

Handle<Value> TiObject::onFunctionCall(const Arguments& args)
{
    return Undefined();
}

void TiObject::onCreateStaticMembers()
{
}

const char* TiObject::getName() const
{
    return (name_ == NULL) ? "" : name_;
}

void TiObject::addMember(TiObject* object, const char* name)
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
        childObject_ = (OBJECT_ENTRY**) realloc(
                childObject_, sizeof(OBJECT_ENTRY*) * childObjectCount_);
        childObject_[childObjectCount_ - 1] = new OBJECT_ENTRY;
        entry = childObject_[childObjectCount_ - 1];
    }
    entry->setObjectName(memberName);
    entry->obj_ = object;
    object->setGlobalTemplate(getGlobalTemplate());
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
Handle<ObjectTemplate>* TiObject::getGlobalTemplate()
{
    return globalTemplate_;
}
void TiObject::setGlobalTemplate(Handle<ObjectTemplate>* globalTemplate)
{
    globalTemplate_ = globalTemplate;
}
bool TiObject::userCanAddMember(const char* propertyName)
{
    return true;
}
Handle<Value> TiObject::propGetter_(Local<String> prop,
                                    const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle < Object > result;
    Handle < Context > context = info.Holder()->CreationContext();
    Handle < External > ptr = Handle < External
                              > ::Cast(
                                      info.Holder()->GetHiddenValue(
                                              String::New("ti_")));
    TiObject* obj = (TiObject*) ptr->Value();
    Handle < External > globalTemplate =
            Handle < External
            > ::Cast(
                    context->Global()->GetHiddenValue(
                            String::New("globalTemplate_")));
    Handle < ObjectTemplate > *global =
            (Handle<ObjectTemplate>*) (globalTemplate->Value());
    String::Utf8Value propName(prop);
    const char* propString = (const char*) (*propName);
    TiObject* propObject = obj->onLookupMember(propString);
    if (propObject == NULL)
    {
        // TODO: lookup
        return Undefined();
    }
    if ((propObject->hasMembers()) || (propObject->isFunction()))
    {
        result = (*global)->NewInstance();
        result->SetHiddenValue(String::New("ti_"), External::New(propObject));
    }
    else
    {
        propObject->release();
        return handleScope.Close(propObject->getValue());
    }
    propObject->release();
    return handleScope.Close(result);
}
Handle<Value> TiObject::propSetter_(Local<String> prop, Local<Value> value,
                                    const AccessorInfo& info)
{
    HandleScope handleScope;
    Handle < Object > result;
    Handle < Context > context = info.Holder()->CreationContext();
    Handle < External > ptr = Handle < External
                              > ::Cast(
                                      info.Holder()->GetHiddenValue(
                                              String::New("ti_")));
    TiObject* obj = (TiObject*) ptr->Value();
    Handle < External > globalTemplate =
            Handle < External
            > ::Cast(
                    context->Global()->GetHiddenValue(
                            String::New("globalTemplate_")));
    String::Utf8Value propName(prop);
    const char* propString = (const char*) (*propName);
    if ((!obj->canAddMembers()) || (!obj->userCanAddMember(propString)))
    {
        return Undefined();
    }
    if (value->IsObject())
    {
        Handle < Object > valueObj = Handle < Object > ::Cast(value);
        Handle < External > ptr2 = Handle < External
                                   > ::Cast(
                                           valueObj->GetHiddenValue(
                                                   String::New("ti_")));
        TiObject* obj2 = (TiObject*) ptr2->Value();
        obj->addMember(obj2, propString);
    }
    else
    {
        info.Holder()->Set(prop, value);
    }
    return value;
}
Handle<Value> TiObject::functCallback_(const Arguments& args)
{
    HandleScope handleScope;
    Handle < External > ptr = Handle < External
                              > ::Cast(
                                      args.Holder()->GetHiddenValue(
                                              String::New("ti_")));
    TiObject* obj = (TiObject*) ptr->Value();
    return handleScope.Close(obj->onFunctionCall(args));
}

bool TiObject::hasMembers()
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

