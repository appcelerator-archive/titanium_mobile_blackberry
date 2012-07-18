/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESLIDEROBJECT_H_
#define NATIVESLIDEROBJECT_H_

#include "NativeControlObject.h"

namespace bb
{
namespace cascades
{
class Slider;
}
}


/*
 * NativeSliderObject
 *
 * UI: Slider control
 */

class NativeSliderObject : public NativeControlObject
{
public:
    NativeSliderObject();
    virtual ~NativeSliderObject();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual int setMax(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setValue(TiObject* obj);

private:
    bb::cascades::Slider* slider_;
};

//Event handler for slider object
class SliderEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit SliderEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~SliderEventHandler() {}

public slots:
    void valueChanging(float value)
    {
        eventContainer_->setDataProperty("value", value);
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    SliderEventHandler(const SliderEventHandler& eHandler);
    SliderEventHandler& operator=(const SliderEventHandler& eHandler);
};

#endif /* NATIVESLIDEROBJECT_H_ */
