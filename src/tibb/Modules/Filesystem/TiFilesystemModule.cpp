/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiFilesystemModule.h"
#include "TiFilesystemBlobProxy.h"
#include "TiFilesystemFileProxy.h"

static QString const RESOURCES_DIRECTORY = "app/native/assets";

using namespace TiFilesystem;

TiFilesystemModule::TiFilesystemModule(const char* name) : Ti::TiModule(name)
{

}

TiFilesystemModule::~TiFilesystemModule()
{

}

Ti::TiValue TiFilesystemModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.filesystem");
	return val;
}
Ti::TiValue TiFilesystemModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiFilesystemModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiFilesystem");
	return val;
}

void TiFilesystemModule::initStart()
{
	createPropertyGetter("applicationCacheDirectory", _getApplicationCacheDirectory);
	createPropertyGetter("applicationDataDirectory", _getApplicationDataDirectory);
	createPropertyGetter("applicationDirectory", _getApplicationDirectory);
	createPropertyGetter("applicationSupportDirectory", _getApplicationSupportDirectory);
	createPropertyGetter("applicationSharedDirectory", _getApplicationSharedDirectory);
	createPropertyGetter("externalStorageDirectory", _getExternalStorageDirectory);
	createPropertyGetter("lineEnding", _getLineEnding);
	createPropertyGetter("resRawDirectory", _getResRawDirectory);
	createPropertyGetter("resourcesDirectory", _getResourcesDirectory);
	createPropertyGetter("separator", _getSeparator);
	createPropertyGetter("tempDirectory", _getTempDirectory);

	createPropertyFunction("createTempDirectory", _createTempDirectory);
	createPropertyFunction("createTempFile", _createTempFile);
	createPropertyFunction("getFile", _getFile);
	createPropertyFunction("isExternalStoragePresent", _isExternalStoragePresent);
	createPropertyFunction("openStream", _openStream);

	addNumber("MODE_READ_WRITE", QIODevice::ReadWrite);
	addNumber("MODE_READ_ONLY", QIODevice::ReadOnly);
	addNumber("MODE_READ", QIODevice::ReadWrite);
	addNumber("MODE_WRITE", QIODevice::WriteOnly);
	addNumber("MODE_APPEND", QIODevice::Append);
}


Ti::TiValue TiFilesystemModule::getApplicationCacheDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getApplicationDataDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(QDir::homePath());
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getApplicationDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(QDir::currentPath());
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getApplicationSupportDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getExternalStorageDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getApplicationSharedDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setString("shared");
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getLineEnding()
{
	Ti::TiValue returnedValue;
	returnedValue.setString("\n");
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getResRawDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getResourcesDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(RESOURCES_DIRECTORY);
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getSeparator()
{
	Ti::TiValue returnedValue;
	returnedValue.setString("/");
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getTempDirectory()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(QDir::tempPath());
	return returnedValue;
}

Ti::TiValue TiFilesystemModule::createTempDirectory(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::createTempFile(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::getFile(Ti::TiValue value)
{
	QString path("");
	if(value.isList()) {
		QList<Ti::TiValue> array = value.toList();
		for(int i = 0, len = array.size(); i < len; i++)
		{
			Ti::TiValue val = array.at(i);
			path.append(val.toString());
			path.append("/");
		}
	} else {
		path.append(value.toString());
		path.append("/");
	}

	path.remove(path.length() - 1, 1);
	// in case there is double slashesh, remove them
	// Ti.Filesyste.getFile( Ti.Filestem.resourceDirectory, '/app.js')
	// or
	// Ti.Filesyste.getFile( Ti.Filestem.resourceDirectory, 'app.js')
	path.replace("//", "/");

	Ti::TiValue returnedValue;
	TiFilesystemFileProxy* proxy;
	if(path.startsWith(RESOURCES_DIRECTORY))
	{
		proxy = TiFilesystemBlobProxy::CreateProxy();
	}
	else
	{
		proxy = TiFilesystemFileProxy::CreateProxy();
	}
	proxy->setPath(path);
	returnedValue.setProxy(proxy);
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::isExternalStoragePresent(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemModule::openStream(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
