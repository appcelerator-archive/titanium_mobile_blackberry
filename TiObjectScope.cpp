/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiObjectScope.h"
#include "TiObject.h"
#include <utility>
#include <stdio.h>
#include <string.h>

TiObjectScope::TiObjectScope()
{
    object_ = NULL;

}

TiObjectScope::TiObjectScope(TiObject* obj)
{
    object_ = obj;
}

TiObjectScope::TiObjectScope(const TiObjectScope& scope)
{
    object_ = scope.object_;
    if (object_ != NULL)
    {
        object_->addRef();
    }
}

TiObjectScope::~TiObjectScope()
{
    if (object_ != NULL)
    {
        object_->release();
    }
}

const TiObjectScope& TiObjectScope::operator =(const TiObjectScope& scope)
{
    if (scope.object_ != NULL)
    {
        scope.object_->addRef();
    }
    if (object_ != NULL)
    {
        object_->release();
    }
    object_ = scope.object_;
    return (*this);
}

TiObject* TiObjectScope::operator ->() const
{
    return object_;
}

TiObjectScope::operator TiObject*() const
{
    return object_;
}

void TiObjectScope::attachTiObject(TiObject* obj)
{
    if (obj != NULL)
    {
        obj->addRef();
    }
    if (object_ != NULL)
    {
        object_->release();
    }
    object_ = obj;
}

TiObject* TiObjectScope::detachTiObject()
{
    TiObject* obj = object_;
    object_ = NULL;
    return obj;
}
