/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUINAVIGATIONGROUPPROXY_H_
#define TIUINAVIGATIONGROUPPROXY_H_

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

class TiUINavigationGroupProxy: public TiProxy {
public:

	static TiUINavigationGroupProxy* createProxy(NativeObjectFactory* objectFactory);

protected:
    virtual void onCreateStaticMembers();
private:

	static Handle<Value> _close(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _open(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _push(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _remove(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _setWindow(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _setRootWindow(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _setBackButtonsVisible(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _setPeekEnabled(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _getPeekEnabled(void* userContext, TiObject*, const Arguments& args);

	TiUINavigationGroupProxy();
	virtual ~TiUINavigationGroupProxy();

	NavigationScene *getNavigationScene();
	bb::cascades::Page *getPageFromTiObject(TiObject*);
	bb::cascades::Sheet *modalSheet_;
	NavigationScene *navigationScene_;
};

#endif /* TIUINAVIGATIONGROUPPROXY_H_ */
