/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumRuntime.h"
#include <stdio.h>
#include <string.h>
#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include <bb/cascades/Event>
#include <bb/cascades/UiObject>
#include <bb/cascades/Control>

#include <bb/cascades/Application>
#include "TiRootObject.h"
#include "TiTitaniumObject.h"
#include "TiCascadesApp.h"
#include "NativeObjectFactory.h"

TitaniumRuntime::TitaniumRuntime()
{
    javaScript_ = NULL;
}

TitaniumRuntime::TitaniumRuntime(const char* javaScript)
{
    javaScript_ = new char[strlen((javaScript == NULL) ? "" : javaScript) + 1];
    strcpy(javaScript_, (javaScript == NULL) ? "" : javaScript);
}

TitaniumRuntime::~TitaniumRuntime()
{
    if (javaScript_ != NULL)
    {
        delete[] javaScript_;
    }
}

int TitaniumRuntime::run(const char* javaScript, int argc, char** argv)
{
    TitaniumRuntime ti(javaScript);
    return ti.internalRun(argc, argv);
}

int TitaniumRuntime::internalRun(int argc, char** argv)
{
    TiRootObject* obj;
    obj = TiRootObject::createRootObject();
    rootObject_.attachTiObject(obj);
    bb::cascades::Application app(argc, argv);
    TiCascadesApp mainApp;
    mainApp.initializeApp();
    NativeObjectFactory objFactory(&mainApp);
    obj->executeScript(&objFactory, javaScript_);
    mainApp.setScene();
    // TODO: implement a message pump here
    return bb::cascades::Application::exec();
}

void TitaniumRuntime::Log(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
}
