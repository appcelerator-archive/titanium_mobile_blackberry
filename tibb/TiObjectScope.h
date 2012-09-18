/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIOBJECTSCOPE_H_
#define TIOBJECTSCOPE_H_

class TiBase;

/*
 * TiObjectScope
 *
 * A helper class for managing reference counting by scope
 */

class TiObjectScope
{
public:
    TiObjectScope();
    TiObjectScope(TiBase* obj);
    TiObjectScope(const TiObjectScope& scope);
    virtual ~TiObjectScope();
    const TiObjectScope& operator =(const TiObjectScope& scope);
    operator TiBase* () const;
    TiBase* operator ->() const;
    void attachTiObject(TiBase* obj);
    TiBase* detachTiObject();

private:
    TiBase* object_;
};

#endif /* TIOBJECTSCOPE_H_ */
