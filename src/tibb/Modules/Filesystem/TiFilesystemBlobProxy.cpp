/*
 * TiFilesystemBlobProxy.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: penrique
 */

#include "TiFilesystemBlobProxy.h"

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
	qDebug() << "Cannot call " << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::copy(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createDirectory(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createFile(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::createTimestamp(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::deleteDirectory(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::deleteFile(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
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
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
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
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::move(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::open(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::read(Ti::TiValue value)
{
	return TiFilesystemFileProxy::read(value);
}
Ti::TiValue TiFilesystemBlobProxy::rename(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::resolve(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::spaceAvailable(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::write(Ti::TiValue)
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}

Ti::TiValue TiFilesystemBlobProxy::getExecutable()
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
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
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueTrue();
}
Ti::TiValue TiFilesystemBlobProxy::getSize()
{
	return TiFilesystemFileProxy::getSize();
}
Ti::TiValue TiFilesystemBlobProxy::getSymbolicLink()
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getWritable()
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getHidden()
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}
Ti::TiValue TiFilesystemBlobProxy::getRemoteBackup()
{
	qDebug() << "Cannot call" << __func__ << "on Resources dir";
	return valueFalse();
}

