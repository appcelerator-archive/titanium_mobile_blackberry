/*
 * TiTimer.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Timer.h"
#include <QDebug>
Ti::TiTimer::TiTimer(int _milliseconds) :
	singleShot(false)
{

	timer = new QTimer();
	timer->setInterval(_milliseconds);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	QObject::connect(timer, SIGNAL(destroyed(QObject*)), this, SLOT(destroyed(QObject*)));
}

Ti::TiTimer::~TiTimer() {
	// TODO Auto-generated destructor stub
}

void Ti::TiTimer::destroyed(QObject* obj) {
	qDebug() << "[TIMER]" << obj;
}
void Ti::TiTimer::timeout()
{
	HandleScope scope;
    callback->Call(callback->CreationContext()->Global(), 0, 0);
}

void Ti::TiTimer::setSingleShot(bool f)
{
	singleShot = f;
	timer->setSingleShot(f);
}
void Ti::TiTimer::start()
{
	timer->start();
}
void Ti::TiTimer::stop()
{
	timer->stop();
}

Handle<Value> Ti::TiTimer::SetTimeout(const Arguments &args)
{
	HandleScope scope;
	Handle<Value> _function = args[0];
	Handle<Value> _timeout = args[1];

	int i = _timeout->ToInteger()->Value();

	Ti::TiTimer *timer = new Ti::TiTimer(i);
	timer->setSingleShot(true);
	timer->start();
	timer->callback = Persistent<Function>::New(Handle<Function>::Cast(_function));
	return scope.Close(Undefined());
}
