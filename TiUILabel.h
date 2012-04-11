/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUILABEL_H_
#define TIUILABEL_H_

#include "TiUIBase.h"

/*
 * Represents a Titanium label object
 *
 * This object can be created by:
 * Titanium.UI.createLabel({...});
 */
class TiUILabel : public TiUIBase
{
public:
    static TiUILabel* createLabel(NativeObjectFactory* nativeObjectFactory);
protected:
    virtual ~TiUILabel();
    virtual void initializeTiObject(TiObject* parentContext);
private:
    TiUILabel(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUILABEL_H_ */
