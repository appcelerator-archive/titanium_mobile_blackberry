/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITEXTFIELD_H_
#define TIUITEXTFIELD_H_

#include "TiUIBase.h"

/*
 * TiUITextField
 *
 * Represents a Titanium TextField object
 *
 * This object can be created by:
 * Titanium.UI.createTextField({...});
 */
class TiUITextField : public TiUIBase
{
public:
    static TiUITextField* createTextField(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUITextField();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUITextField(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUITEXTFIELD_H_ */
