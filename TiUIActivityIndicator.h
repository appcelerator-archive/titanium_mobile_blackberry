/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIACTIVITYINDICATOR_H_
#define TIUIACTIVITYINDICATOR_H_

#include "TiProxy.h"

/*
 * TiUIActivityIndicator
 *
 * Represents a Titanium activity indicator object
 *
 */

class TiUIActivityIndicator : public TiProxy
{
public:
    static TiUIActivityIndicator* createActivityIndicator(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIActivityIndicator();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    explicit TiUIActivityIndicator();
    static Handle<Value> show_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> hide_(void* userContext, TiObject* caller, const Arguments& args);
    // Disable copy ctor & assignment operator
    TiUIActivityIndicator(const TiUIActivityIndicator& indicator);
    TiUIActivityIndicator& operator=(const TiUIActivityIndicator& indicator);
};


#endif /* TIUIACTIVITYINDICATOR_H_ */
