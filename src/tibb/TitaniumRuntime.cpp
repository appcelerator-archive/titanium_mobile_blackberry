/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumRuntime.h"

#include "NativeObject.h"
#include "NativeObjectFactory.h"
#include "TiCascadesApp.h"
#include "TiLogger.h"
#include "TiRootObject.h"
#include "TiTitaniumObject.h"

#include <bb/cascades/Application>
#include <bb/cascades/Control>
#include <bb/cascades/Event>
#include <bb/cascades/UIObject>
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <stdio.h>
#include <string.h>

TitaniumRuntime* TitaniumRuntime::runtime = 0;

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
    runtime = &ti;  // Note this pointer will be invalid once we return.
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
    objectFactory_ = &objFactory;
    mainApp_ = &mainApp;
    TiLogger::initialize(&objFactory);
    int ret = obj->executeScript(&objFactory, javaScript_, messageLoop, this);
    // TODO: handle non-zero return code here
    TiLogger::deleteInstance();
    obj->release();
    return ret;
}

int TitaniumRuntime::messageLoop(void* context)
{
    TitaniumRuntime* self = (TitaniumRuntime*)context;
    NativeObject* nativeObject = self->objectFactory_->getRootContainer();
    self->mainApp_->setScene(nativeObject);
    if (nativeObject != NULL)
    {
        nativeObject->release();
    }
    return bb::cascades::Application::exec();
}
