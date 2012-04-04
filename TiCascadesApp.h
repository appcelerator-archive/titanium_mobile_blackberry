/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TICASCADESAPP_H_
#define TICASCADESAPP_H_

#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include <bb/cascades/Event>
#include <bb/cascades/UiObject>
#include <bb/cascades/Control>
#include <bb/cascades/Container>
#include <bb/cascades/Application>

class TiCascadesApp : public QObject
{
    Q_OBJECT
public:
    TiCascadesApp();
    virtual ~TiCascadesApp();
    void initializeApp();
    void setScene();
    void setBackgroundColor(unsigned int color);
    void setBackgroundColor(const char* color);
    void* createContainer();
    void addContainerToAppContainer(void* container);
private:
    bb::cascades::Container* appContainer_;
};

#endif /* TICASCADESAPP_H_ */
