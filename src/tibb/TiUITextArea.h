/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITEXTAREA_H_
#define TIUITEXTAREA_H_

#include "TiUIBase.h"

/*
 * TiUITextArea
 *
 * Represents a Titanium TextArea object
 *
 * This object can be created by:
 * Titanium.UI.createTextArea({...});
 */
class TiUITextArea : public TiUIBase
{
public:
    static TiUITextArea* createTextArea(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUITextArea();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUITextArea();

    //This class is neither copy-constructible nor assignable
    TiUITextArea(const TiUITextArea& obj);
    TiUITextArea& operator=(const TiUITextArea& obj);
};

#endif /* TIUITEXTAREA_H_ */
