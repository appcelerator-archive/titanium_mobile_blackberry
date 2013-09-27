/**
 * TiUIBlackberry.h
 *
 *
 */

#ifndef NATIVE_TiUIBlackberry_MODULE
#define NATIVE_TiUIBlackberry_MODULE

#include "TiCore.h"

class TiUIBlackberryModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiUIBlackberryModule);
	TiUIBlackberryModule(const char*);
	virtual ~TiUIBlackberryModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

};

#endif
