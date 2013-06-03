/*
 * TiUINavigationGroupProxy.h
 *
 *  Created on: May 31, 2013
 *      Author: penrique
 */

#ifndef TIUINAVIGATIONGROUPPROXY_H_
#define TIUINAVIGATIONGROUPPROXY_H_

#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
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
	NavigationScene *navigationScene_;
};

#endif /* TIUINAVIGATIONGROUPPROXY_H_ */
