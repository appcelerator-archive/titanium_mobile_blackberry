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

namespace bb
{
namespace cascades
{
class Button;
}
}


/*
 * NativeScrollableViewObject
 *
 * UI: Button control
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

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeScrollableViewObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeScrollableViewObject(const NativeScrollableViewObject&);
    void operator=(const NativeScrollableViewObject&);
    TiScrollableView *scrollableView_;
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
