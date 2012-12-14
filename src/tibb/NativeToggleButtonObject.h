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
    static NativeToggleButtonObject* createToggleButton(TiObject* tiObject);
    virtual int getObjectType() const;
    virtual int initialize();
    virtual int setValue(TiObject* value);
    void updateValue(bool value);

protected:
    virtual ~NativeToggleButtonObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeToggleButtonObject(TiObject* tiObject);
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
    explicit ToggleButtonEventHandler(TiEventContainer* eventContainer, NativeToggleButtonObject* owner)
    {
        Q_ASSERT(owner);
        owner_ = owner;
        owner_->addRef();
        eventContainer_ = eventContainer;
    }

    virtual ~ToggleButtonEventHandler()
    {
        Q_ASSERT(owner_);
        owner_->release();
    }

public slots:
    void checkedChanged(bool value)
    {
        owner_->updateValue(value);
        eventContainer_->setDataProperty("value", value);
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;
    NativeToggleButtonObject* owner_;

    // Disable copy ctor & assignment operator
    ToggleButtonEventHandler(const ToggleButtonEventHandler& eHandler);
    ToggleButtonEventHandler& operator=(const ToggleButtonEventHandler& eHandler);
};

#endif /* NATIVETOGGLEBUTTONOBJECT_H_ */
