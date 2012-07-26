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
    virtual void onCreateStaticMembers();

protected:
    virtual ~TiUIProgressBar();

private:
    explicit TiUIProgressBar();
    // Disable copy ctor & assignment operator
    TiUIProgressBar(const TiUIProgressBar& progressBar);
    TiUIProgressBar& operator=(const TiUIProgressBar& progressBar);
};

#endif /* TIUIPROGRESSBAR_H_ */
