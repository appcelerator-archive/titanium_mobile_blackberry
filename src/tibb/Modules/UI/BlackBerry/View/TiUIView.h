/*
 * TiUIView.h
 *
 *  Created on: Jul 14, 2013
 *      Author: penrique
 */

#ifndef TIUIVIEW_H_
#define TIUIVIEW_H_

#include "TiCore.h"
namespace TiUI {

class TiUIView : public Ti::TiView
{
public:
	TiUIView(Ti::TiViewProxy*);
	virtual ~TiUIView();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
};
}
#endif /* TIUIVIEW_H_ */
