/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBASE_H_
#define TIBASE_H_

/*
 * TiBase
 *
 * Base class for all objects that need to be reference counted.  It is the base
 * class of all TiObjects and NativeObjects.
 *
 * NOTE: The refcount is initialized at 1 in the ctor and when the last
 * reference is released the object is deleted.
 */

class TiBase
{
public:
    virtual void addRef();
    virtual void release();

protected:
    TiBase();
    virtual ~TiBase();

private:
    int refCount_;
};

#endif /* TIBASE_H_ */
