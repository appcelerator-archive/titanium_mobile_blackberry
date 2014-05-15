/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITABLEVIEWROW_H_
#define TI_TIUITABLEVIEWROW_H_

#include "TiCore.h"

namespace TiUI {

class TiUITableViewRow : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUITableViewRow(Ti::TiViewProxy*);
	virtual ~TiUITableViewRow();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void onEventAdded(QString);
};

} /* namespace TiUI */
#endif /* TIUITABLEVIEWROW_H_ */
