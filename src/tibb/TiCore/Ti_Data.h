/*
 * Ti_Blob.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIDATA_H_
#define TI_TIDATA_H_

#include "Ti_Proxy.h"
#include <QByteArray>

namespace Ti {

class TiData : public Ti::TiProxy
{
public:
	TiData(const char*);
	virtual ~TiData();

	virtual QByteArray 	getData() = 0;
	virtual QString 	getFilename() = 0;
	virtual QString 	getContentType() = 0;
};
} /* namespace Ti */
#endif /* TI_TIDATA_H_ */
