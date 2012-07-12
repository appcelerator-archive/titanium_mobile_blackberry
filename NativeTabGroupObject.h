/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETABGROUPOBJECT_H_
#define NATIVETABGROUPOBJECT_H_

#include "NativeControlObject.h"

class NativeObjectFactory;
namespace bb
{
namespace cascades
{
class TabbedPane;
}
}

/*
 * NativeTabGroupObject
 *
 * UI: Tab Group control
 */

class NativeTabGroupObject : public NativeControlObject
{
public:
    static NativeObject* createTabGroup(NativeObjectFactory* nativeObjectFactory);
    virtual ~NativeTabGroupObject();
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int setActiveTab(NativeObject* tab);
    virtual int setActiveTab(int index);
    virtual int open();

protected:
    virtual int initialize(TiEventContainerFactory* containerFactory);

private:
    NativeObjectFactory* nativeObjectFactory_;
    bb::cascades::TabbedPane* tabGroup_;

    NativeTabGroupObject();
    // Disable copy ctor & assignment operator
    NativeTabGroupObject(const NativeTabGroupObject& obj);
    NativeTabGroupObject& operator=(const NativeTabGroupObject& obj);
};

#endif /* NATIVETABGROUPOBJECT_H_ */
