/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TICASCADESAPP_H_
#define TICASCADESAPP_H_

#ifndef _WIN32
#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include <bb/cascades/Event>
#include <bb/cascades/UiObject>
#include <bb/cascades/Control>
#include <bb/cascades/Container>
#include <bb/cascades/Application>
#else
#define Q_OBJECT
class QObject
{
};
#endif

typedef void* UIHANDLE;

class TiCascadesApp : public QObject
{
    Q_OBJECT
public:
    TiCascadesApp();
    virtual ~TiCascadesApp();
    void initializeApp();
    void setScene();
    void setBackgroundColor(UIHANDLE container,const char* color);
    UIHANDLE createContainer();
    void addContainerToAppContainer(UIHANDLE container);
private:
    UIHANDLE appContainer_;
};

#endif /* TICASCADESAPP_H_ */
