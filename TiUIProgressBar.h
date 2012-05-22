/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIPROGRESSBAR_H_
#define TIUIPROGRESSBAR_H_

#include "TiUIBase.h"

/*
 * TiUIProgressBar
 *
 * Represents a Titanium progress bar object
 */

class TiUIProgressBar : public TiUIBase
{
public:
    static TiUIBase* createProgressBar(NativeObjectFactory* nativeObjectFactory);
    virtual void initializeTiObject(TiObject* parentContext);

protected:
    virtual ~TiUIProgressBar();

private:
    TiUIProgressBar(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUIPROGRESSBAR_H_ */
