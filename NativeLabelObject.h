/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELABELOBJECT_H_
#define NATIVELABELOBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/Label>

/*
 * NativeLabelObject
 *
 * UI: Label control
 */

class NativeLabelObject : public NativeControlObject
{
public:
    static NativeLabelObject* createLabel();
    virtual int getObjectType() const;
    virtual int setText(const char* text);
    virtual int setColor(const char* color);
    virtual int setTextAlign(const char* align);
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual void completeInitialization();
    virtual NAHANDLE getNativeHandle() const;

protected:
    NativeLabelObject();
    virtual ~NativeLabelObject();

private:
    bb::cascades::Label* label_;
};

#endif /* NATIVELABELOBJECT_H_ */
