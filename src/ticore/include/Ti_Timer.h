/*
 * TiTimer.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TITIMER_H_
#define TI_TITIMER_H_

#include <QObject>
#include <QTimer>

#include <v8.h>

using namespace v8;

namespace Ti
{
class TiTimer: public QObject {
	Q_OBJECT;
public:
	TiTimer(int);
	virtual ~TiTimer();
	static Handle<Value> SetTimeout(const Arguments &args);
	void setSingleShot(bool);
	void start();
	void stop();
	QTimer *timer;
	Persistent<Function> callback;
	bool singleShot;
public slots:
	void destroyed(QObject*);
	void timeout();
};
}
#endif /* TITIMER_H_ */
