/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiNetwork.h"

#include "TiSocketObject.h"

TiNetwork::TiNetwork()
    : TiProxy("Network")
{
    objectFactory_ = NULL;
}

TiNetwork::TiNetwork(NativeObjectFactory* objectFactory)
    : TiProxy("Network")
{
    objectFactory_ = objectFactory;
}

TiNetwork::~TiNetwork()
{
}

void TiNetwork::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiNetwork* obj = new TiNetwork(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiNetwork::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiSocketObject::addObjectToParent(this, objectFactory_);
    // TODO: Add class methods, constants, properties
}
