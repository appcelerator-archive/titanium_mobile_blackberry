/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIANNOTATIONOBJECT_H_
#define TIANNOTATIONOBJECT_H_

#include "TiUIBase.h"

/*
 * TiAnnotationObject
 *
 * Represents a Titanium AnnotationObject object
 *
 */

class TiAnnotationObject: public TiUIBase
{
public:
    static TiAnnotationObject* createAnnotationObject(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiAnnotationObject();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiAnnotationObject();
};

#endif /* TIANNOTATIONOBJECT_H_ */
