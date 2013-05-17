/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIFILESYSTEMOBJECT_
#define TIFILESYSTEMOBJECT_

#include "TiProxy.h"

class TiFilesystemFileObject: public TiProxy
{
public:
	TiFilesystemFileObject(QString path);
	QString getPath();

protected:
    virtual ~TiFilesystemFileObject();
    virtual void onCreateStaticMembers();

private:

	static Handle<Value> _isFile(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _isDirectory(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _writable(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _write(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _read(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _append(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _exists(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _getNativePath(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _createDirectory(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _createFile(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _deleteDirectory(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _deleteFile(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _getDirectoryListing(void* userContext, TiObject*, const Arguments& args);

	static Handle<Value> getIsWritable(TiFilesystemFileObject *file);
	QString _path;
};

#endif /* TIFILESYSTEMOBJECT_ */
