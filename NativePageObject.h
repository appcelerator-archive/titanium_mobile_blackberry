/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NativePageObject_H_
#define NativePageObject_H_

#include "NativeControlObject.h"

class NativeObjectFactory;

namespace bb
{
namespace cascades
{
class Page;
}
}

/*
 * NativePageObject
 *
 * UI: Container (Window)
 */

class NativePageObject : public NativeControlObject
{
public:
    static NativeObject* createPage(TiObject* tiObject, NativeObjectFactory* nativeObjectFactory);
    virtual ~NativePageObject();
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int open();
    virtual int removeChildNativeObject(NativeObject* obj);

protected:
    virtual int initialize();

private:
    NativeObjectFactory* nativeObjectFactory_;
    bb::cascades::Page* page_;

    explicit NativePageObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativePageObject(const NativePageObject& obj);
    NativePageObject& operator=(const NativePageObject& obj);
};

#endif /* NativePageObject_H_ */
