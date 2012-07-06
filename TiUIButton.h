/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBUTTON_H_
#define TIUIBUTTON_H_

#include "TiUIBase.h"

/*
 * TiUIButton
 *
 * Represents a Titanium button object
 *
 */

class TiUIButton : public TiUIBase
{
public:
    static TiUIBase* createButton(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIButton();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIButton();
};

#endif /* TIUIBUTTON_H_ */
