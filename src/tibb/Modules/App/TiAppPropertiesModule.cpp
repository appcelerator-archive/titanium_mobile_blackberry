/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAppPropertiesModule.h"
#include <QSettings>

TiAppPropertiesModule::TiAppPropertiesModule(const char* name) : Ti::TiModule(name)
{
	createPropertyFunction("getBool", _getBool);
	createPropertyFunction("getDouble", _getDouble);
	createPropertyFunction("getInt", _getInt);
	createPropertyFunction("getList", _getList);
	createPropertyFunction("getObject", _getObject);
	createPropertyFunction("getString", _getString);
	createPropertyFunction("hasProperty", _hasProperty);
	createPropertyFunction("listProperties", _listProperties);
	createPropertyFunction("removeProperty", _removeProperty);
	createPropertyFunction("setBool", _setBool);
	createPropertyFunction("setDouble", _setDouble);
	createPropertyFunction("setInt", _setInt);
	createPropertyFunction("setList", _setList);
	createPropertyFunction("setObject", _setObject);
	createPropertyFunction("setString", _setString);
}

TiAppPropertiesModule::~TiAppPropertiesModule()
{

}

Ti::TiValue TiAppPropertiesModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.prps");
	return val;
}
Ti::TiValue TiAppPropertiesModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiAppPropertiesModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiAppProperties");
	return val;
}

QVariant TiAppPropertiesModule::createObjectFromTiValue(Ti::TiValue val)
{
	qDebug() << "[VAL]" << val.toString();
	QMap<QString, QVariant> map;
	if(!val.isMap()) return map;

	QMap<QString, Ti::TiValue> values = val.toMap();

	foreach(QString key, values.keys())
	{
		Ti::TiValue newValue = values[key];
		if(newValue.isList())
		{
			map[key] = createListFromTiValue(newValue);
		}
		else if(newValue.isMap())
		{
			map[key] = createObjectFromTiValue(newValue);
		}
		else
		{
			map[key] = newValue.toString();
		}

	}

	return map;
}

QMap<QString, Ti::TiValue> TiAppPropertiesModule::createMapFromQVariant(QVariant val)
{
	qDebug() << "createMapFromQVariant" << val;
	QMap<QString, Ti::TiValue> map;
	if(val.type() == QVariant::Map)
	{
		QMap<QString, QVariant> varMap = val.toMap();
		foreach(QString key, varMap.keys())
		{
			QVariant current = varMap[key];

			switch(current.type())
			{
			case QVariant::List:
			{
				Ti::TiValue newVal;
				newVal.setList(createListFromQVariant(current));
				map.insert(key, newVal);
				break;
			}
			case QVariant::Int:
			case QVariant::UInt:
			case QVariant::LongLong:
			case QVariant::ULongLong:
			{
				Ti::TiValue newVal;
				newVal.setNumber(current.toDouble(NULL));
				map.insert(key, newVal);
				break;
			}
			case QVariant::Bool:
			{
				Ti::TiValue newVal;
				newVal.setBool(current.toBool());
				map.insert(key, newVal);
				break;
			}
			default:
			{
				Ti::TiValue newVal;
				newVal.setString(current.toString());
				map.insert(key, newVal);
				break;
			}
			}
		}
	}

	return map;
}
QList<Ti::TiValue> TiAppPropertiesModule::createListFromQVariant(QVariant val)
{
	QList<Ti::TiValue> list;
	if(val.type() == QVariant::List)
	{
		QList<QVariant> varList = val.toList();
		for(int i = 0, len = varList.size(); i < len; i++)
		{
			QVariant current = varList.at(i);
			switch(current.type())
			{
			case QVariant::List:
				list.append(createListFromQVariant(current));
				break;
			case QVariant::Int:
			case QVariant::UInt:
			case QVariant::LongLong:
			case QVariant::ULongLong:
			{
				Ti::TiValue newVal;
				newVal.setNumber(current.toDouble(NULL));
				list.append(newVal);
				break;
			}
			case QVariant::Bool:
			{
				Ti::TiValue newVal;
				newVal.setBool(current.toBool());
				list.append(newVal);
				break;
			}
			default:
			{
				Ti::TiValue newVal;
				newVal.setString(current.toString());
				list.append(newVal);
				break;
			}
			}
		}
	}
	return list;
}

QVariant TiAppPropertiesModule::createListFromTiValue(Ti::TiValue val)
{

	QList<QVariant> list;
	if(!val.isList()) return list;

	QList<Ti::TiValue> values = val.toList();

	for(int i = 0, len = values.size(); i < len; i++)
	{
		Ti::TiValue newValue = values.at(i);
		if(newValue.isList())
		{
			list.append(createListFromTiValue(newValue));
		}
		else if(newValue.isMap())
		{
			list.append(createObjectFromTiValue(newValue));
		}
		else
		{
			list.append(newValue.toString());
		}

	}

	return list;
}

