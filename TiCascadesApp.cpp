/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "TiCascadesApp.h"

TiCascadesApp::TiCascadesApp()
{
    appContainer_=NULL;
}

TiCascadesApp::~TiCascadesApp()
{
    if(appContainer_!=NULL)
    {
        delete appContainer_;
        appContainer_=NULL;
    }
}

void TiCascadesApp::initializeApp()
{
    appContainer_=new bb::cascades::Container();
}

void TiCascadesApp::setScene()
{
    bb::cascades::Application::setScene(appContainer_);
}
