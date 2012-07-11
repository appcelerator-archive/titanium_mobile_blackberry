/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETIMEOUTHANDLER_H_
#define NATIVETIMEOUTHANDLER_H_

#include <QtCore/QObject>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;

class TiV8Event;
class QTimer;

/**
 * NativeTimeoutHandler
 */
class NativeTimeoutHandler : public QObject
{
    Q_OBJECT

public:
    NativeTimeoutHandler(Handle<Number> number, Handle<Function> eventFunction,
                         bool interval);
    ~NativeTimeoutHandler();
    int getId();
    void clearTimeout();

public slots:
    void onEventFired();

private:
    int generateId();

    TiV8Event* event_;
    QTimer* timer_;
    static int idGenerator;
};


#endif /* NATIVETIMEOUTHANDLER_H_ */
