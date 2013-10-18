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
	TiEvent(Handle<Function>);
	virtual ~TiEvent();
	void fireWithParameters(QString, Handle<Object>, Ti::TiEventParameters*);
	static void fireCallbackIfNeeded(QString, Handle<Object>, Ti::TiEventParameters*);
	Persistent<Function> callback;
};
}
#endif /* TIEVENT_H_ */
