/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIUITABLEVIEW_H_
#define TIUITABLEVIEW_H_

#include "TiUIBase.h"

/*
 * TiUITableView
 *
 * Represents a Titanium TableView object
 *
 * This object can be created by:
 * Titanium.UI.createTableView({...});
 */
class TiUITableView : public TiUIBase
{
public:
    static TiUITableView* createTableView(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUITableView();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();
    static Handle<Value> _scrollToIndex(void* userContext, TiObject* caller, const Arguments& args);

private:
    explicit TiUITableView(NativeObjectFactory* nativeObjectFactory);

    TiUITableView(const TiUITableView& obj);
    TiUITableView& operator=(const TiUITableView& obj);
};

#endif /* TIUITABLEVIEW_H_ */
