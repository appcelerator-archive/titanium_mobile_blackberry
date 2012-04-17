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
    Q_SLOT
    void valueChanging(float value);
    Q_SLOT
    void valueChanged(float value);
    Q_SLOT
    void clicked();

private:
    TiEventContainer* eventContainer_;
};

#endif /* TICASCADESEVENTHANDLER_H_ */
