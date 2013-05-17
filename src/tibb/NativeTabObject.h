/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETABOBJECT_H_
#define NATIVETABOBJECT_H_

#include "NativeControlObject.h"

#include <QPointer>

#include <bb/cascades/TabbedPane>

class NativeObjectFactory;
namespace bb
{
namespace cascades
{
class ActionItem;
class NavigationPane;
class Page;
class Tab;
}
}

/*
 * NativeTabObject
 *
 * UI: Tab container
 */

class NativeTabObject : public NativeControlObject
{
public:
    static NativeObject* createTab(TiObject* tiObject);
    virtual ~NativeTabObject();

    virtual NATIVE_TYPE getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;

    virtual int addChildNativeObject(NativeObject* obj);
    virtual int openWindowOnTab(NativeObject* obj);

    virtual int setActive(TiObject* obj);
    virtual int setIcon(TiObject* obj);
    virtual int setTitle(TiObject* obj);
	virtual int setDescription(TiObject* obj);

    virtual int isActive(TiObject* obj);

protected:
    virtual int initialize();

    void setTabbedPane(bb::cascades::TabbedPane* pane) {
        tabPane_ = pane;
    }

private:
    bb::cascades::NavigationPane* navigationPane_;
    bb::cascades::Tab* tab_;
    QPointer<bb::cascades::TabbedPane> tabPane_;

    explicit NativeTabObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeTabObject(const NativeTabObject& obj);
    NativeTabObject& operator=(const NativeTabObject& obj);

friend class NativeTabGroupObject;
};


#endif /* NATIVETABOBJECT_H_ */
