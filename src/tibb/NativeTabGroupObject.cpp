/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTabGroupObject.h"

#include <bb/cascades/TabbedPane>

#include <v8.h>

#include "NativeObjectFactory.h"
#include "NativeTabObject.h"
#include "SceneManager.h"
#include "TabbedScene.h"
#include "TiCascadesApp.h"
#include "TiObject.h"
#include "TiUITabGroup.h"

using namespace bb::cascades;
using namespace titanium;
using namespace v8;




NativeTabGroupObject::NativeTabGroupObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_TABGROUP)
    , nativeObjectFactory_(NULL)
    , tabGroup_(NULL)
{
}

NativeTabGroupObject::~NativeTabGroupObject()
{
    delete tabGroup_;
    tabGroup_ = NULL;
}

NativeObject* NativeTabGroupObject::createTabGroup(TiObject* tiObject, NativeObjectFactory* nativeObjectFactory)
{
    NativeTabGroupObject* obj = new NativeTabGroupObject(tiObject);
    obj->nativeObjectFactory_ = nativeObjectFactory;
    return obj;
}

NATIVE_TYPE NativeTabGroupObject::getObjectType() const
{
    return N_TYPE_TABGROUP;
}

NAHANDLE NativeTabGroupObject::getNativeHandle() const
{
    return tabGroup_;
}

int NativeTabGroupObject::initialize()
{
    if (tabGroup_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }

    scene_ = new TabbedScene();
    tabGroup_ = static_cast<TabbedPane*>(scene_->pane());

    // TODO(josh): expose as property
    tabGroup_->setShowTabsOnActionBar(true);

    if (tabGroup_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::addChildNativeObject(NativeObject* obj)
{
    if (obj && obj->getObjectType() == N_TYPE_TAB)
    {
        if (obj->getNativeHandle())
        {
            NativeTabObject* tab = static_cast<NativeTabObject*>(obj);
            tabGroup_->add((bb::cascades::Tab*) tab->getNativeHandle());
            tab->setTabbedPane(tabGroup_);
            return NATIVE_ERROR_OK;
        }
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::removeChildNativeObject(NativeObject* obj)
{
    if (obj && obj->getObjectType() != N_TYPE_TAB) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    Tab* tab = static_cast<Tab*>(obj->getNativeHandle());
    tabGroup_->remove(tab);

    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::setActiveTab(TiObject* obj)
{
    HandleScope scope;

    Handle<Value> val = obj->getValue();
    if (val->IsObject()) {
        TiObject* obj = TiObject::getTiObjectFromJsObject(val);
        if (!obj || !obj->isUIObject()) {
            // Not the right type of object.
            return NATIVE_ERROR_INVALID_ARG;
        }
        setActiveTab(obj->getNativeObject());
    } else {
        Local<Number> index = val->ToInteger();
        if (index.IsEmpty()) {
            // Not a valid number.
            return NATIVE_ERROR_INVALID_ARG;
        }
        setActiveTab(index->Value());
    }

    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::setActiveTab(NativeObject* tab)
{
    if (tab && tab->getObjectType() == N_TYPE_TAB)
    {
        if (tab->getNativeHandle())
        {
            tabGroup_->setActiveTab((bb::cascades::Tab*) tab->getNativeHandle());
            return NATIVE_ERROR_OK;
        }
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::setActiveTab(int index)
{
    if (tabGroup_->at(index) != NULL)
    {
        tabGroup_->setActiveTab(tabGroup_->at(index));
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::getActiveTab(TiObject* obj)
{
    Tab* activeTab = tabGroup_->activeTab();
    if (activeTab) {
        TiUITabGroup* tabGroup = static_cast<TiUITabGroup*>(tiObject_);
        TiObject* tabObj = tabGroup->getChildAt(tabGroup_->indexOf(activeTab));
        obj->setValue(tabObj->getValue());
    }
    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::setShowTabsOnActionBar(TiObject* obj)
{
	bool show;
    getBoolean(obj, &show);

	tabGroup_->setShowTabsOnActionBar(show);
    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::getTabs(TiObject* obj)
{
    Local<Array> tabs = Array::New();
    obj->setValue(tabs);

    TiUITabGroup* tabGroup = static_cast<TiUITabGroup*>(tiObject_);
    int count = tabGroup->childCount();
    for (int i = 0; i < count; i++) {
        TiObject* tab = tabGroup->getChildAt(i);
        tabs->Set(i, tab->getValue());
    }

    return NATIVE_ERROR_OK;
}

void NativeTabGroupObject::setupEvents(TiEventContainerFactory* factory)
{
    TiEventContainer* eventFocus = factory->createEventContainer();
    eventFocus->setDataProperty("type", "focus");
    events_.insert("focus", EventPairSmartPtr(eventFocus, new TabGroupFocusEventHandler(eventFocus)));
    QObject::connect(tabGroup_, SIGNAL(activeTabChanged(bb::cascades::Tab*)), events_["focus"]->handler(), SLOT(activeTabChanged(bb::cascades::Tab*)));
}

int NativeTabGroupObject::open()
{
    //Q_ASSERT(nativeObjectFactory_ != NULL);
    //nativeObjectFactory_->setRootContainer(this);

    SceneManager::instance()->presentScene(scene_);

    return NATIVE_ERROR_OK;
}

