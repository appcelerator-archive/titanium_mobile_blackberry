/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIMAPVIEW_H_
#define TIMAPVIEW_H_

#include "TiUIBase.h"

/*
 * TiMapView
 *
 * Represents a Titanium MapView object
 *
 */

class TiMapView: public TiUIBase
{
public:
    static TiMapView* createMapView(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiMapView();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiMapView();

	static Handle<Value> _selectAnnotation(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _removeAnnotation(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _addAnnotation(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TIMAPVIEW_H_ */
