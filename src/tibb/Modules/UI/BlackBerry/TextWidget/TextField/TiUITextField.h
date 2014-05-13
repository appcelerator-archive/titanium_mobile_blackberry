/*
 * TiUITextField.h
 *
 *  Created on: Friday, September 13, 2013
 *      Author: penrique
 */

#ifndef TI_TIUITEXTFIELD_H_
#define TI_TIUITEXTFIELD_H_

#include "TiCore.h"
#include "../TiUITextWidget.h"
#include <bb/cascades/TextField>
#include <bb/cascades/AbstractTextControl>

namespace TiUI {
class TiUITextField : public TiUITextWidget
{
	Q_OBJECT;
public:
	TiUITextField(Ti::TiViewProxy*);
	virtual ~TiUITextField();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
private:
	bb::cascades::TextField *_textField;
};
}
#endif /* TIUITEXTFIELD_H_ */
