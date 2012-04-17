/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUISLIDER_H_
#define TIUISLIDER_H_

#include "TiUIBase.h"

/*
 * TiUISlider
 *
 * Represents a Titanium slider control object
 */

class TiUISlider : public TiUIBase
{
public:
    static TiUISlider* createSlider(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUISlider();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUISlider(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUISLIDER_H_ */
