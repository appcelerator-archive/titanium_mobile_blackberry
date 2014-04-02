/*
 * TiUIButton.h
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
 */

#ifndef TI_UIBUTTON_H_
#define TI_UIBUTTON_H_

#include "TiCore.h"

namespace bb
{
namespace cascades
{
class Button;
class TapEvent;
}
}

namespace Ti
{
class TiViewProxy;
}
namespace TiUI {

class TiUIButton: public Ti::TiView {
	Q_OBJECT;
public:
	TiUIButton(Ti::TiViewProxy*);
	virtual ~TiUIButton();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	virtual void onTapEvent(bb::cascades::TapEvent*);
	bb::cascades::Button * getNative();
private:
	bb::cascades::Button *_button;
public slots:
	void onClick();
};
}
#endif /* TIUIBUTTON_H_ */
