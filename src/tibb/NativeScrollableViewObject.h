/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESCROLLABLEVIEWOBJECT_H_
#define NATIVESCROLLABLEVIEWOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include <iostream>


/*
 * NativeScrollableViewObject
 *
 * UI: ScrollableView control
 */
class TiScrollableView;

class NativeScrollableViewObject : public NativeControlObject
{
public:
    static NativeScrollableViewObject* createScrollableView(TiObject* tiObject);
    virtual ~NativeScrollableViewObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual int addChildNativeObject(NativeObject* obj);
    virtual void updateLayout(QRectF rect);
    virtual int setViews(TiObject* obj);

    virtual int setCurrentPage(TiObject* obj);
    virtual int setDisableBounce(TiObject* obj);
    virtual int setOverScrollMode(TiObject* obj);
    virtual int setOverlayEnabled(TiObject* obj);
    virtual int setPagingControlAlpha(TiObject* obj);
    virtual int setPagingControlColor(TiObject* obj);
    virtual int setPagingControlHeight(TiObject* obj);
    virtual int setPagingControlOnTop(TiObject* obj);
    virtual int setPagingControlTimeout(TiObject* obj);
    virtual int setScrollingEnabled(TiObject* obj);
    virtual int setShowPagingControl(TiObject* obj);

    virtual void scrollToIndex(int index, bool animated);
    virtual void scrollToView(NativeObject *view, bool animated);

    virtual void moveNext();
    virtual void movePrevious();


protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeScrollableViewObject(TiObject* tiObject);
    NativeScrollableViewObject(const NativeScrollableViewObject&);
    void operator=(const NativeScrollableViewObject&);
    TiScrollableView *scrollableView_;
    QList<NativeObject*>allViews_;
};


//Event handler for button object
class ScrollableViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ScrollableViewEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ScrollableViewEventHandler() {}

public slots:
    void clicked()
    {
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    ScrollableViewEventHandler(const ScrollableViewEventHandler& eHandler);
    ScrollableViewEventHandler& operator=(const ScrollableViewEventHandler& eHandler);
};

#endif /* NATIVEBUTTONOBJECT_H_ */
