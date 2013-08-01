/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMap.h"

#include "KeyboardType.h"
#include "Scene.h"
#include "TiCascadesApp.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiMapView.h"
#include "TiAnnotationObject.h"

#include <string.h>

using namespace titanium;

TiMap::TiMap()
    : TiProxy("Map")
{
    objectFactory_ = NULL;
    contentContainer_ = NULL;
}

TiMap::TiMap(NativeObjectFactory* objectFactory)
    : TiProxy("Map")
{
    objectFactory_ = objectFactory;
    contentContainer_ = NULL;
}

TiMap::~TiMap()
{
}

void TiMap::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiMap* obj = new TiMap(objectFactory);
    parent->addMember(obj);
    obj->setAttachedObject(parent);
    obj->release();
}

void TiMap::onCreateStaticMembers()
{
    HandleScope scope;

    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "createView", this, _createView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createAnnotation", this, _createAnnotation);

    // Adding javascript constants from Ti.Map
    ADD_STATIC_TI_VALUE("ANNOTATION_GREEN", Number::New(Ti::Map::ANNOTATION_GREEN), this);
    ADD_STATIC_TI_VALUE("ANNOTATION_RED", Number::New(Ti::Map::ANNOTATION_RED), this);
    ADD_STATIC_TI_VALUE("ANNOTATION_PURPLE", Number::New(Ti::Map::ANNOTATION_PURPLE), this);
}

Handle<Value> TiMap::_createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args)
{
    HandleScope handleScope;
    TiMap* obj = (TiMap*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiProxy* newControl = (createCallback)(obj->objectFactory_);
    newControl->setAttachedObject(obj);
    newControl->setValue(result);
    newControl->makeWeak();
    if (args.Length() > 0)
    {
        newControl->applyProperties(args[0]);
    }
    setTiObjectToJsObject(result, newControl);
    return handleScope.Close(result);
}

Handle<Value> TiMap::_createView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiMapView::createMapView, args);
}

Handle<Value> TiMap::_createAnnotation(void* userContext, TiObject*, const Arguments& args)
{
	 return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiAnnotationObject::createAnnotationObject, args);
}


