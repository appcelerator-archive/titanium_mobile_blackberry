/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICASCADESEVENTHANDLER_H_
#define TICASCADESEVENTHANDLER_H_

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include "bb/cascades/imageview"

class TiEventContainer;

/*
 * TiCascadesEventHandler
 *
 * Cascades generic event handler
 */

class TiCascadesEventHandler : public QObject
{
    Q_OBJECT

public:
    TiCascadesEventHandler(TiEventContainer* eventContainer);
    virtual ~TiCascadesEventHandler();
    TiEventContainer* getEventContainer() const;

public slots:
    void valueChanging(float value);
    void valueChanged(float value);
    void clicked();
    void imageChanged(const bb::cascades::Image);
    void textChanging(QString str);
    void selectedIndexChanged(int index);

private:
    TiEventContainer* eventContainer_;
};

#endif /* TICASCADESEVENTHANDLER_H_ */
