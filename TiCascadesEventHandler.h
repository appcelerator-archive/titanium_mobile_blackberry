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
class NativeListViewObject;

/*
 * TiCascadesEventHandler
 *
 * Cascades generic event handler
 */

class TiCascadesEventHandler : public QObject
{
    Q_OBJECT

public:
    //TODO need to implement event handler for each native controller and pass controller to each event handler
    TiCascadesEventHandler(TiEventContainer* eventContainer, NativeListViewObject* owner = NULL);
    virtual ~TiCascadesEventHandler();
    TiEventContainer* getEventContainer() const;

public slots:
    void valueChanging(float value);
    void valueChanged(float value);
    void clicked();
    void imageChanged(const bb::cascades::Image);
    void textChanging(QString str);
    void selectedIndexChanged(int index);
    void selectionChanged(QVariantList var, bool b);

private:
    TiEventContainer* eventContainer_;
    NativeListViewObject* owner_;
};

#endif /* TICASCADESEVENTHANDLER_H_ */
