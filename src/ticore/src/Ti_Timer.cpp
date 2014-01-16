/*
 * TiTimer.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Timer.h"
#include "Ti_Helper.h"
#include <QDebug>

static QList<Handle<Value> > _timeouts;

static void _TimerWeakCallback(Persistent<Value>, void* t)
{
	if(t == NULL) return;
	Ti::TiTimer *timer = static_cast<Ti::TiTimer*>(t);
	delete timer;
	/*
     object.Clear();
     object.Dispose();
     qDebug() << "[TiEvent] _EvantWeakCallback";
     */
}

Ti::TiTimer::TiTimer(int _milliseconds) :
singleShot(false),
fireCallback(true)
{
    
	timer = new QTimer();
	timer->setInterval(_milliseconds);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	QObject::connect(timer, SIGNAL(destroyed(QObject*)), this, SLOT(destroyed(QObject*)));
}

Ti::TiTimer::~TiTimer()
{
	callback.Clear();
	callback.Dispose();
}

void Ti::TiTimer::destroyed(QObject* obj) {
	qDebug() << "[TIMER]" << obj;
}
void Ti::TiTimer::timeout()
{
	HandleScope scope;
	if(singleShot)
    {
    	if(_timeouts.contains(callback) && fireCallback)
    	{
            
    	    Handle<Context> context = callback->CreationContext();
    	    callback->Call(context->Global(), 0, 0);
        	callback.MakeWeak(this, _TimerWeakCallback);
    		_timeouts.removeOne(callback);
    	}
    }
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
	timer->callback->SetHiddenValue(String::New("timer"), External::New(timer));
	_timeouts.append(timer->callback);
	return scope.Close(timer->callback);
}

Handle<Value> Ti::TiTimer::ClearTimeout(const Arguments &args)
{
	qDebug() << "[TiTimer] ClearTimeout!";
	HandleScope scope;
	Handle<Function> _function = Handle<Function>::Cast(args[0]);
	if(_timeouts.contains(_function))
	{
		qDebug() << "[TiTimer] Found!";
		Persistent<Function> callback = (Persistent<Function>)_function;
		Handle<External> timerObject = Handle<External>::Cast(callback->GetHiddenValue(String::New("timer")));
		Ti::TiTimer* tiTimer = static_cast<Ti::TiTimer*>(timerObject->Value());
    	callback.MakeWeak(tiTimer, _TimerWeakCallback);
    	tiTimer->fireCallback = false;
		tiTimer->stop();
		qDebug() << "[TiTimer] remove timer?" << _timeouts.removeOne(_function);
		qDebug() << "[TiTimer] Done with this";
        
	}
	return scope.Close(Object::New());
    
}

Handle<Value> Ti::TiTimer::SetInterval(const Arguments &args)
{
	HandleScope scope;
    
	Handle<Value> _function = args[0];
	Handle<Value> _timeout = args[1];
    
	int i = _timeout->ToInteger()->Value();
    
	Ti::TiTimer *timer = new Ti::TiTimer(i);
	timer->setSingleShot(true);
	timer->start();
	timer->callback = Persistent<Function>::New(Handle<Function>::Cast(_function));
	_timeouts.append(timer->callback);
	return scope.Close(timer->callback);
}

Handle<Value> Ti::TiTimer::ClearInterval(const Arguments &args)
{
	HandleScope scope;
	return scope.Close(Undefined());
    
}

