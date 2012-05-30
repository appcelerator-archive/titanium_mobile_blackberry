/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewObject.h"
#include "TiCascadesEventHandler.h"
#include "TiEventContainer.h"
#include "bb/cascades/imageview"

TiCascadesEventHandler::TiCascadesEventHandler(TiEventContainer* eventContainer, NativeListViewObject* owner)
{
    eventContainer_ = eventContainer;
    owner_ = owner;
}

TiCascadesEventHandler::~TiCascadesEventHandler()
{
}

TiEventContainer* TiCascadesEventHandler::getEventContainer() const
{
    return eventContainer_;
}

void TiCascadesEventHandler::valueChanging(float value)
{
    eventContainer_->setDataProperty("value", value);
    eventContainer_->fireEvent();
}

void TiCascadesEventHandler::valueChanged(float value)
{
    // TODO: finish this
}

void TiCascadesEventHandler::textChanging(QString str)
{
    eventContainer_->setDataProperty("value", str.toInt());
    eventContainer_->fireEvent();
}

void TiCascadesEventHandler::selectionChanged(QVariantList var, bool b)
{
    eventContainer_->setDataProperty("index", var[0].toString().toStdString().c_str());
    QString str;
    if (owner_)
    {
        str = owner_->getListViewElementFromIndex(var);
    }
    //TODO later we may need to implement all complex data types instead of using just names, but for now it is fine
    eventContainer_->setComplexDataProperty("rowData", "title", str.toStdString().c_str());
    eventContainer_->fireEvent();
}

void TiCascadesEventHandler::clicked()
{
    // TODO: add x, y coordinates
    eventContainer_->fireEvent();
}

void TiCascadesEventHandler::imageChanged(const bb::cascades::Image image)
{
    // TODO: add x, y coordinates
    eventContainer_->fireEvent();
}

void TiCascadesEventHandler::selectedIndexChanged(int index)
{
    eventContainer_->setDataProperty("value", index);
    eventContainer_->fireEvent();
}
