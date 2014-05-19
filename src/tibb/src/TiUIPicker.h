/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIPICKER_H_
#define TIUIPICKER_H_

#include "TiUIBase.h"

/*
 * TiUIPicker
 *
 * Represents a Titanium Picker object
 *
 * This object can be created by:
 * Titanium.UI.createPicker({...});
 */
class TiUIPicker : public TiUIBase
{
public:
    static TiUIPicker* createPicker(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIPicker();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    TiUIPicker();

    // Disable copy ctor & assignment operator
    TiUIPicker(const TiUIPicker& obj);
    TiUIPicker& operator=(const TiUIPicker& obj);
};

#endif /* TIUIPICKER_H_ */
