/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIIMAGEBUTTON_H_
#define TIUIIMAGEBUTTON_H_

#include "TiUIBase.h"

/*
 * TiUIButton
 *
 * Represents a Titanium button object
 *
 */

class TiUIImageButton : public TiUIBase
{
public:
    static TiUIImageButton* createButton(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIImageButton();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIImageButton();
};

#endif /* TIUIIMAGEBUTTON_H_ */
