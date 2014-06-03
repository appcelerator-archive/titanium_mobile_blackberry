/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIMEDIAMODULE_H_
#define TI_TIMEDIAMODULE_H_

#include <TiCore.h>

class TiMediaModule : public Ti::TiModule
{
public:
	TiMediaModule(const char*);
	CREATE_MODULE(TiMediaModule)
	virtual ~TiMediaModule();
};
#endif /* PLATFORMMODULE_H_ */
