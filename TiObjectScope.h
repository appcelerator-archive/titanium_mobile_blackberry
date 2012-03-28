/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIOBJECTSCOPE_H_
#define TIOBJECTSCOPE_H_

class TiObject;

class TiObjectScope
{
public:
    TiObjectScope();
    TiObjectScope(TiObject* obj);
    TiObjectScope(const TiObjectScope& scope);
    virtual ~TiObjectScope();
    const TiObjectScope& operator =(const TiObjectScope& scope);
    operator TiObject*() const;
    TiObject* operator ->() const;
    void attachTiObject(TiObject* obj);
    TiObject* detachTiObject();
private:
    TiObject* object_;
};

#endif /* TIOBJECTSCOPE_H_ */
