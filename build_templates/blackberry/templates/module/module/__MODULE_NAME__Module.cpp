/**
 * __MODULE_NAME__.cpp
 *
 *
 */

#include "__MODULE_NAME__Module.h"
#include "ExampleProxy.h"

__MODULE_NAME__Module::__MODULE_NAME__Module(const char* name) : Ti::TiModule(name)
{
	addFunction("createExample", ExampleProxy::CreateProxy);
}

__MODULE_NAME__Module::~__MODULE_NAME__Module()
{

}

Ti::TiValue __MODULE_NAME__Module::getModuleId()
{
	Ti::TiValue val;
	val.setString("__MODULE_ID__");
	return val;
}
Ti::TiValue __MODULE_NAME__Module::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("__MODULE_VERSION__");
	return val;
}
Ti::TiValue __MODULE_NAME__Module::getModuleName()
{
	Ti::TiValue val;
	val.setString("__MODULE_NAME__");
	return val;
}