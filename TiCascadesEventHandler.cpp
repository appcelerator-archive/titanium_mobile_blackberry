/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCascadesEventHandler.h"
#include "TiEventContainer.h"

TiCascadesEventHandler::TiCascadesEventHandler(TiEventContainer* eventContainer)
{
    eventContainer_ = eventContainer;
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
}

void TiCascadesEventHandler::clicked()
{
    // TODO: add x, y coordinates
    eventContainer_->fireEvent();
}
