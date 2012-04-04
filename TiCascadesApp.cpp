/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "TiCascadesApp.h"
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
        delete appContainer_;
        appContainer_=NULL;
    }
}
void TiCascadesApp::initializeApp()
{
    appContainer_=new Container();
    appContainer_->setLayout(new DockLayout());
}

void TiCascadesApp::setScene()
{
    Application::setScene(appContainer_);
}

void TiCascadesApp::setBackgroundColor(unsigned int color)
{
    // TODO: there has to be a better way
    float b=(((float)(color&0x000000FF))/255.0f);
    float g=(((float)((color>>8)&0x000000FF))/255.0f);
    float r=(((float)((color>>16)&0x000000FF))/255.0f);
    //float a=(((float)((color>>24)&0x000000FF))/255.0f);
    appContainer_->setBackground(*(new Color(r,g,b,1.0f)));

}

void TiCascadesApp::setBackgroundColor(const char* color)
{
    float r;
    float g;
    float b;
    float a;
    TiUtility::convertHTMLStringToColorComponents(color,&r,&g,&b,&a);
    appContainer_->setBackground(*(new Color(r,g,b,a)));
}

void* TiCascadesApp::createContainer()
{
    return new Container();
}

void TiCascadesApp::addContainerToAppContainer(void* container)
{
    appContainer_->add((Control*)container);
}
