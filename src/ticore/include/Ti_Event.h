/*
 * TiEvent.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIEVENT_H_
#define TI_TIEVENT_H_

#include <v8.h>
#include "Ti_Helper.h"

using namespace v8;
namespace Ti
{
class TiEventParameters;
class TiEvent {
public:
	static void FireCallbackIfNeeded(QString, Handle<Object>, Ti::TiEventParameters*);
	static void AddEventToObject(Handle<Object>, QString, Handle<Function>);
	static void RemoveEventFromObject(Handle<Object>, QString, Handle<Function>);
	static void FireEventOnObject(Handle<Object>, QString, Ti::TiEventParameters*);
private:
	TiEvent();
	virtual ~TiEvent();
};
}
#endif /* TIEVENT_H_ */
