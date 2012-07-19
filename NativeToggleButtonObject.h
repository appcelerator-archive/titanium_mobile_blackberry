/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETOGGLEBUTTONOBJECT_H_
#define NATIVETOGGLEBUTTONOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class ToggleButton;
}
}


/*
 * NativeToggleButtonObject
 *
 * UI: Toggle Button
 */

class NativeToggleButtonObject : public NativeControlObject
{
public:
    static NativeToggleButtonObject* createToggleButton();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual void completeInitialization();
    virtual int setValue(TiObject* value);

protected:
    virtual ~NativeToggleButtonObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeToggleButtonObject();
    // Disable copy ctor & assignment operator
    NativeToggleButtonObject(const NativeToggleButtonObject& toggleButton);
    NativeToggleButtonObject& operator=(const NativeToggleButtonObject& toggleButton);

    bb::cascades::ToggleButton* toggleButton_;
};

//Event handler for toggleButton object
class ToggleButtonEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ToggleButtonEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~ToggleButtonEventHandler() {}

public slots:
    //TODO

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    ToggleButtonEventHandler(const ToggleButtonEventHandler& eHandler);
    ToggleButtonEventHandler& operator=(const ToggleButtonEventHandler& eHandler);
};

#endif /* NATIVETOGGLEBUTTONOBJECT_H_ */
