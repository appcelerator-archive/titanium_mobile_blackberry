/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESLIDEROBJECT_H_
#define NATIVESLIDEROBJECT_H_

#include "NativeControlObject.h"
#include "TiCascadesEventHandler.h"
#include <bb/cascades/Slider>

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
    virtual NAHANDLE getNativeHandle() const;
    virtual int setMax(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();

private:
    bb::cascades::Slider* slider_;
    TiEventContainer* eventChange_;
    TiCascadesEventHandler* eventChangeHandler_;
};

#endif /* NATIVESLIDEROBJECT_H_ */
