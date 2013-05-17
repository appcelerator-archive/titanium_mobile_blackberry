/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIFILESYSTEMOBJECT_H_
#define TIFILESYSTEMOBJECT_H_

#include "TiProxy.h"

/*
 * TiFilesystemObject
 *
 * Object that represents name space: Titanium.Filesystem
 */

enum TI_FILESYSTEM_PATHS
{
    TI_FILESYSTEM_RESOURCES,
    TI_FILESYSTEM_TEMP,
    TI_FILESYSTEM_DATA
};

class TiFilesystemObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiFilesystemObject();
    virtual void onCreateStaticMembers();

private:
    TiFilesystemObject(NativeObjectFactory* objectFactory);
    TiFilesystemObject(const TiFilesystemObject&);
    TiFilesystemObject& operator=(const TiFilesystemObject&);

    static Handle<Value> getDataDirectory();
    static Handle<Value> getTempDirectory();
    static Handle<Value> getResourcesDirectory();
    static Handle<Value> _getFile(void*, TiObject*, const Arguments&);

    NativeObjectFactory* _objectFactory;
};

#endif /* TIFILESYSTEMOBJECT_H_ */
