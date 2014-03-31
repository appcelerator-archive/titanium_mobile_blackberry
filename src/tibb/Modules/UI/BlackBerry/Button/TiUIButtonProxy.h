/*
 * TiUIButtonProxy.h
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
 */

#ifndef TI_UIBUTTONPROXY_H_
#define TI_UIBUTTONPROXY_H_

#include "TiCore.h"
#include <bb/cascades/Button>
using namespace v8;

namespace TiUI
{
class TiUIButton;
class TiUIButtonProxy: public Ti::TiViewProxy {
public:
	TiUIButtonProxy(const char*);
	CREATE_PROXY(TiUIButtonProxy);
	virtual ~TiUIButtonProxy();

	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setColor, getColor)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setFont, getFont)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setImage, getImage)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setSelectedColor, getSelectedColor)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setStyle, getStyle)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setSystemButton, getSystemButton)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setTextAlign, getTextAlign)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setTitle, getTitle)
	TI_CREATE_SETTER_GETTER(TiUIButtonProxy, setVerticalAlign, getVerticalAlign)


private:
	bb::cascades::Button* _native;
	TiUIButton* _button;
};

}
#endif /* TIUIBUTTONPROXY_H_ */
