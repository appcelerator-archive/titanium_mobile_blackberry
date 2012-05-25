/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEIMAGEVIEWOBJECT_H_
#define NATIVEIMAGEVIEWOBJECT_H_

#include "NativeControlObject.h"
#include "bb/cascades/resources/image.h"

//forward declaration
namespace bb
{
namespace cascades
{
class ImageView;
}
}

class ImageViewEventHandler;

class NativeImageViewObject : public NativeControlObject
{
public:
    static NativeImageViewObject* createImageView();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual int setImage(const char* image);
    virtual int setWidth(float width);
    virtual int setHeight(float height);
    virtual int setLeft(float left);
    virtual int setTop(float top);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();
    virtual NAHANDLE getNativeHandle() const;

protected:
    virtual ~NativeImageViewObject();

private:
    NativeImageViewObject();
    // Disable copy ctor and assignment operator
    NativeImageViewObject(const NativeImageViewObject& obj);
    NativeImageViewObject& operator=(const NativeImageViewObject& obj);
    bb::cascades::ImageView* imageView_;
    TiEventContainer* eventImageChanged_;
    ImageViewEventHandler* eventHandler_;
    float left_;
    float top_;
};

//Event handler for ImageView object
class ImageViewEventHandler : public QObject
{
    Q_OBJECT

public:
    ImageViewEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ImageViewEventHandler() {}

public slots:
    void imageChanged(const bb::cascades::Image image)
    {
        // TODO: add x, y coordinates
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    ImageViewEventHandler(const ImageViewEventHandler& eHandler);
    ImageViewEventHandler& operator=(const ImageViewEventHandler& eHandler);
};

#endif /* NATIVEIMAGEVIEWOBJECT_H_ */
