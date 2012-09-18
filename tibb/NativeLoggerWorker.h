/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELOGGERWORKER_H_
#define NATIVELOGGERWORKER_H_

#include <QObject>

class QString;


/*
 * NativeLoggerWorker
 *
 * Worker for the Native Logger
 */

class NativeLoggerWorker : public QObject
{

    Q_OBJECT

public slots:

    void log(const QString& t);
    void flush();
};

#endif /* NATIVELOGGERWORKER_H_ */
