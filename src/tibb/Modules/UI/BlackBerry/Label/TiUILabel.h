/*
 * TiUILabel.h
 *
 *  Created on: Jul 14, 2013
 *      Author: penrique
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

class TiUILabel: public Ti::TiView {
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
