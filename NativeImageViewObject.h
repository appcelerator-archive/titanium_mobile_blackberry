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


class NativeImageViewObject : public NativeControlObject
{
public:
    static NativeImageViewObject* createImageView();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual int setImage(TiObject* obj);

protected:
    virtual ~NativeImageViewObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    NativeImageViewObject();
    // Disable copy ctor and assignment operator
    NativeImageViewObject(const NativeImageViewObject& obj);
    NativeImageViewObject& operator=(const NativeImageViewObject& obj);

    bb::cascades::ImageView* imageView_;
    float left_;
    float top_;
};

//Event handler for ImageView object
class ImageViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ImageViewEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ImageViewEventHandler() {}

public slots:
    void imageChanged(const bb::cascades::Image/* image*/)
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
