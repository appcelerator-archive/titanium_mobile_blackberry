/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TILOCALEOBJECT_H_
#define TILOCALEOBJECT_H_

#include "LocaleParser.h"

#include "TiProxy.h"

/*
 * TiLocaleObject
 *
 * Locale module containing stream utility methods.
 */
class TiLocaleObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static Handle<Value> _getString(void*, TiObject*, const Arguments& args);

protected:
    virtual ~TiLocaleObject();
    virtual void onCreateStaticMembers();

private:
    TiLocaleObject();
    TiLocaleObject(const TiLocaleObject&);
    TiLocaleObject& operator=(const TiLocaleObject&);
    static Handle<Value> _getCurrentLanguage(void*, TiObject*, const Arguments& args);
    static Handle<Value> _getCurrentCountry(void*, TiObject*, const Arguments& args);
    static Handle<Value> _getCurrentLocale(void*, TiObject*, const Arguments& args);
    static Handle<Value> _getCurrentLanguage();
    static Handle<Value> _getCurrentCountry();
    static Handle<Value> _getCurrentLocale();
};

#endif /* TILOCALEOBJECT_H_ */
