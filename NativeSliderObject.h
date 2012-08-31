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
    static NativeSliderObject* createSlider(TiObject* tiObject);
    virtual ~NativeSliderObject();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual int setMax(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setValue(TiObject* obj);
    void updateValue(float value);

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeSliderObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeSliderObject(const NativeSliderObject&);
    void operator=(const NativeSliderObject&);

    bb::cascades::Slider* slider_;
};

//Event handler for slider object
class SliderEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit SliderEventHandler(TiEventContainer* eventContainer, NativeSliderObject* owner)
    {
        Q_ASSERT(owner);
        owner_ = owner;
        owner_->addRef();
        eventContainer_ = eventContainer;
    }

    virtual ~SliderEventHandler()
    {
        Q_ASSERT(owner_);
        owner_->release();
    }

public slots:
    void valueChanging(float value)
    {
        owner_->updateValue(value);
        eventContainer_->setDataProperty("value", value);
        eventContainer_->fireEvent();
    }

private:
    NativeSliderObject* owner_;
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    SliderEventHandler(const SliderEventHandler& eHandler);
    SliderEventHandler& operator=(const SliderEventHandler& eHandler);
};

#endif /* NATIVESLIDEROBJECT_H_ */
