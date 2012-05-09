/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEIMAGEVIEWOBJECT_H_
#define NATIVEIMAGEVIEWOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class ImageView;
}
}

class TiCascadesEventHandler;

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
    TiCascadesEventHandler* eventHandler_;
    float left_;
    float top_;
};

#endif /* NATIVEIMAGEVIEWOBJECT_H_ */