QVariant TiAppPropertiesModule::convertTiValueToQVariant(Ti::TiValue value, PropertyType type)
{
	switch(type)
	{
	case TiAppPropertiesModule::BoolProperty:
		return QVariant(value.toBool());
	case TiAppPropertiesModule::DoubleProperty:
		return QVariant(value.toNumber());
	case TiAppPropertiesModule::IntProperty:
		return QVariant((int)value.toNumber());
	case TiAppPropertiesModule::ListProperty:
		return createListFromTiValue(value);
	case TiAppPropertiesModule::ObjectProperty:
		return createObjectFromTiValue(value);
	case TiAppPropertiesModule::StringProperty:
		return QVariant(value.toString());
	}

}

Ti::TiValue TiAppPropertiesModule::convertQVariantToTiValue(QVariant value, PropertyType type)
{
	Ti::TiValue val;
	switch(type)
	{
	case TiAppPropertiesModule::BoolProperty:
		val.setBool(value.toBool());
		break;
	case TiAppPropertiesModule::DoubleProperty:
		val.setNumber(value.toDouble(NULL));
		break;
	case TiAppPropertiesModule::IntProperty:
		val.setNumber(value.toInt(NULL));
		break;
	case TiAppPropertiesModule::ListProperty:
		val.setList(createListFromQVariant(value));
		break;
	case TiAppPropertiesModule::ObjectProperty:
	{
		val.setMap(createMapFromQVariant(value));
		break;
	}
	case TiAppPropertiesModule::StringProperty:
		val.setString(value.toString());
		break;
	default:
		val.setUndefined();
		break;
	}
	return val;
}

void TiAppPropertiesModule::setProp(Ti::TiValue value, PropertyType type)
{
	QSettings settings;
	if(type == TiAppPropertiesModule::RemoveProperty)
	{
		settings.remove(value.toString());
		return;
	}
	if(!value.isList()) return;

	QList<Ti::TiValue> values = value.toList();
	Ti::TiValue key = values.at(0);
	Ti::TiValue prop = values.at(1);

	settings.setValue(key.toString(), convertTiValueToQVariant(prop, type));
}

Ti::TiValue TiAppPropertiesModule::getProp(Ti::TiValue value, PropertyType type)
{
	QString key;
	QVariant prop;

	if(value.isList())
	{
		QList<Ti::TiValue> values = value.toList();
		Ti::TiValue keyVal = values.at(0);
		Ti::TiValue propVal = values.at(1);
		key = keyVal.toString();
		prop = convertTiValueToQVariant(propVal, type);
	}
	else
	{
		key = value.toString();
	}

	QSettings settings;
	if(settings.contains(key))
	{
		return convertQVariantToTiValue(settings.value(key), type);
	}
	else
	{
		if(prop.isValid())
		{
			settings.setValue(key, prop);
			return convertQVariantToTiValue(prop, type);
		}
		QSettings defaultSettings("app/native/_private_assets_/app_properties.ini", QSettings::IniFormat);
		if(defaultSettings.contains(key))
		{
			return convertQVariantToTiValue(defaultSettings.value(key), type);
		}
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiAppPropertiesModule::getBool(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::BoolProperty);
}
Ti::TiValue TiAppPropertiesModule::getDouble(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::DoubleProperty);
}
Ti::TiValue TiAppPropertiesModule::getInt(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::IntProperty);
}
Ti::TiValue TiAppPropertiesModule::getList(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::ListProperty);
}
Ti::TiValue TiAppPropertiesModule::getObject(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::ObjectProperty);
}
Ti::TiValue TiAppPropertiesModule::getString(Ti::TiValue value)
{
	return getProp(value, TiAppPropertiesModule::StringProperty);
}
Ti::TiValue TiAppPropertiesModule::hasProperty(Ti::TiValue value)
{
	QSettings settings;
	Ti::TiValue val;
	val.setBool(settings.contains(value.toString()));
	return val;
}
Ti::TiValue TiAppPropertiesModule::listProperties(Ti::TiValue)
{
	QSettings settings;
	QList<Ti::TiValue> allProps;
	foreach(QString propName, settings.allKeys())
	{
		Ti::TiValue pName;
		pName.setString(propName);
		allProps.append(pName);
	}
	Ti::TiValue val;
	val.setList(allProps);
	return val;
}
Ti::TiValue TiAppPropertiesModule::removeProperty(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::RemoveProperty);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setBool(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::BoolProperty);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setDouble(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::DoubleProperty);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setInt(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::IntProperty);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setList(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::ListProperty);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setObject(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::ObjectProperty);

	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppPropertiesModule::setString(Ti::TiValue value)
{
	setProp(value, TiAppPropertiesModule::StringProperty);

	Ti::TiValue val;
	val.setUndefined();
	return val;
}

