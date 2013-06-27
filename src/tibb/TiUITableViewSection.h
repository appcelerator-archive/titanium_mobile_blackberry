/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITABLEVIEWSECTION_H_
#define TIUITABLEVIEWSECTION_H_

#include "TiProxy.h"

class TiUITableViewSection : public TiProxy
{
public:
	virtual void onCreateStaticMembers();

    static Handle<Value> createProxy(void* userContext, TiObject*, const Arguments& args)
    {
    	return TiProxy::createProxy(new TiUITableViewSection(), userContext, args);
    }
    Handle<Array> getRowsInSection();

private:
	TiUITableViewSection();
	virtual ~TiUITableViewSection();

    Persistent<Array> rowsInSection;
    void addRow(Handle<Value>);
    // JS Setters
    static void _setTitle(void* userContext, Handle<Value> val);
    static void _setSubTitle(void* userContext, Handle<Value> val);
    // JS Getters
    static Handle<Value> _getTitle(void* userContext);
    static Handle<Value> _getSubTitle(void* userContext);
    // JS Methods
    static Handle<Value> _add(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TIUITABLEVIEWSECTION_H_ */
