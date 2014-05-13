/*
 * TiUITextFieldProxy.h
 *
 *  Created on: Friday, September 13, 2013
 *      Author: penrique
 */

#ifndef TI_TIUITEXTFIELDPROXY_H_
#define TI_TIUITEXTFIELDPROXY_H_

#include "TiCore.h"
#include <bb/cascades/TextField>
#include "../TiUITextWidgetProxy.h"

namespace TiUI {
class TiUITextField;
class TiUITextFieldProxy : public TiUITextWidgetProxy
{
public:
	CREATE_PROXY(TiUITextFieldProxy)
	TiUITextFieldProxy(const char*);
	virtual ~TiUITextFieldProxy();


	void setBorderStyle(Ti::TiValue);
	void setClearButtonMode(Ti::TiValue);
	void setLeftButton(Ti::TiValue);
	void setLeftButtonMode(Ti::TiValue);
	void setLeftButtonPadding(Ti::TiValue);
	void setMinimumFontSize(Ti::TiValue);
	void setPaddingLeft(Ti::TiValue);
	void setPaddingRight(Ti::TiValue);
	void setPasswordMask(Ti::TiValue);
	void setRightButton(Ti::TiValue);
	void setRightButtonMode(Ti::TiValue);
	void setRightButtonPadding(Ti::TiValue);

	Ti::TiValue getBorderStyle();
	Ti::TiValue getClearButtonMode();
	Ti::TiValue getLeftButton();
	Ti::TiValue getLeftButtonMode();
	Ti::TiValue getLeftButtonPadding();
	Ti::TiValue getMinimumFontSize();
	Ti::TiValue getPaddingLeft();
	Ti::TiValue getPaddingRight();
	Ti::TiValue getPasswordMask();
	Ti::TiValue getRightButton();
	Ti::TiValue getRightButtonMode();
	Ti::TiValue getRightButtonPadding();


	EXPOSE_SETTER(TiUITextFieldProxy, setBorderStyle)
	EXPOSE_SETTER(TiUITextFieldProxy, setClearButtonMode)
	EXPOSE_SETTER(TiUITextFieldProxy, setLeftButton)
	EXPOSE_SETTER(TiUITextFieldProxy, setLeftButtonMode)
	EXPOSE_SETTER(TiUITextFieldProxy, setLeftButtonPadding)
	EXPOSE_SETTER(TiUITextFieldProxy, setMinimumFontSize)
	EXPOSE_SETTER(TiUITextFieldProxy, setPaddingLeft)
	EXPOSE_SETTER(TiUITextFieldProxy, setPaddingRight)
	EXPOSE_SETTER(TiUITextFieldProxy, setPasswordMask)
	EXPOSE_SETTER(TiUITextFieldProxy, setRightButton)
	EXPOSE_SETTER(TiUITextFieldProxy, setRightButtonMode)
	EXPOSE_SETTER(TiUITextFieldProxy, setRightButtonPadding)

	EXPOSE_GETTER(TiUITextFieldProxy, getBorderStyle)
	EXPOSE_GETTER(TiUITextFieldProxy, getClearButtonMode)
	EXPOSE_GETTER(TiUITextFieldProxy, getLeftButton)
	EXPOSE_GETTER(TiUITextFieldProxy, getLeftButtonMode)
	EXPOSE_GETTER(TiUITextFieldProxy, getLeftButtonPadding)
	EXPOSE_GETTER(TiUITextFieldProxy, getMinimumFontSize)
	EXPOSE_GETTER(TiUITextFieldProxy, getPaddingLeft)
	EXPOSE_GETTER(TiUITextFieldProxy, getPaddingRight)
	EXPOSE_GETTER(TiUITextFieldProxy, getPasswordMask)
	EXPOSE_GETTER(TiUITextFieldProxy, getRightButton)
	EXPOSE_GETTER(TiUITextFieldProxy, getRightButtonMode)
	EXPOSE_GETTER(TiUITextFieldProxy, getRightButtonPadding)

private:
	bb::cascades::TextField *_nativeTextField;
};
}
#endif /* TIUITEXTFIELDPROXY_H_ */
