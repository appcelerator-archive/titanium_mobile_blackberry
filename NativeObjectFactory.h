/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECTFACTORY_H_
#define NATIVEOBJECTFACTORY_H_

class NativeObject;
class NativeContainerObject;
class TiCascadesApp;

class NativeObjectFactory
{
public:
    NativeObjectFactory(TiCascadesApp* cascadesApp);
    virtual ~NativeObjectFactory();
    NativeObject* createNativeObject(int type);
    NativeObject* getRootContainer() const;
private:
    TiCascadesApp* cascadesApp_;
    NativeContainerObject* rootContainer_;
};

#endif /* NATIVEOBJECTFACTORY_H_ */
