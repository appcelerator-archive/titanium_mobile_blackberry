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

class NativeObject;

/*
 * TiCascadesApp
 *
 * Cascades application object
 */

class TiCascadesApp : public QObject
{
Q_OBJECT
    public:
    TiCascadesApp();
    virtual ~TiCascadesApp();
    void initializeApp();
    void setScene(NativeObject* mainWindow);
};

#endif /* TICASCADESAPP_H_ */
