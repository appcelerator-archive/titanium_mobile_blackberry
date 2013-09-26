/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETABGROUPOBJECT_H_
#define NATIVETABGROUPOBJECT_H_

#include "NativeControlObject.h"
#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"
#include "EventHandler.h"

class NativeObjectFactory;
namespace bb
{
namespace cascades
{
class TabbedPane;
class Tab;
}
}

namespace titanium {
class Scene;
}

using namespace titanium;

/*
 * NativeTabGroupObject
 *
 * UI: Tab Group control
 */
class NativeTabGroupObject : public NativeControlObject
{
public:
    static NativeObject* createTabGroup(TiObject* tiObject, NativeObjectFactory* nativeObjectFactory);
    virtual ~NativeTabGroupObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int removeChildNativeObject(NativeObject* obj);
    virtual int setActiveTab(TiObject* obj);
    virtual int setActiveTab(NativeObject* tab);
    virtual int setActiveTab(int index);
    virtual int getActiveTab(TiObject* obj);
	virtual int setShowTabsOnActionBar(TiObject* obj);
    virtual int getTabs(TiObject* obj);
    virtual int open();

    virtual void setupEvents(TiEventContainerFactory* factory);

protected:
    virtual int initialize();

private:
    NativeObjectFactory* nativeObjectFactory_;
    bb::cascades::TabbedPane* tabGroup_;
    titanium::Scene* scene_;

    explicit NativeTabGroupObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeTabGroupObject(const NativeTabGroupObject& obj);
    NativeTabGroupObject& operator=(const NativeTabGroupObject& obj);
};

class TabGroupFocusEventHandler : public EventHandler
{
    Q_OBJECT
public:
    explicit TabGroupFocusEventHandler(TiEventContainer* container)
        : EventHandler(container) { }

public slots:
    void activeTabChanged(bb::cascades::Tab*)
    {
    	TiEventContainer* eventContainer = getEventContainer();
    	eventContainer->fireEvent();
    }
};
#endif /* NATIVETABGROUPOBJECT_H_ */
