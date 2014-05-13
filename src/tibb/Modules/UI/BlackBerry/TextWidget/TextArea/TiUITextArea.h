/*
 * TiUITextArea.h
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#ifndef TI_TIUITEXTAREA_H_
#define TI_TIUITEXTAREA_H_

#include "TiCore.h"
#include "../TiUITextWidget.h"
#include <bb/cascades/TextArea>
#include <bb/cascades/AbstractTextControl>

namespace TiUI {

class TiUITextArea : public TiUITextWidget
{
	Q_OBJECT;
public:
	TiUITextArea(Ti::TiViewProxy*);
	virtual ~TiUITextArea();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
private:
	bb::cascades::TextArea *_textArea;

};
}
#endif /* TIUITEXTAREA_H_ */
