/**
 * TiUIBlackberry.cpp
 *
 *
 */

#include "TiUIBlackberryModule.h"
#include "ApplicationMenu/ApplicationMenuProxy.h"

using namespace TiUI;

TiUIBlackberryModule::TiUIBlackberryModule(const char* name) : Ti::TiModule(name)
{
	addFunction("createApplicationMenu", ApplicationMenuProxy::CreateProxy);
}

TiUIBlackberryModule::~TiUIBlackberryModule()
{

}

Ti::TiValue TiUIBlackberryModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.ui.blackberry");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiUIBlackberry");
	return val;
}
