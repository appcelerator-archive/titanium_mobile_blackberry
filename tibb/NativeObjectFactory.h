/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECTFACTORY_H_
#define NATIVEOBJECTFACTORY_H_

#include "TiEventContainerFactory.h"

class NativeObject;
class NativePageObject;
class NativeStringInterface;
class TiCascadesApp;
class TiObject;

/*
 * NativeObjectFactory
 *
 * Creates native control objects
 *
 */

class NativeObjectFactory
{
public:
    NativeObjectFactory(TiCascadesApp* cascadesApp);
    virtual ~NativeObjectFactory();
    NativeObject* createNativeObject(int type, TiObject* tiObj);
    NativeObject* getRootContainer() const;
    void setRootContainer(NativeObject* container);
    void setEventContainerFactory(TiEventContainerFactory* eventContainerFactory);
    TiEventContainerFactory* getEventContainerFactory() const;
    TiCascadesApp* getCascadeApp()
    {
        return cascadesApp_;
    }

    static const NativeStringInterface* getNativeStringInterface();

private:
    TiCascadesApp* cascadesApp_;
    NativeObject* rootContainer_;
    TiEventContainerFactory* eventContainerFactory_;
};

#endif /* NATIVEOBJECTFACTORY_H_ */
