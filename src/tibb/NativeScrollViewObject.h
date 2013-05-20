/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESCROLLVIEWOBJECT_H_
#define NATIVESCROLLVIEWOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include <QtCore/QSize>

namespace bb
{
namespace cascades
{
class ScrollView;
class Container;
class Button;
class ScrollViewEventHandler;
class LayoutUpdateHandler;
class ScrollViewProperties;
}
}
class NativeScrollViewObject;


/*
 * NativeScrollViewObject
 *
 * UI: ScrollView control
 */

class NativeScrollViewContentObject : public NativeControlObject
{
public:
    explicit NativeScrollViewContentObject(TiObject* tiObject, NativeScrollViewObject* scrollView);
    virtual void updateLayout(QRectF rect);
    NativeScrollViewObject *scrollView_;
};

class NativeScrollViewObject : public NativeControlObject
{
public:
    static NativeScrollViewObject* createScrollView(TiObject* tiObject);
    virtual ~NativeScrollViewObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual void updateLayout(QRectF rect);
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int setContentWidth(TiObject *obj);
    virtual int setContentHeight(TiObject *obj);
    virtual int setBackgroundColor(TiObject *obj);
    virtual int setLayout(TiObject *obj);
    void setContentWidthAndHeight(float w, float h);
    bb::cascades::ScrollViewProperties* scrollViewProperties_;
    bb::cascades::ScrollView* scrollView_;
    bb::cascades::Container* contentView_;
    bb::cascades::Container* nativeContentView_;
    NativeScrollViewContentObject *contentViewProxy_;



    void onContentViewSizeChange(QRectF rect);
protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeScrollViewObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeScrollViewObject(const NativeScrollViewObject&);
    void operator=(const NativeScrollViewObject&);
    QSize contentSize_;
    QSize scrollViewSize_;
    bool contentWidthSet_;
    bool contentHeightSet_;
};


class ScrollViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ScrollViewEventHandler(NativeScrollViewObject* owner)
    {
        owner_ = owner;
    }
    virtual ~ScrollViewEventHandler() {}

public slots:
    void onContainerLayoutChange(QRectF rect)
    {
    	owner_->onContentViewSizeChange(rect);
    }
private:
	NativeScrollViewObject *owner_;
};


/*
//Event handler for button object
class ButtonEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ButtonEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ButtonEventHandler() {}

public slots:
    void clicked()
    {
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    ButtonEventHandler(const ButtonEventHandler& eHandler);
    ButtonEventHandler& operator=(const ButtonEventHandler& eHandler);
};
 */
#endif /* NATIVESCROLLVIEWOBJECT_H_ */
