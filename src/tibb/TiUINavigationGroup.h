/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TiUINavigationGroup_H_
#define TiUINavigationGroup_H_

#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include "TiProxy.h"
#include "Scene.h"

class NavigationScene: public titanium::Scene {
    Q_OBJECT
public:
    NavigationScene(): titanium::Scene(new bb::cascades::NavigationPane()){}
};

class TiUINavigationGroup: public TiProxy {
public:

	static TiUINavigationGroup* createProxy(NativeObjectFactory* objectFactory);

protected:
    virtual void onCreateStaticMembers();
private:

	static Handle<Value> _close(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _open(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _push(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _remove(void* userContext, TiObject*, const Arguments& args);

	static Handle<Value> _getPeekEnabled(void* userContext);
	static Handle<Value> _getBackButtonsVisible(void* userContext);

	static void _setWindow(void* userContext, Handle<Value> value);
	static void _setRootWindow(void* userContext, Handle<Value> value);
	static void _setBackButtonsVisible(void* userContext, Handle<Value> value);
	static void _setPeekEnabled(void* userContext, Handle<Value> value);

	TiUINavigationGroup();
	virtual ~TiUINavigationGroup();

	NavigationScene *getNavigationScene();
	bb::cascades::Page *getPageFromTiObject(TiObject*);
	bb::cascades::Sheet *modalSheet_;
	NavigationScene *navigationScene_;
};

#endif /* TiUINavigationGroup_H_ */
