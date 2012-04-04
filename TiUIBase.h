/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBASE_H_
#define TIUIBASE_H_

#include "TiObject.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Control>

class TiCascadesApp;

class TiUIBase : public TiObject
{
public:
protected:
    TiUIBase(TiCascadesApp& app,const char* name);
    TiUIBase();
    virtual ~TiUIBase();
    virtual TiCascadesApp* getCascadesApp() const;
    virtual bool canAddMembers() const;
private:
    TiCascadesApp* cascadesApp_;
};

#endif /* TIUIBASE_H_ */
