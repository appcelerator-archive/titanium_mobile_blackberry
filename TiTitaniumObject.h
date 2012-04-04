/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITITANIUMOBJECT_H_
#define TITITANIUMOBJECT_H_

#include "TiObject.h"

class TiCascadesApp;

class TiTitaniumObject : public TiObject
{
public:
    static TiObject* createObject(TiCascadesApp& cascadesApp);
protected:
    virtual ~TiTitaniumObject();
    virtual void onCreateStaticMembers();
	virtual bool canAddMembers() const;
private:
    TiTitaniumObject();
    TiCascadesApp* cascadesApp_;
};

#endif /* TITITANIUMOBJECT_H_ */
