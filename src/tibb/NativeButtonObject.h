/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEBUTTONOBJECT_H_
#define NATIVEBUTTONOBJECT_H_

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
 * NativeButtonObject
 *
 * UI: Button control
 */

class NativeButtonObject : public NativeControlObject
{
public:
    static NativeButtonObject* createButton(TiObject* tiObject);
    virtual ~NativeButtonObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual int setTitle(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual void updateLayout(QRectF rect);

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeButtonObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeButtonObject(const NativeButtonObject&);
    void operator=(const NativeButtonObject&);

    bb::cascades::Button* button_;
};


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

#endif /* NATIVEBUTTONOBJECT_H_ */
