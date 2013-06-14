/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUINavigationGroup.h"
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

TiUINavigationGroup::TiUINavigationGroup() {
	navigationScene_ = NULL;
	modalSheet_ = NULL;
}

TiUINavigationGroup::~TiUINavigationGroup() {
	// TODO Auto-generated destructor stub
}

TiUINavigationGroup* TiUINavigationGroup::createProxy(NativeObjectFactory* objectFactory)
{
	TiUINavigationGroup* obj = new TiUINavigationGroup;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

NavigationScene *TiUINavigationGroup::getNavigationScene()
{
	if(navigationScene_ == NULL) {
		navigationScene_ = new NavigationScene();
	}
	return navigationScene_;
}

void TiUINavigationGroup::onCreateStaticMembers()
{
	TiProxy::onCreateStaticMembers();
	TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "pop", this, _pop);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "push", this, _push);
	TiGenericFunctionObject::addGenericFunctionToParent(this, "remove", this, _remove);


	createSettersAndGetters("window", _setWindow, NULL);
	createSettersAndGetters("rootWindow", _setRootWindow, NULL);
	createSettersAndGetters("backButtonsVisible", _setBackButtonsVisible, _getBackButtonsVisible);
	createSettersAndGetters("peekEnabled", _setPeekEnabled, _getPeekEnabled);
}

bb::cascades::Page* TiUINavigationGroup::getPageFromTiObject(TiObject* obj)
{
	NativeObject *nativeObject = obj->getNativeObject();
    if (nativeObject->getObjectType() == N_TYPE_WINDOW) {
    	titanium::Window* window = static_cast<titanium::Window*>(nativeObject->getNativeHandle());
    	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(window->scene()->pane());
    	return page;
    }
    return NULL;
}

Handle<Value> TiUINavigationGroup::_getPeekEnabled(void* userContext)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	return Boolean::New(pane->isPeekEnabled());
}

Handle<Value> TiUINavigationGroup::_getBackButtonsVisible(void* userContext)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	return Boolean::New(pane->backButtonsVisible());
}

void TiUINavigationGroup::_setPeekEnabled(void* userContext, Handle<Value> value)
{
	if(value->IsBoolean())
	{
		TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
		NavigationScene *nav = proxy->getNavigationScene();
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	    Local<Boolean> b = value->ToBoolean();
		pane->setPeekEnabled(b->Value());
	}
}

void TiUINavigationGroup::_setBackButtonsVisible(void* userContext, Handle<Value> value)
{
	if(value->IsBoolean())
	{
		TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
		NavigationScene *nav = proxy->getNavigationScene();
		bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	    Local<Boolean> b = value->ToBoolean();
		pane->setBackButtonsVisible(b->Value());
	}
}

void TiUINavigationGroup::_setWindow(void* userContext, Handle<Value> value)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();

	TiObject *obj = TiObject::getTiObjectFromJsObject(value);
	bb::cascades::Page* page = proxy->getPageFromTiObject(obj);
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());

	page->setParent(0);
	pane->push(page);

}
void TiUINavigationGroup::_setRootWindow(void* userContext, Handle<Value> value)
{
	TiUINavigationGroup::_setWindow(userContext, value);
}

Handle<Value> TiUINavigationGroup::_close(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;

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
		return TiUINavigationGroup::_remove(userContext, NULL, args);
	}
	return Undefined();
}
Handle<Value> TiUINavigationGroup::_open(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();

	// If no arguments, open the NavigationGroup
	if(args.Length() == 0) {
		titanium::SceneManager::instance()->presentScene(nav);
	}
	else if(args.Length() > 0 && args[0]->IsObject())
	{
		// Check if we have a window as an argument and open it in the stack
		TiObject *obj = TiObject::getTiObjectFromJsObject(args[0]);
		if(obj != NULL)
		{
			NativeObject *nativeObject = obj->getNativeObject();
			if (nativeObject->getObjectType() == N_TYPE_WINDOW) {
				// depricated, use .push() instead
				nativeObject->fireEvent("open", NULL);
				return TiUINavigationGroup::_push(userContext, NULL, args);
			}
			return Undefined();
		}
		// Check for modal flag
		Local<Object> modal = args[0]->ToObject();
		Local<Boolean> isTrue = modal->Get(String::New("modal"))->ToBoolean();

		// if true, open a modal NavigationGroup
		if(isTrue->Value()) {
			proxy->modalSheet_ = bb::cascades::Sheet::create();
			proxy->modalSheet_->setPeekEnabled(false);
			proxy->modalSheet_->setContent(nav->pane());
			proxy->modalSheet_->open();
	    	return Undefined();
		}
		// If not, just show it
		else
		{
			titanium::SceneManager::instance()->presentScene(nav);
		}

	}
	return Undefined();
}
Handle<Value> TiUINavigationGroup::_pop(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
	NavigationScene *nav = proxy->getNavigationScene();
	bb::cascades::NavigationPane *pane = static_cast<bb::cascades::NavigationPane*>(nav->pane());
	pane->pop();
	return Undefined();
}
Handle<Value> TiUINavigationGroup::_push(void* userContext, TiObject*, const Arguments& args)
{
	if(args.Length() > 0 && args[0]->IsObject())
	{
		_setWindow(userContext, args[0]);
	}

	return Undefined();
}
Handle<Value> TiUINavigationGroup::_remove(void* userContext, TiObject*, const Arguments& args)
{
	TiUINavigationGroup* proxy = (TiUINavigationGroup*)userContext;
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
