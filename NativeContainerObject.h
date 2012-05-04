/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTAINEROBJECT_H_
#define NATIVECONTAINEROBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/Container>

class NativeObjectFactory;

/*
 * NativeContainerObject
 *
 * UI: Container (Window)
 */

class NativeContainerObject : public NativeControlObject
{
public:
    static NativeObject* createContainer(NativeObjectFactory* nativeObjectFactory);
    NativeContainerObject();
    NativeContainerObject(bb::cascades::Container* container);
    virtual ~NativeContainerObject();
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int open();
    virtual int setBackgroundColor(TiObject* obj);

protected:
    virtual int initialize(TiEventContainerFactory* containerFactory);

private:
    bb::cascades::Container* container_;
    NativeObjectFactory* nativeObjectFactory_;
};

#endif /* NATIVECONTAINEROBJECT_H_ */
