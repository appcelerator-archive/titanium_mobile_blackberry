/*
 * TiTimer.cpp
 *
 *  Created on: Jul 12, 2013
 *      Author: penrique
 */

#include "Ti_Timer.h"

Ti::TiTimer::TiTimer(int _milliseconds) {

	timer = new QTimer();
	timer->setInterval(_milliseconds);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

Ti::TiTimer::~TiTimer() {
	// TODO Auto-generated destructor stub
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
	Handle<Value> _function = args[0];
	Handle<Value> _timeout = args[1];

	int i = _timeout->ToInteger()->Value();

	Ti::TiTimer *timer = new Ti::TiTimer(i);
	timer->setSingleShot(true);
	timer->start();
	timer->callback = Persistent<Function>::New(Handle<Function>::Cast(_function));
	return Undefined();
}
