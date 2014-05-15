/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISWITCH_H_
#define TI_TIUISWITCH_H_

#include "TiCore.h"
#include <bb/cascades/ToggleButton>

namespace TiUI {

class TiUISwitch : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUISwitch(Ti::TiViewProxy*);

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	void setChecked(bool);
	void setEnabled(bool);
	bool isChecked();
	bool isEnabled();
	virtual ~TiUISwitch();
private:
	bb::cascades::ToggleButton* _switch;
public slots:
	void onChange(bool);
};

} /* namespace TiUI */
#endif /* TIUISWITCH_H_ */
