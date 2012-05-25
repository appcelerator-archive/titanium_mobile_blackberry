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

class TiEventContainer;
class ButtonEventHandler;

/*
 * NativeButtonObject
 *
 * UI: Button control
 */

class NativeButtonObject : public NativeControlObject
{
public:
    NativeButtonObject();
    virtual ~NativeButtonObject();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;
    virtual int setTitle(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();

private:
    bb::cascades::Button* button_;
    TiEventContainer* eventClick_;
    ButtonEventHandler* eventHandler_;
};


//Event handler for button object
class ButtonEventHandler : public QObject
{
    Q_OBJECT

public:
    ButtonEventHandler(TiEventContainer* eventContainer)
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
