/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_TiBlackberry_MODULE
#define NATIVE_TiBlackberry_MODULE

#include "TiCore.h"

class TiBlackberryModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiBlackberryModule);
	TiBlackberryModule(const char*);
	virtual ~TiBlackberryModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();


};

#endif
