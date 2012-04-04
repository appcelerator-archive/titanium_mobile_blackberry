/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"

TiUIBase::TiUIBase()
{
    cascadesApp_=NULL;
}

TiUIBase::~TiUIBase()
{
}

TiUIBase::TiUIBase(TiCascadesApp& app,const char* name):
        TiObject(name)
{
    cascadesApp_=&app;
}

TiCascadesApp* TiUIBase::getCascadesApp() const
{
    return cascadesApp_;
}

bool TiUIBase::canAddMembers() const
{
    return true;
}
