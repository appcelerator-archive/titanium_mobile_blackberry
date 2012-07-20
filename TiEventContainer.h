/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIEVENTCONTAINER_H_
#define TIEVENTCONTAINER_H_

//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#include <v8.h>
//#pragma GCC diagnostic warning "-Wunused-parameter"

class TiEvent;
class TiObject;

#include <qmap.h>
#include <qvariant.h>

/*
 * TiEvent
 *
 * Abstract class manages a list of subscribers for a specified event
 *
 */

class TiEventContainer
{
public:
    virtual void addListener(TiEvent* listener) = 0;
    virtual void removeListener(int id) = 0;
    virtual void fireEvent() = 0;
    virtual void fireEvent(const TiObject* eventData) const = 0;
    virtual void setDataProperty(const char* propertyName, const char* value) = 0;
    virtual void setDataProperty(const char* propertyName, int value) = 0;
    virtual void setDataProperty(const char* propertyName, float value) = 0;
    virtual void setComplexDataProperty(const char* complexPropertyName, const char* propertyName, const char* value) = 0;
    virtual void setDataModelProperty(const char* propertyName, QMap<QString, QVariant> data) = 0;
    virtual ~TiEventContainer()
    {
    }
    ;

protected:
    TiEventContainer()
    {
    }
    ;
};

#endif /* TIEVENTCONTAINER_H_ */
