/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIAPIMODULE_H_
#define TIAPIMODULE_H_

#include <TiCore.h>

class TiAPIModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiAPIModule);
	TiAPIModule(const char*);
	virtual ~TiAPIModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	Ti::TiValue debug(Ti::TiValue);
	Ti::TiValue error(Ti::TiValue);
	Ti::TiValue info(Ti::TiValue);
	Ti::TiValue log (Ti::TiValue);
	Ti::TiValue timestamp(Ti::TiValue);
	Ti::TiValue trace(Ti::TiValue);
	Ti::TiValue warn(Ti::TiValue);

	EXPOSE_METHOD(TiAPIModule, debug);
	EXPOSE_METHOD(TiAPIModule, error);
	EXPOSE_METHOD(TiAPIModule, info);
	EXPOSE_METHOD(TiAPIModule, log );
	EXPOSE_METHOD(TiAPIModule, timestamp);
	EXPOSE_METHOD(TiAPIModule, trace);
	EXPOSE_METHOD(TiAPIModule, warn);

};

#endif /* TIAPPMODULE_H_ */
