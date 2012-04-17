/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTAINEROBJECT_H_
#define NATIVECONTAINEROBJECT_H_

#include "NativeObject.h"
#include <bb/cascades/Container>

class NativeContainerObject : public NativeObject
{
public:
    static NativeObject* createContainer(NativeContainerObject* root);
    NativeContainerObject();
    NativeContainerObject(bb::cascades::Container* container);
    virtual ~NativeContainerObject();
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int open();
    void setRootContainer(NativeContainerObject* root);
protected:
    virtual int initialize();
private:
    bb::cascades::Container* container_;
    NativeContainerObject* root_;
};

#endif /* NATIVECONTAINEROBJECT_H_ */
