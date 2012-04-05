/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "TiCascadesApp.h"
#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/Color>
#include "TiUtility.h"



using namespace bb::cascades;

TiCascadesApp::TiCascadesApp()
{
    appContainer_=NULL;
}

TiCascadesApp::~TiCascadesApp()
{
    if(appContainer_!=NULL)
    {
        delete (Container*)appContainer_;
        appContainer_=NULL;
    }
}
void TiCascadesApp::initializeApp()
{
    appContainer_=new Container();
    ((Container*)appContainer_)->setLayout(new DockLayout());
}

void TiCascadesApp::setScene()
{
    Application::setScene((Container*)appContainer_);
}

void TiCascadesApp::setBackgroundColor(UIHANDLE container,const char* color)
{
    float r;
    float g;
    float b;
    float a;
    TiUtility::convertHTMLStringToColorComponents(color,&r,&g,&b,&a);
    Container* ct=(Container*)container;
    if(ct==NULL)
    {
        ct=(Container*)appContainer_;
    }
    ct->setBackground(*(new Color(r,g,b,a)));
}

UIHANDLE TiCascadesApp::createContainer()
{
    return new Container();
}

void TiCascadesApp::addContainerToAppContainer(UIHANDLE container)
{
    Container* ctn=(Container*)container;
    ((Container*)appContainer_)->add(ctn);
}
