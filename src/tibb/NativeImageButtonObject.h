/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEIMAGEBUTTONOBJECT_H_
#define NATIVEIMAGEBUTTONOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>

namespace bb
{
namespace cascades
{
class ImageButton;
}
}


/*
 * NativeImageButtonObject
 *
 * UI: ImageButton control
 */

class NativeImageButtonObject : public NativeControlObject
{
public:
    static NativeImageButtonObject* createButton(TiObject* tiObject);
    virtual ~NativeImageButtonObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual int setTitle(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual int setImageDisabled(TiObject* obj);
    virtual int setImagePressed(TiObject* obj);
    virtual int setEnabled(TiObject* obj);
    virtual void updateLayout(QRectF rect);

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeImageButtonObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeImageButtonObject(const NativeImageButtonObject&);
    void operator=(const NativeImageButtonObject&);

    bb::cascades::ImageButton* button_;
};


//Event handler for button object
class ImageButtonEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ImageButtonEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ImageButtonEventHandler() {}

public slots:
    void clicked()
    {
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    ImageButtonEventHandler(const ImageButtonEventHandler& eHandler);
    ImageButtonEventHandler& operator=(const ImageButtonEventHandler& eHandler);
};

#endif /* NATIVEBUTTONOBJECT_H_ */
