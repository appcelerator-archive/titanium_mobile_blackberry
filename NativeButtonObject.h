/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEBUTTONOBJECT_H_
#define NATIVEBUTTONOBJECT_H_

#include "NativeControlObject.h"
#include "TiCascadesEventHandler.h"
#include <bb/cascades/Button>

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
    virtual int setLabel(const char* text);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();

private:
    bb::cascades::Button* button_;
    TiEventContainer* eventClick_;
    TiCascadesEventHandler* eventHandler_;
};

#endif /* NATIVEBUTTONOBJECT_H_ */
