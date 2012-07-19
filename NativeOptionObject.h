/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOPTIONOBJECT_H_
#define NATIVEOPTIONOBJECT_H_

#include "NativeObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class Option;
}
}

/*
 * NativeOptionObject
 *
 * UI: Option
 */
class NativeOptionObject : public NativeObject
{
public:
    static NativeOptionObject* createOption();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int setText(const char* text);

protected:
    virtual ~NativeOptionObject();

private:
    explicit NativeOptionObject();
    // Disable copy ctor & assignment operator
    NativeOptionObject(const NativeOptionObject& dropdown);
    NativeOptionObject& operator=(const NativeOptionObject& dropdown);
    // Class members
    bb::cascades::Option* option_;
};

#endif /* NATIVEOPTIONOBJECT_H_ */
