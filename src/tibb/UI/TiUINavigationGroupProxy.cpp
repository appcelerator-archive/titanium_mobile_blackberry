/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUINavigationGroupProxy.h"
#include "TiGenericFunctionObject.h"
#include "SceneManager.h"
#include "Window.h"
#include "NativeObject.h"

/* How to create a NavigationGroup
 *
 * var nav = Ti.UI.createNavigationGroup();
 * var rootWindow = Ti.UI.createWindow();
 * nav.setRootWindow(rootWindow);
 * nav.open();
 */

/*
 * How to open a new window
 *
 * var otherWindow = Ti.UI.createWindow();
 * nav.push(otherWindow);
 */

/*
 * How to close the last window
 *
 * nav.pop();
 */

/*
 * How remove a specific window
 *
 * nav.remove(window);
 */

/*
 * How to close the NavigationGroup
 *
 * nav.close()
 */

TiUINavigationGroupProxy::TiUINavigationGroupProxy() {
	navigationScene_ = NULL;
	modalSheet_ = NULL;
}

TiUINavigationGroupProxy::~TiUINavigationGroupProxy() {
	// TODO Auto-generated destructor stub
}

TiUINavigationGroupProxy* TiUINavigationGroupProxy::createProxy(NativeObjectFactory* objectFactory)
{
	TiUINavigationGroupProxy* obj = new TiUINavigationGroupProxy;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

NavigationScene *TiUINavigationGroupProxy::getNavigationScene()
{
	if(navigationScene_ == NULL) {
		navigationScene_ = new NavigationScene();
	}
	return navigationScene_;
}

void TiUINavigationGroupProxy::onCreateStaticMembers()
{
	TiProxy::onCreateStaticMembers();
	TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "pop", this, _pop);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "push", this, _push);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "remove", this, _remove);


	// TODO: Replace these  with the setters and getters
	// Waiting on https://github.com/appcelerator/titanium_mobile_blackberry/pull/63
	TiGenericFunctionObject::addGenericFunctionToParent(this, "setWindow", this, _setWindow);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "setRootWindow", this, _setRootWindow);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "setBackButtonsVisible", this, _setBackButtonsVisible);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "setPeekEnabled", this, _setPeekEnabled);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "getPeekEnabled", this, _getPeekEnabled);
	//	createSettersAndGetters("window", _setWindow, NULL);
	//	createSettersAndGetters("rootWindow", _setRootWindow, NULL);
	//	createSettersAndGetters("backButtonsVisible", _setBackButtonsVisible, NULL);
	//	createSettersAndGetters("peekEnabled", _setPeekEnabled, _getPeekEnabled);

}

bb::cascades::Page* TiUINavigationGroupProxy::getPageFromTiObject(TiObject* obj)
{
	NativeObject *nativeObject = obj->getNativeObject();
    if (nativeObject->getObjectType() == N_TYPE_WINDOW) {
    	titanium::Window* window = static_cast<titanium::Window*>(nativeObject->getNativeHandle());
    	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(window->scene()->pane());
    	return page;
    }
    return NULL;
}

Handle<Value> TiUINavigationGroupProxy::_setPeekEnabled(void* userContext, TiObject*, const Arguments& args)
{
	if(args.Length() > 0 && args[0]->IsBoolean())
	{
		TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
		NavigationScene *nav = proxy->getNavigationScene();
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	    Local<Boolean> b = args[0]->ToBoolean();
		pane->setPeekEnabled(b->Value());
	}
	return Undefined();
}

Handle<Value> TiUINavigationGroupProxy::_getPeekEnabled(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	return Boolean::New(pane->isPeekEnabled());
}

Handle<Value> TiUINavigationGroupProxy::_setBackButtonsVisible(void* userContext, TiObject*, const Arguments& args)
{
	if(args.Length() > 0 && args[0]->IsBoolean())
	{
		TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
		NavigationScene *nav = proxy->getNavigationScene();
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	    Local<Boolean> b = args[0]->ToBoolean();
		pane->setBackButtonsVisible(b->Value());
	}
	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_close(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;

	NavigationScene *nav = proxy->getNavigationScene();
	if(args.Length() == 0 && proxy->modalSheet_ != NULL)
	{
		proxy->modalSheet_->close();
	}
	else if(args.Length() == 0)
	{
		titanium::SceneManager::instance()->removeScene(nav);
		delete nav;
		proxy->navigationScene_ = NULL;
	}
	else if(args[0]->IsObject())
	{
		TiObject *obj = TiObject::getTiObjectFromJsObject(args[0]);
		if(obj == NULL && proxy->modalSheet_ != NULL) {
			proxy->modalSheet_->close();
			return Undefined();
		}
		// depricated, use .remove() instead
		return TiUINavigationGroupProxy::_remove(userContext, NULL, args);
	}
	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_open(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();

	if(args.Length() == 0) {
		titanium::SceneManager::instance()->presentScene(nav);
	}
	else if(args.Length() > 0 && args[0]->IsObject())
	{
		TiObject *obj = TiObject::getTiObjectFromJsObject(args[0]);
		if(obj == NULL) {
			proxy->modalSheet_ = bb::cascades::Sheet::create();
			proxy->modalSheet_->setContent(nav->pane());
			proxy->modalSheet_->open();
	    	return Undefined();
		}
		NativeObject *nativeObject = obj->getNativeObject();
	    if (nativeObject->getObjectType() == N_TYPE_WINDOW) {
			// depricated, use .push() instead
	    	return TiUINavigationGroupProxy::_push(userContext, NULL, args);
	    }
	}
	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_pop(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	pane->pop();
	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_push(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();

	if(args.Length() > 0 && args[0]->IsObject())
	{
		TiObject *obj = TiObject::getTiObjectFromJsObject(args[0]);
		bb::cascades::Page* page = proxy->getPageFromTiObject(obj);
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());

		page->setParent(0);
		pane->push(page);
		return Undefined();
	}

	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_remove(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroupProxy* proxy = (TiUINavigationGroupProxy*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	if(args.Length() > 0 && args[0]->IsObject())
	{
		TiObject *obj = TiObject::getTiObjectFromJsObject(args[0]);
		bb::cascades::Page *page = proxy->getPageFromTiObject(obj);
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
		pane->remove(page);
	}
	return Undefined();
}
Handle<Value> TiUINavigationGroupProxy::_setWindow(void* userContext, TiObject*, const Arguments& args)
{
	// deprecated, use .setRootWindow() instead
	return TiUINavigationGroupProxy::_push(userContext, NULL, args);
}
Handle<Value> TiUINavigationGroupProxy::_setRootWindow(void* userContext, TiObject*, const Arguments& args)
{
	return TiUINavigationGroupProxy::_push(userContext, NULL, args);
}
