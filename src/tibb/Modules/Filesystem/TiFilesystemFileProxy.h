/*
 * TiFilesystemFileProxy.h
 *
 *  Created on: Sep 4, 2013
 *      Author: penrique
 */

#ifndef TI_FILESYSTEMFILEPROXY_H_
#define TI_FILESYSTEMFILEPROXY_H_

#include "TiCore.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>

class TiFilesystemFileProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiFilesystemFileProxy)
	TiFilesystemFileProxy(const char*);
	virtual ~TiFilesystemFileProxy();

	Ti::TiValue getExecutable();
	Ti::TiValue getName();
	Ti::TiValue getNativePath();
	Ti::TiValue getParent();
	Ti::TiValue getReadonly();
	Ti::TiValue getSize();
	Ti::TiValue getSymbolicLink();
	Ti::TiValue getWritable();
	Ti::TiValue getHidden();
	Ti::TiValue getRemoteBackup();

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

	void setHidden(Ti::TiValue);
	void setRemoteBackup(Ti::TiValue);

	EXPOSE_SETTER(TiFilesystemFileProxy, setHidden)
	EXPOSE_SETTER(TiFilesystemFileProxy, setRemoteBackup)

	Ti::TiValue append(Ti::TiValue);
	Ti::TiValue copy(Ti::TiValue);
	Ti::TiValue createDirectory(Ti::TiValue);
	Ti::TiValue createFile(Ti::TiValue);
	Ti::TiValue createTimestamp(Ti::TiValue);
	Ti::TiValue deleteDirectory(Ti::TiValue);
	Ti::TiValue deleteFile(Ti::TiValue);
	Ti::TiValue exists(Ti::TiValue);
	Ti::TiValue extension(Ti::TiValue);
	Ti::TiValue getDirectoryListing(Ti::TiValue);
	Ti::TiValue isDirectory(Ti::TiValue);
	Ti::TiValue isFile(Ti::TiValue);
	Ti::TiValue modificationTimestamp(Ti::TiValue);
	Ti::TiValue move(Ti::TiValue);
	Ti::TiValue open(Ti::TiValue);
	Ti::TiValue read(Ti::TiValue);
	Ti::TiValue rename(Ti::TiValue);
	Ti::TiValue resolve(Ti::TiValue);
	Ti::TiValue spaceAvailable(Ti::TiValue);
	Ti::TiValue write(Ti::TiValue);

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

	void setPath(QString);
private:
	QString _path;
	QFileInfo _fileInfo;
};

#endif /* TIFILESYSTEMFILE_H_ */
