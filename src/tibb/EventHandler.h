/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_EVENT_HANDLER_H
#define TI_EVENT_HANDLER_H

#include <QObject>

#include "TiEventContainer.h"

namespace titanium {

class EventHandler : public QObject
{
    Q_OBJECT

public:
    explicit EventHandler(TiEventContainer* container)
        : container_(container) { }

    virtual ~EventHandler() { }

protected:
    TiEventContainer* getEventContainer() const {
        return container_;
    }

private:
    TiEventContainer* container_;
};

} // namespace titanium

#endif
