/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIFILESYSTEMBLOBPROXY_H_
#define TIFILESYSTEMBLOBPROXY_H_

#include "TiCore.h"
#include "TiFilesystemFileProxy.h"

namespace TiFilesystem {
class TiFilesystemBlobProxy : public TiFilesystemFileProxy
{
public:
	CREATE_PROXY(TiFilesystemBlobProxy)
	TiFilesystemBlobProxy(const char* name);
	virtual ~TiFilesystemBlobProxy();

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

	virtual void setHidden(Ti::TiValue);
	virtual void setRemoteBackup(Ti::TiValue);

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
	virtual Ti::TiData::Type getType();

private:
	Ti::TiValue valueFalse();
	Ti::TiValue valueTrue();
};
}

#endif /* TIFILESYSTEMBLOBPROXY_H_ */
