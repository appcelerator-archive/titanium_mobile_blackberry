/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELAYOUTHANDLER_H_
#define NATIVELAYOUTHANDLER_H_

#include <NativeControlObject.h>

#include <QtCore/QObject>

/**
 * NativeLayoutHandler
 */
class NativeLayoutHandler : public QObject
{
    Q_OBJECT

public:
    explicit NativeLayoutHandler(NativeControlObject* owner)
    {
        owner_ = owner;
    }
    virtual ~NativeLayoutHandler() {}

public slots:
    void handleLayoutFrameUpdated(QRectF rect)
    {
        owner_->updateLayout(rect);
    }

private:
    NativeControlObject* owner_;

    // Disable copy ctor & assignment operator
    NativeLayoutHandler(const NativeLayoutHandler& eHandler);
    NativeLayoutHandler& operator=(const NativeLayoutHandler& eHandler);
};


#endif /* NATIVELAYOUTHANDLER_H_ */
