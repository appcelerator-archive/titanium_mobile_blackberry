/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUtilsModule.h"
#include <QCryptographicHash>
#include "sha256.h"

TiUtilsModule::TiUtilsModule(const char* name) : Ti::TiModule(name)
{
	createPropertyFunction("base64decode", _base64decode);
	createPropertyFunction("base64encode", _base64encode);
	createPropertyFunction("md5HexDigest", _md5HexDigest);
	createPropertyFunction("sha1", _sha1);
	createPropertyFunction("sha256", _sha256);
}

TiUtilsModule::~TiUtilsModule()
{

}

QByteArray TiUtilsModule::bytesFromValue(Ti::TiValue value)
{
	QByteArray rawData;
	if(value.isProxy())
	{
		Ti::TiBlob* blob = static_cast<Ti::TiBlob*>(value.toProxy());
		rawData = blob->getData();
	}
	else
	{
		rawData = value.toString().toLocal8Bit();
	}
	return rawData;
}

QString TiUtilsModule::intToHex(int decimal)
{
	QString hexadecimal;
	hexadecimal.setNum(decimal, 16);
	return hexadecimal;
}

Ti::TiValue TiUtilsModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.utils");
	return val;
}
Ti::TiValue TiUtilsModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiUtilsModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiUtils");
	return val;
}

Ti::TiValue TiUtilsModule::base64decode(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setProxy(Ti::TiBlob::InitWithString(QByteArray::fromBase64(bytesFromValue(value)), "titanium/blob"));
	return val;
}
Ti::TiValue TiUtilsModule::base64encode(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setProxy(Ti::TiBlob::InitWithString(bytesFromValue(value).toBase64(), "titanium/blob"));
	return val;
}
Ti::TiValue TiUtilsModule::md5HexDigest(Ti::TiValue value)
{
	QByteArray hash = QCryptographicHash::hash(bytesFromValue(value), QCryptographicHash::Md5);
	Ti::TiValue val;
	val.setString(QString(hash.toHex()));
	return val;
}
Ti::TiValue TiUtilsModule::sha1(Ti::TiValue value)
{
	QByteArray hash = QCryptographicHash::hash(bytesFromValue(value), QCryptographicHash::Sha1);
	Ti::TiValue val;
	val.setString(QString(hash.toHex()));
	return val;
}
Ti::TiValue TiUtilsModule::sha256(Ti::TiValue value)
{
	Ti::TiValue val;
	QString str = value.toString();

	unsigned char *key = NULL;
	key = (unsigned char*)qstrdup(str.toLocal8Bit().constData());

	unsigned char hash[32];
	sha256_context ctx;
	sha256_starts(&ctx);
	sha256_update(&ctx, key, str.length());
	sha256_finish(&ctx, hash);
	QByteArray result = QByteArray(reinterpret_cast<const char *>(hash)).toHex();

	// for some reason we're getting 4 extra characters
	QString returnString = QString(result);
	returnString.remove(returnString.length() - 4, 4);

	val.setString(returnString);

	return val;
}
