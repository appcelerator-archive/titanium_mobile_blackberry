/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUISCROLLVIEW_H_
#define TIUISCROLLVIEW_H_

#include "TiUIBase.h"

/*
 * TiUIScrollView
 *
 * Represents a Titanium scrollView object
 *
 */

class TiUIScrollView : public TiUIBase
{
public:
    static TiUIScrollView* createScrollView(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIScrollView();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIScrollView();
};

#endif /* TIUISCROLLVIEW_H_ */
