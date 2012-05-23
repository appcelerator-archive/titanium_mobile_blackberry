/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTVIEWOBJECT_H_
#define NATIVELISTVIEWOBJECT_H_

#include "NativeControlObject.h"

/*
 * NativeListView
 *
 * UI: ListView control
 */

namespace bb
{
namespace cascades
{
class ListView;
};
};

class TiEventContainer;
class TiCascadesEventHandler;

class NativeListViewObject : public NativeControlObject
{
public:
    static NativeListViewObject* createListView();
    virtual int getObjectType() const;
    virtual int setTop(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setWidth(TiObject* obj);
    virtual int setData(TiObject* obj);
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual void completeInitialization();
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual QString getListViewElementFromIndex(QVariantList var);
    virtual NAHANDLE getNativeHandle() const;
    virtual int scrollToIndex(const char* index);

protected:
    virtual ~NativeListViewObject();

private:
    NativeListViewObject();
    //Not copy-constructible; Not assignable.
    NativeListViewObject(const NativeListViewObject& obj);
    NativeListViewObject& operator=(const NativeListViewObject& obj);

    bb::cascades::ListView* listView_;
    TiEventContainer* eventClicked_;
    TiCascadesEventHandler* eventHandler_;
    float left_;
    float top_;
};

#endif /* NATIVELISTVIEWOBJECT_H_ */
