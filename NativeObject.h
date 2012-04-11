/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECT_H_
#define NATIVEOBJECT_H_

typedef void* NAHANDLE;

#define NATIVE_ERROR_OK                 0
#define NATIVE_ERROR_NOTSUPPORTED       1
#define NATIVE_ERROR_OUTOFMEMORY        2
#define NATIVE_ERROR_INVALID_ARG        3

#define NO_TYPE_CONTAINER               1
#define NO_TYPE_WINDOW                  2
#define NO_TYPE_LABEL                   3

#define N_PROP_SET_UNDEFINED                    0
#define N_PROP_SET_ANCHOR_POINT                 1
#define N_PROP_SET_ANIMATED_CENTER_POINT        2
#define N_PROP_SET_BACKGROUND_COLOR             3
#define N_PROP_SET_BACKGROUND_DISABLED_COLOR    4
#define N_PROP_SET_BACKGROUND_DISABLED_IMAGE    5
#define N_PROP_SET_BACKGROUND_FOCUSED_COLOR     6
#define N_PROP_SET_TEXT                         7
#define N_PROP_SET_TEXT_ALIGN                   8

class NativeObjectFactory;
/*
 * Abstract class that represents a native object.
 */
class NativeObject
{
public:
    virtual void addRef();
    virtual void release();
    virtual int getObjectType() const=0;
    virtual int setPropertyValue(int propertyNumber, const char* value);
    virtual int addChildNativeObject(NativeObject* obj);
    virtual NAHANDLE getNativeHandle() const;
    virtual int open();
    virtual void completeInitialization();
    virtual int isInitializationComplete() const;
protected:
    NativeObject();
    virtual ~NativeObject();
    virtual int initialize();
    friend class NativeObjectFactory;
private:
    int refCount_;
    int isInitializationComplete_;
};

#endif /* NATIVEOBJECT_H_ */
