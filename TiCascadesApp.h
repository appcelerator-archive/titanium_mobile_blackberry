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
#include <bb/cascades/Container>
#else
#define Q_OBJECT
class QObject
{
};
#endif

class TiCascadesApp : public QObject
{
Q_OBJECT
public:
    TiCascadesApp();
    virtual ~TiCascadesApp();
    void initializeApp();
    void setScene();
#ifndef _WIN32
    bb::cascades::Container* appContainer_;
#endif
};

#endif /* TICASCADESAPP_H_ */
