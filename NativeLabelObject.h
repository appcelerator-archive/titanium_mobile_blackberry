/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELABELOBJECT_H_
#define NATIVELABELOBJECT_H_

#include "NativeAbstractTextControlObject.h"
#include <bb/cascades/Label>

/*
 * NativeLabelObject
 *
 * UI: Label control
 */

class NativeLabelObject : public NativeAbstractTextControlObject
{
public:
    static NativeLabelObject* createLabel();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;

protected:
    virtual ~NativeLabelObject();

private:
    explicit NativeLabelObject();
    // Disable copy ctor & assignment operator
    NativeLabelObject(const NativeLabelObject& indicator);
    NativeLabelObject& operator=(const NativeLabelObject& indicator);
    bb::cascades::Label* label_;
};

#endif /* NATIVELABELOBJECT_H_ */
