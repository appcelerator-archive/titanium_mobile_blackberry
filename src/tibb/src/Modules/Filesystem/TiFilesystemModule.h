/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_TiFilesystem_MODULE
#define NATIVE_TiFilesystem_MODULE

#include <TiCore.h>

class TiFilesystemModule : public Ti::TiModule
{

private:
	QString resolveApplicationDirectory();

public:
	CREATE_MODULE(TiFilesystemModule);
	TiFilesystemModule(const char*);
	virtual ~TiFilesystemModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	virtual void initStart();
//	virtual void initEnd();

	Ti::TiValue getApplicationCacheDirectory();
	Ti::TiValue getApplicationDataDirectory();
	Ti::TiValue getApplicationDirectory();
	Ti::TiValue getApplicationSupportDirectory();
	Ti::TiValue getApplicationSharedDirectory();
	Ti::TiValue getExternalStorageDirectory();
	Ti::TiValue getLineEnding();
	Ti::TiValue getResRawDirectory();
	Ti::TiValue getResourcesDirectory();
	Ti::TiValue getSeparator ();
	Ti::TiValue getTempDirectory();

	EXPOSE_GETTER(TiFilesystemModule, getApplicationCacheDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getApplicationDataDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getApplicationDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getApplicationSupportDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getApplicationSharedDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getExternalStorageDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getLineEnding);
	EXPOSE_GETTER(TiFilesystemModule, getResRawDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getResourcesDirectory);
	EXPOSE_GETTER(TiFilesystemModule, getSeparator );
	EXPOSE_GETTER(TiFilesystemModule, getTempDirectory);

	Ti::TiValue createTempDirectory(Ti::TiValue);
	Ti::TiValue createTempFile(Ti::TiValue);
	Ti::TiValue getFile(Ti::TiValue);
	Ti::TiValue isExternalStoragePresent(Ti::TiValue);
	Ti::TiValue openStream(Ti::TiValue);

	EXPOSE_METHOD(TiFilesystemModule, createTempDirectory);
	EXPOSE_METHOD(TiFilesystemModule, createTempFile);
	EXPOSE_METHOD(TiFilesystemModule, getFile);
	EXPOSE_METHOD(TiFilesystemModule, isExternalStoragePresent);
	EXPOSE_METHOD(TiFilesystemModule, openStream);

};

#endif
