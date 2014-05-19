/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_TiAppProperties_MODULE
#define NATIVE_TiAppProperties_MODULE

#include <TiCore.h>

class TiAppPropertiesModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiAppPropertiesModule);
	TiAppPropertiesModule(const char*);
	virtual ~TiAppPropertiesModule();

    enum PropertyType {
        BoolProperty,
        DoubleProperty,
        IntProperty,
        ListProperty,
        ObjectProperty,
        StringProperty,
        RemoveProperty
    };

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	Ti::TiValue getBool(Ti::TiValue);
	Ti::TiValue getDouble(Ti::TiValue);
	Ti::TiValue getInt(Ti::TiValue);
	Ti::TiValue getList(Ti::TiValue);
	Ti::TiValue getObject(Ti::TiValue);
	Ti::TiValue getString(Ti::TiValue);
	Ti::TiValue hasProperty(Ti::TiValue);
	Ti::TiValue listProperties(Ti::TiValue);
	Ti::TiValue removeProperty(Ti::TiValue);
	Ti::TiValue setBool(Ti::TiValue);
	Ti::TiValue setDouble(Ti::TiValue);
	Ti::TiValue setInt(Ti::TiValue);
	Ti::TiValue setList(Ti::TiValue);
	Ti::TiValue setObject(Ti::TiValue);
	Ti::TiValue setString(Ti::TiValue);

	EXPOSE_METHOD(TiAppPropertiesModule, getBool)
	EXPOSE_METHOD(TiAppPropertiesModule, getDouble)
	EXPOSE_METHOD(TiAppPropertiesModule, getInt)
	EXPOSE_METHOD(TiAppPropertiesModule, getList)
	EXPOSE_METHOD(TiAppPropertiesModule, getObject)
	EXPOSE_METHOD(TiAppPropertiesModule, getString)
	EXPOSE_METHOD(TiAppPropertiesModule, hasProperty)
	EXPOSE_METHOD(TiAppPropertiesModule, listProperties)
	EXPOSE_METHOD(TiAppPropertiesModule, removeProperty)
	EXPOSE_METHOD(TiAppPropertiesModule, setBool)
	EXPOSE_METHOD(TiAppPropertiesModule, setDouble)
	EXPOSE_METHOD(TiAppPropertiesModule, setInt)
	EXPOSE_METHOD(TiAppPropertiesModule, setList)
	EXPOSE_METHOD(TiAppPropertiesModule, setObject)
	EXPOSE_METHOD(TiAppPropertiesModule, setString)
private:
	QVariant convertTiValueToQVariant(Ti::TiValue, PropertyType);
	QVariant createObjectFromTiValue(Ti::TiValue);
	QVariant createListFromTiValue(Ti::TiValue);
	QList<Ti::TiValue> createListFromQVariant(QVariant);
	QMap<QString, Ti::TiValue> createMapFromQVariant(QVariant);
	Ti::TiValue convertQVariantToTiValue(QVariant, PropertyType);
    Ti::TiValue getProp(Ti::TiValue, PropertyType);
	void setProp(Ti::TiValue, PropertyType);

};

#endif
