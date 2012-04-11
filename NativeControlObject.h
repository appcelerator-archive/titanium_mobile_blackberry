/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTROLOBJECT_H_
#define NATIVECONTROLOBJECT_H_

#include "NativeObject.h"
#include <bb/cascades/Control>

//typedef int (*NATIVECONTROL_SETPROP_CALLBACK)(NativeControlObject*,const char*);

class NativeControlObject : public NativeObject
{
public:
    NativeControlObject();
    virtual ~NativeControlObject();
    virtual int setPropertyValue(int propertyNumber, const char* value);

    virtual int setBackgroundColor(const char* text);
    virtual int setText(const char* text);
    virtual int setTextAlign(const char* align);
protected:
    virtual bb::cascades::Control* getControl() const;
    virtual void setControl(bb::cascades::Control* control);
private:
    bb::cascades::Control* control_;
};

#endif /* NATIVECONTROLOBJECT_H_ */
