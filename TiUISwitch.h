/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUISWITCH_H_
#define TIUISWITCH_H_

#include "TiUIBase.h"

/*
 * TiUISwitch
 *
 * Represents a Titanium Switch object
 *
 * This object can be created by:
 * Titanium.UI.createSwitch({...});
 */
class TiUISwitch : public TiUIBase
{
public:
    static TiUIBase* createSwitch(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUISwitch();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUISwitch(NativeObjectFactory* nativeObjectFactory);

    // Disable copy ctor & assignment operator
    TiUISwitch(const TiUISwitch& switchObj);
    TiUISwitch& operator=(const TiUISwitch& switchObj);
};


#endif /* TIUISWITCH_H_ */
