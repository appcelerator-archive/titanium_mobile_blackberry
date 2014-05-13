/*
 * TiUISlider.h
 *
 *  Created on: Wednesday, September 25, 2013
 *      Author: penrique
 */

#ifndef TI_TIUISLIDER_H_
#define TI_TIUISLIDER_H_

#include "TiCore.h"
#include <bb/cascades/Slider>

namespace TiUI {

class TiUISlider : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUISlider(Ti::TiViewProxy*);
	virtual ~TiUISlider();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	bb::cascades::Slider* getNative();
private:
	bb::cascades::Slider *_slider;
public slots:
	void onChange(float);
	void onChanging(float);
};
}
#endif /* TIUISLIDER_H_ */
