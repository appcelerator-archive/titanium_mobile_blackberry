/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUILABEL_H_
#define TI_TIUILABEL_H_

#include "TiCore.h"

namespace bb
{
namespace cascades
{
class Label;
}
}
namespace TiUI {

class TiViewProxy;

class TiUILabel: public Ti::TiView
{
	Q_OBJECT;
public:
	TiUILabel(Ti::TiViewProxy*);
	virtual ~TiUILabel();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	bb::cascades::Label* getNative();
private:
	bb::cascades::Label* _label;
};
}
#endif /* TIUILABEL_H_ */
