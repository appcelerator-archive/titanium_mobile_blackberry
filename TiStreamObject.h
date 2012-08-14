/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TISTREAMOBJECT_H_
#define TISTREAMOBJECT_H_

#include "TiProxy.h"

/*
 * TiStreamObject
 *
 * Stream module containing stream utility methods.
 */
class TiStreamObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);

protected:
    virtual ~TiStreamObject();
    virtual void onCreateStaticMembers();

private:
    TiStreamObject();
    TiStreamObject(const TiStreamObject&);
    TiStreamObject& operator=(const TiStreamObject&);

    static Handle<Value> _createStream(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TISTREAMOBJECT_H_ */
