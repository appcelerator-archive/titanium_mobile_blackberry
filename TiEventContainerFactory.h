/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIEVENTCONTAINERFACTORY_H_
#define TIEVENTCONTAINERFACTORY_H_

class TiEventContainer;

/*
 * TiEventContainerFactory
 *
 * Abstract class that creates event containers. The list
 * is event containers is specific to a control and therefore
 * must be created by the control, e.g., the button control
 * creates a 'click' event container and this container contains
 * a list of subscribers who subscribe to 'click'.
 */

class TiEventContainerFactory
{
public:
    virtual TiEventContainer* createEventContainer()=0;
    virtual ~TiEventContainerFactory();

protected:
    TiEventContainerFactory();
};

#endif /* TIEVENTCONTAINERFACTORY_H_ */
