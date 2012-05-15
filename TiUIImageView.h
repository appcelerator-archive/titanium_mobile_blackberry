/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIIMAGEVIEW_H_
#define TIUIIMAGEVIEW_H_

#include "TiUIBase.h"

/*
 * TiUIImageView
 *
 * Represents a Titanium imageView object
 *
 * This object can be created by:
 * Titanium.UI.createImageView({...});
 */
class TiUIImageView : public TiUIBase
{
public:
    static TiUIImageView* createImageView(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIImageView();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIImageView(NativeObjectFactory* nativeObjectFactory);
};


#endif /* TIUIIMAGEVIEW_H_ */
