/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef CONTROLLAYOUTHANDLER_H_
#define CONTROLLAYOUTHANDLER_H_

#include <NativeControlObject.h>

#include <QtCore/QObject>

/**
 * ControlLayoutHandler
 */
class ControlLayoutHandler : public QObject
{
    Q_OBJECT

public:
    explicit ControlLayoutHandler(NativeControlObject* owner)
    {
        owner_ = owner;
    }
    virtual ~ControlLayoutHandler() {}

public slots:
    void handleLayoutFrameUpdated(QRectF rect)
    {
        owner_->updateLayout(rect);
    }

private:
    NativeControlObject* owner_;

    // Disable copy ctor & assignment operator
    ControlLayoutHandler(const ControlLayoutHandler& eHandler);
    ControlLayoutHandler& operator=(const ControlLayoutHandler& eHandler);
};


#endif /* CONTROLLAYOUTHANDLER_H_ */
