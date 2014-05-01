/*
 * TiSceneManager.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TISCENEMANAGER_H_
#define TI_TISCENEMANAGER_H_

#include <QList>

namespace bb
{
namespace cascades
{
class AbstractPane;
}
}

namespace Ti
{
class TiWindowProxy;
class TiSceneManager {
public:
	TiSceneManager();
	virtual ~TiSceneManager();
	void addPane(TiWindowProxy*);
	void removePane(TiWindowProxy*);
	static TiSceneManager* Instance();
	static void Open(TiWindowProxy*);
	static void Close(TiWindowProxy*);
private:
	QList<TiWindowProxy*> _windows;
};
}
#endif /* TISCENEMANAGER_H_ */
