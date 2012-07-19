/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NativePageObject_H_
#define NativePageObject_H_

#include "NativeControlObject.h"
#include <bb/cascades/Container>
#include <bb/cascades/Page>

class NativeObjectFactory;

/*
 * NativePageObject
 *
 * UI: Container (Window)
 */

class NativePageObject : public NativeControlObject
{
public:
    static NativeObject* createPage(NativeObjectFactory* nativeObjectFactory);
    virtual ~NativePageObject();
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int open();
    virtual int removeChildNativeObject(NativeObject* obj);
    virtual int setBackgroundColor(TiObject* obj);

protected:
    virtual int initialize();

private:
    bb::cascades::Container* container_;
    NativeObjectFactory* nativeObjectFactory_;
    bb::cascades::Page* page_;

    NativePageObject();
    // Disable copy ctor & assignment operator
    NativePageObject(const NativePageObject& obj);
    NativePageObject& operator=(const NativePageObject& obj);
};

#endif /* NativePageObject_H_ */
