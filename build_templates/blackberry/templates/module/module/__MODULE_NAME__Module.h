/**
 * __MODULE_NAME__.h
 *
 *
 */

#ifndef NATIVE___MODULE_NAME___MODULE
#define NATIVE___MODULE_NAME___MODULE

#include "TiCore.h"

class __MODULE_NAME__Module : public Ti::TiModule
{
public:
	CREATE_MODULE(__MODULE_NAME__Module);
	__MODULE_NAME__Module(const char*);	
	virtual ~__MODULE_NAME__Module();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	
};

#endif
