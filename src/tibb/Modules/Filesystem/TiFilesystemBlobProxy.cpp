/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiFilesystemBlobProxy.h"

namespace TiFilesystem {

TiFilesystemBlobProxy::TiFilesystemBlobProxy(const char* name) :
	TiFilesystemFileProxy(name) {

}

TiFilesystemBlobProxy::~TiFilesystemBlobProxy()
{

}

Ti::TiValue TiFilesystemBlobProxy::valueFalse()
{
	Ti::TiValue val;
	val.setBool(false);
	return val;
}

Ti::TiValue TiFilesystemBlobProxy::valueTrue()
{
	Ti::TiValue val;
	val.setBool(true);
	return val;
}

void TiFilesystemBlobProxy::setHidden(Ti::TiValue)
{

}
void TiFilesystemBlobProxy::setRemoteBackup(Ti::TiValue)
{

}

Ti::TiValue TiFilesystemBlobProxy::append(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::copy(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createDirectory(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createFile(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createTimestamp(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::deleteDirectory(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::deleteFile(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::exists(Ti::TiValue value)
{
	return TiFilesystemFileProxy::exists(value);
}
Ti::TiValue TiFilesystemBlobProxy::extension(Ti::TiValue value)
{
	return TiFilesystemFileProxy::extension(value);
}
Ti::TiValue TiFilesystemBlobProxy::getDirectoryListing(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::isDirectory(Ti::TiValue value)
{
	return TiFilesystemFileProxy::isDirectory(value);
}
Ti::TiValue TiFilesystemBlobProxy::isFile(Ti::TiValue value)
{
	return TiFilesystemFileProxy::isFile(value);
}
Ti::TiValue TiFilesystemBlobProxy::modificationTimestamp(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::move(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::open(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::read(Ti::TiValue value)
{
	return TiFilesystemFileProxy::read(value);
}
Ti::TiValue TiFilesystemBlobProxy::rename(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::resolve(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::spaceAvailable(Ti::TiValue)
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::write(Ti::TiValue)
{
	return valueFalse();
}

Ti::TiValue TiFilesystemBlobProxy::getExecutable()
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getName()
{
	return TiFilesystemFileProxy::getName();
}
Ti::TiValue TiFilesystemBlobProxy::getNativePath()
{
	return TiFilesystemFileProxy::getNativePath();
}
Ti::TiValue TiFilesystemBlobProxy::getParent()
{
	Ti::TiValue val; val.setNull();
	return val;
}
Ti::TiValue TiFilesystemBlobProxy::getReadonly()
{
	return valueTrue();
}
Ti::TiValue TiFilesystemBlobProxy::getSize()
{
	return TiFilesystemFileProxy::getSize();
}
Ti::TiValue TiFilesystemBlobProxy::getSymbolicLink()
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getWritable()
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getHidden()
{
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getRemoteBackup()
{
	return valueFalse();
}

}
