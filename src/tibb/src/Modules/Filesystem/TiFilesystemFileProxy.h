/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_FILESYSTEMFILEPROXY_H_
#define TI_FILESYSTEMFILEPROXY_H_

#include <TiCore.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>

namespace TiFilesystem {

class TiFilesystemFileProxy : public Ti::TiData
{
public:
	CREATE_PROXY(TiFilesystemFileProxy)
	TiFilesystemFileProxy(const char*);
	virtual ~TiFilesystemFileProxy();

	virtual Ti::TiValue getExecutable();
	virtual Ti::TiValue getName();
	virtual Ti::TiValue getNativePath();
	virtual Ti::TiValue getParent();
	virtual Ti::TiValue getReadonly();
	virtual Ti::TiValue getSize();
	virtual Ti::TiValue getSymbolicLink();
	virtual Ti::TiValue getWritable();
	virtual Ti::TiValue getHidden();
	virtual Ti::TiValue getRemoteBackup();

	EXPOSE_GETTER(TiFilesystemFileProxy, getExecutable)
	EXPOSE_GETTER(TiFilesystemFileProxy, getName)
	EXPOSE_GETTER(TiFilesystemFileProxy, getNativePath)
	EXPOSE_GETTER(TiFilesystemFileProxy, getParent)
	EXPOSE_GETTER(TiFilesystemFileProxy, getReadonly)
	EXPOSE_GETTER(TiFilesystemFileProxy, getSize)
	EXPOSE_GETTER(TiFilesystemFileProxy, getSymbolicLink)
	EXPOSE_GETTER(TiFilesystemFileProxy, getWritable)
	EXPOSE_GETTER(TiFilesystemFileProxy, getHidden)
	EXPOSE_GETTER(TiFilesystemFileProxy, getRemoteBackup)

	virtual void setHidden(Ti::TiValue);
	virtual void setRemoteBackup(Ti::TiValue);

	EXPOSE_SETTER(TiFilesystemFileProxy, setHidden)
	EXPOSE_SETTER(TiFilesystemFileProxy, setRemoteBackup)

	virtual Ti::TiValue append(Ti::TiValue);
	virtual Ti::TiValue copy(Ti::TiValue);
	virtual Ti::TiValue createDirectory(Ti::TiValue);
	virtual Ti::TiValue createFile(Ti::TiValue);
	virtual Ti::TiValue createTimestamp(Ti::TiValue);
	virtual Ti::TiValue deleteDirectory(Ti::TiValue);
	virtual Ti::TiValue deleteFile(Ti::TiValue);
	virtual Ti::TiValue exists(Ti::TiValue);
	virtual Ti::TiValue extension(Ti::TiValue);
	virtual Ti::TiValue getDirectoryListing(Ti::TiValue);
	virtual Ti::TiValue isDirectory(Ti::TiValue);
	virtual Ti::TiValue isFile(Ti::TiValue);
	virtual Ti::TiValue modificationTimestamp(Ti::TiValue);
	virtual Ti::TiValue move(Ti::TiValue);
	virtual Ti::TiValue open(Ti::TiValue);
	virtual Ti::TiValue read(Ti::TiValue);
	virtual Ti::TiValue rename(Ti::TiValue);
	virtual Ti::TiValue resolve(Ti::TiValue);
	virtual Ti::TiValue spaceAvailable(Ti::TiValue);
	virtual Ti::TiValue write(Ti::TiValue);

	EXPOSE_METHOD(TiFilesystemFileProxy, append);
	EXPOSE_METHOD(TiFilesystemFileProxy, copy);
	EXPOSE_METHOD(TiFilesystemFileProxy, createDirectory);
	EXPOSE_METHOD(TiFilesystemFileProxy, createFile);
	EXPOSE_METHOD(TiFilesystemFileProxy, createTimestamp);
	EXPOSE_METHOD(TiFilesystemFileProxy, deleteDirectory);
	EXPOSE_METHOD(TiFilesystemFileProxy, deleteFile);
	EXPOSE_METHOD(TiFilesystemFileProxy, exists);
	EXPOSE_METHOD(TiFilesystemFileProxy, extension);
	EXPOSE_METHOD(TiFilesystemFileProxy, getDirectoryListing);
	EXPOSE_METHOD(TiFilesystemFileProxy, isDirectory);
	EXPOSE_METHOD(TiFilesystemFileProxy, isFile);
	EXPOSE_METHOD(TiFilesystemFileProxy, modificationTimestamp);
	EXPOSE_METHOD(TiFilesystemFileProxy, move);
	EXPOSE_METHOD(TiFilesystemFileProxy, open);
	EXPOSE_METHOD(TiFilesystemFileProxy, read);
	EXPOSE_METHOD(TiFilesystemFileProxy, rename);
	EXPOSE_METHOD(TiFilesystemFileProxy, resolve);
	EXPOSE_METHOD(TiFilesystemFileProxy, spaceAvailable);
	EXPOSE_METHOD(TiFilesystemFileProxy, write);

	virtual void setPath(QString);
	virtual QString getFilePath();
	virtual QByteArray 	getData();
	virtual QString 	getFilename();
	virtual QString 	getContentType();
	virtual Ti::TiData::Type getType();

private:
	QString _path;
	QFileInfo _fileInfo;
};

}
#endif /* TIFILESYSTEMFILE_H_ */
