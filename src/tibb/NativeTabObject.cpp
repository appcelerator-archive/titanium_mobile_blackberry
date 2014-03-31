/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTabObject.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/Image>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/Page>
#include <bb/cascades/Tab>

#include "Scene.h"
#include "TiObject.h"
#include "V8Utils.h"
#include "Window.h"
#include "TiCore.h"

using namespace bb::cascades;
using namespace titanium;

NativeTabObject::NativeTabObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_TAB)
    , navigationPane_(NULL)
    , tab_(NULL)
{
}

NativeTabObject::~NativeTabObject()
{
    delete tab_;
    tab_ = NULL;
    delete navigationPane_;
    navigationPane_ = NULL;
}

NativeObject* NativeTabObject::createTab(TiObject* tiObject)
{
    NativeTabObject* obj = new NativeTabObject(tiObject);
    return obj;
}

NATIVE_TYPE NativeTabObject::getObjectType() const
{
    return N_TYPE_TAB;
}

NAHANDLE NativeTabObject::getNativeHandle() const
{
    return tab_;
}

int NativeTabObject::addChildNativeObject(NativeObject* obj)
{
    if (obj->getObjectType() == N_TYPE_WINDOW)
    {
    	titanium::Window* window = static_cast<titanium::Window*>(obj->getNativeHandle());
        Page* page = static_cast<Page*>(window->scene()->pane());

        // The ownership of the page must be cleared before pushing,
        // otherwise navigation pane will do nothing.
        page->setParent(0);

        navigationPane_->push(page);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabObject::pop()
{
    navigationPane_->pop();
    return NATIVE_ERROR_OK;
}

int NativeTabObject::openWindowOnTab(NativeObject* obj)
{
    return addChildNativeObject(obj);
}
int NativeTabObject::closeWindowOnTab(NativeObject* obj)
{
    if (obj->getObjectType() == N_TYPE_WINDOW)
    {
    	titanium::Window* window = static_cast<titanium::Window*>(obj->getNativeHandle());
        Page* page = static_cast<Page*>(window->scene()->pane());

        // The ownership of the page must be cleared before pushing,
        // otherwise navigation pane will do nothing.
        page->setParent(0);

        navigationPane_->remove(page);
    }
    return NATIVE_ERROR_OK;
}

int NativeTabObject::setIcon(TiObject* obj)
{
    QString iconPath = V8ValueToQString(obj->getValue());
    iconPath = Ti::TiHelper::getAssetPath(iconPath);
    tab_->setImage(bb::cascades::Image(QUrl(iconPath)));
    return NATIVE_ERROR_OK;
}

int NativeTabObject::setWindow(TiObject* obj)
{
	Handle<Value> window = obj->getValue();
	TiObject* windowObject = TiObject::getTiObjectFromJsObject(window);
    NativeObject* childNO = windowObject->getNativeObject();
    addChildNativeObject(childNO);
    childNO->release();
	return NATIVE_ERROR_OK;
}

int NativeTabObject::setTitle(TiObject* obj)
{
    QString title = V8ValueToQString(obj->getValue());
    tab_->setTitle(title);
    return NATIVE_ERROR_OK;
}

int NativeTabObject::setDescription(TiObject* obj)
{
    QString desc = V8ValueToQString(obj->getValue());
    tab_->setDescription(desc);
    return NATIVE_ERROR_OK;
}

int NativeTabObject::setActive(TiObject* obj)
{
    if (!tabPane_.isNull() && obj->getValue()->IsTrue()) {
        tabPane_->setActiveTab(tab_);
    }
    return NATIVE_ERROR_OK;
}

int NativeTabObject::isActive(TiObject* obj)
{
    bool active = !tabPane_.isNull() && tabPane_->activeTab() == tab_;
    obj->setValue(Boolean::New(active));
    return NATIVE_ERROR_OK;
}

int NativeTabObject::initialize()
{
    tab_ = Tab::create();
    navigationPane_ = NavigationPane::create();
    tab_->setContent(navigationPane_);

    if (tab_ == NULL || navigationPane_ == NULL)
    {
        //if one of the tab_ or navigationPane_ pointers is NULL,
        //it means that create function couldn't allocate enough memory for at least one of these objects
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}

