/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiFilesystemFileProxy.h"
#include <bb/FileSystemInfo>
#include <QDateTime>

namespace TiFilesystem {

TiFilesystemFileProxy::TiFilesystemFileProxy(const char* name) :
	Ti::TiData(name), _path("")
{
	createPropertyGetter("executable", _getExecutable);
	createPropertyGetter("name", _getName);
	createPropertyGetter("nativePath", _getNativePath);
	createPropertyGetter("parent", _getParent);
	createPropertyGetter("readonly", _getReadonly);
	createPropertyGetter("size", _getSize);
	createPropertyGetter("symbolicLink", _getSymbolicLink);
	createPropertyGetter("writable", _getWritable);

	createPropertySetterGetter("hidden", _setHidden, _getHidden);
	createPropertySetterGetter("remoteBackup", _setRemoteBackup, _getRemoteBackup);

	createPropertyFunction("append", _append);
	createPropertyFunction("copy", _copy);
	createPropertyFunction("createDirectory", _createDirectory);
	createPropertyFunction("createFile", _createFile);
	createPropertyFunction("createTimestamp", _createTimestamp);
	createPropertyFunction("deleteDirectory", _deleteDirectory);
	createPropertyFunction("deleteFile", _deleteFile);
	createPropertyFunction("exists", _exists);
	createPropertyFunction("extension", _extension);
	createPropertyFunction("getDirectoryListing", _getDirectoryListing);
	createPropertyFunction("isDirectory", _isDirectory);
	createPropertyFunction("isFile", _isFile);
	createPropertyFunction("modificationTimestamp", _modificationTimestamp);
	createPropertyFunction("move", _move);
	createPropertyFunction("open", _open);
	createPropertyFunction("read", _read);
	createPropertyFunction("rename", _rename);
	createPropertyFunction("resolve", _resolve);
	createPropertyFunction("spaceAvailable", _spaceAvailable);
	createPropertyFunction("write", _write);
}

TiFilesystemFileProxy::~TiFilesystemFileProxy()
{

}

QByteArray TiFilesystemFileProxy::getData()
{
	QFile file(_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    	return "";
    }

    QByteArray a = file.readAll();
    file.close();
    return a;
}
QString TiFilesystemFileProxy::getFilename()
{
	return _fileInfo.fileName();
}
QString TiFilesystemFileProxy::getContentType()
{
	return "";
}

void TiFilesystemFileProxy::setPath(QString path)
{
	_path = QString(path);
	_fileInfo = QFileInfo(QFile(_path));
}

Ti::TiValue TiFilesystemFileProxy::getExecutable()
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isExecutable());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getName()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(_fileInfo.fileName());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getNativePath()
{
	Ti::TiValue returnedValue;
	returnedValue.setString(_fileInfo.absolutePath());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getParent()
{
	Ti::TiValue returnedValue;
	QDir dir(_path);
	if(!dir.cdUp()) {
		returnedValue.setUndefined();
		Ti::TiHelper::Log("Cannot get parent directory");
		return returnedValue;
	}
	TiFilesystemFileProxy *newFileProxy = TiFilesystemFileProxy::CreateProxy();
	newFileProxy->setPath(dir.absolutePath());
	returnedValue.setProxy(newFileProxy);
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getReadonly()
{
	Ti::TiValue returnedValue;
	// TODO: Come back to this one, it might not work propertly
	QFile file(_path);
	returnedValue.setBool(!file.isWritable() && file.isReadable());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getSize()
{
	Ti::TiValue returnedValue;
	returnedValue.setNumber(_fileInfo.size());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getSymbolicLink()
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isSymLink());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getWritable()
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isWritable());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getHidden()
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isHidden());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getRemoteBackup()
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}

void TiFilesystemFileProxy::setHidden(Ti::TiValue)
{

}
void TiFilesystemFileProxy::setRemoteBackup(Ti::TiValue)
{

}

Ti::TiValue TiFilesystemFileProxy::append(Ti::TiValue value)
{
	Ti::TiValue returnedValue;

	QFile file(_path);
	if(value.isString() && file.open(QIODevice::WriteOnly | QIODevice::Append  | QIODevice::Text))
	{
		file.write(value.toString().toUtf8());
		file.close();
		returnedValue.setBool(true);
	} else {
		returnedValue.setBool(false);
	}

	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::copy(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::createDirectory(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(QDir(_path).mkdir(value.toString()));
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::createFile(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	QFile file(_path);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		returnedValue.setBool(false);
		return returnedValue;
	}
	// TODO: Not sure if this is the right way, maybe??
	file.write("");
	file.close();
	returnedValue.setBool(true);
	_fileInfo = QFileInfo(file);
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::createTimestamp(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	QDateTime created = _fileInfo.created();
	returnedValue.setNumber(created.toMSecsSinceEpoch());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::deleteDirectory(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(QDir(_path).rmdir(value.toString()));
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::deleteFile(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(QDir(_path).rmpath(value.toString()));
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::exists(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.exists());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::extension(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setString(_fileInfo.suffix());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::getDirectoryListing(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	if(!_fileInfo.isDir())
	{
		returnedValue.setUndefined();
		return returnedValue;
	}

	QDir dir(_path);
	QStringList allFiles = dir.entryList();

	QList<Ti::TiValue> array;
	for(int i = 0, len = allFiles.length(); i < len; i++)
	{
		Ti::TiValue val;
		val.setString(allFiles.at(i));
		array.append(val);
		Ti::TiHelper::Log(allFiles.at(i));
	}
	returnedValue.setList(array);
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::isDirectory(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isDir());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::isFile(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(_fileInfo.isFile());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::modificationTimestamp(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setNumber(_fileInfo.lastModified().toMSecsSinceEpoch());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::move(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	returnedValue.setBool(QFile(_path).rename(value.toString()));
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::open(Ti::TiValue value)
{
	Ti::TiValue returnedValue;
	// TODO: come back to this
	//	returnedValue.setBool(QFile(_path).open( (QIODevice::OpenMode)value.toNumber() ));
	returnedValue.setUndefined();
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::read(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setProxy(static_cast<Ti::TiProxy*>(Ti::TiBlob::InitWithFile(_path)));
	return returnedValue;
}

Ti::TiValue TiFilesystemFileProxy::rename(Ti::TiValue value)
{
	return move(value);
}
Ti::TiValue TiFilesystemFileProxy::resolve(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	returnedValue.setString(_fileInfo.absoluteFilePath());
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::spaceAvailable(Ti::TiValue)
{
	Ti::TiValue returnedValue;
	bb::FileSystemInfo info;
	returnedValue.setNumber(info.availableFileSystemSpace(_path));
	return returnedValue;
}
Ti::TiValue TiFilesystemFileProxy::write(Ti::TiValue value)
{
	Ti::TiValue returnedValue;

	QFile file(_path);
	if(value.isString() && file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		file.write(value.toString().toUtf8());
		file.close();
		returnedValue.setBool(true);
	}
	else
	{
		returnedValue.setBool(false);
	}

	return returnedValue;
}

}
