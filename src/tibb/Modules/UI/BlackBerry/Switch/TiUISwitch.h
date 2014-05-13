/*
 * TiUISwitch.h
 *
 *  Created on: Sep 12, 2013
 *      Author: penrique
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
