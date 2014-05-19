/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_TiUtils_MODULE
#define NATIVE_TiUtils_MODULE

#include <TiCore.h>

class TiUtilsModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiUtilsModule);
	TiUtilsModule(const char*);
	virtual ~TiUtilsModule();

	QByteArray bytesFromValue(Ti::TiValue);
	QString intToHex(int);

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	Ti::TiValue base64decode(Ti::TiValue);
	Ti::TiValue base64encode(Ti::TiValue);
	Ti::TiValue md5HexDigest(Ti::TiValue);
	Ti::TiValue sha1(Ti::TiValue);
	Ti::TiValue sha256(Ti::TiValue);

	EXPOSE_METHOD(TiUtilsModule, base64decode);
	EXPOSE_METHOD(TiUtilsModule, base64encode);
	EXPOSE_METHOD(TiUtilsModule, md5HexDigest);
	EXPOSE_METHOD(TiUtilsModule, sha1);
	EXPOSE_METHOD(TiUtilsModule, sha256);
private:

};

#endif
