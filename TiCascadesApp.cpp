/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCascadesApp.h"
#include <bb/cascades/Application>

#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/Label>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Font>
#include <bb/cascades/Event>
#include <bb/cascades/UiObject>
#include <bb/cascades/Control>
#include <bb/cascades/Container>
#include <bb/cascades/Application>
#include <bb/cascades/StackLayout>
#include <bb/cascades/Page>
#include "TiUtility.h"

using namespace bb::cascades;

TiCascadesApp::TiCascadesApp()
{
    appContainer_ = NULL;
}

TiCascadesApp::~TiCascadesApp()
{
    if (appContainer_ != NULL)
    {
        appContainer_ = NULL;
    }
}
void TiCascadesApp::initializeApp()
{
    appContainer_ = new Container();
    appContainer_->setLayout(new DockLayout());
}

void TiCascadesApp::setScene()
{
    Page* page = new Page();
    page->setContent(appContainer_);
    Application::setScene(page);
}

