/*
 * TiUITextWidgetProxy.h
 *
 *  Created on: Sep 22, 2013
 *      Author: penrique
 */

#ifndef TIUITEXTWIDGETPROXY_H_
#define TIUITEXTWIDGETPROXY_H_

#include "TiCore.h"
#include "TiUITextWidget.h"
#include <bb/cascades/TextField>
#include <bb/cascades/TextArea>
#include <bb/cascades/AbstractTextControl>

namespace TiUI {

class TiUITextWidgetProxy : public Ti::TiViewProxy{
public:

	TiUITextWidgetProxy(const char*);
	virtual ~TiUITextWidgetProxy();

	static Handle<Value> CreateTextArea(const Arguments&);
	static Handle<Value> CreateTextField(const Arguments&);

	void setView(Ti::TiView*);

	void setAppearance(Ti::TiValue);
	void setAutocapitalization(Ti::TiValue);
	void setAutocorrect(Ti::TiValue);
	void setAutoLink(Ti::TiValue);
	void setBackgroundColor(Ti::TiValue);
	void setClearOnEdit(Ti::TiValue);
	void setColor(Ti::TiValue);
	void setEditable(Ti::TiValue);
	void setEllipsize(Ti::TiValue);
	void setEnabled(Ti::TiValue);
	void setEnableReturnKey(Ti::TiValue);
	void setFont(Ti::TiValue);
	void setHintText(Ti::TiValue);
	void setKeyboardToolbar(Ti::TiValue);
	void setKeyboardToolbarColor(Ti::TiValue);
	void setKeyboardToolbarHeight(Ti::TiValue);
	void setKeyboardType(Ti::TiValue);
	void setMaxLength(Ti::TiValue);
	void setReturnKeyType(Ti::TiValue);
	void setSuppressReturn(Ti::TiValue);
	void setTextAlign(Ti::TiValue);
	void setValue(Ti::TiValue);
	void setVerticalAlign(Ti::TiValue);

	Ti::TiValue getAppearance();
	Ti::TiValue getAutocapitalization();
	Ti::TiValue getAutocorrect();
	Ti::TiValue getAutoLink();
	Ti::TiValue getClearOnEdit();
	Ti::TiValue getColor();
	Ti::TiValue getEditable();
	Ti::TiValue getEllipsize();
	Ti::TiValue getEnabled();
	Ti::TiValue getEnableReturnKey();
	Ti::TiValue getFont();
	Ti::TiValue getHintText();
	Ti::TiValue getKeyboardToolbar();
	Ti::TiValue getKeyboardToolbarColor();
	Ti::TiValue getKeyboardToolbarHeight();
	Ti::TiValue getKeyboardType();
	Ti::TiValue getMaxLength();
	Ti::TiValue getReturnKeyType();
	Ti::TiValue getSuppressReturn();
	Ti::TiValue getTextAlign();
	Ti::TiValue getValue();
	Ti::TiValue getVerticalAlign();

	Ti::TiValue blur(Ti::TiValue);
	Ti::TiValue focus(Ti::TiValue);
	Ti::TiValue hasText(Ti::TiValue);
	Ti::TiValue setSelection(Ti::TiValue);

	EXPOSE_SETTER(TiUITextWidgetProxy, setAppearance)
	EXPOSE_SETTER(TiUITextWidgetProxy, setAutocapitalization)
	EXPOSE_SETTER(TiUITextWidgetProxy, setAutocorrect)
	EXPOSE_SETTER(TiUITextWidgetProxy, setAutoLink)
	EXPOSE_SETTER(TiUITextWidgetProxy, setClearOnEdit)
	EXPOSE_SETTER(TiUITextWidgetProxy, setColor)
	EXPOSE_SETTER(TiUITextWidgetProxy, setEditable)
	EXPOSE_SETTER(TiUITextWidgetProxy, setEllipsize)
	EXPOSE_SETTER(TiUITextWidgetProxy, setEnabled)
	EXPOSE_SETTER(TiUITextWidgetProxy, setEnableReturnKey)
	EXPOSE_SETTER(TiUITextWidgetProxy, setFont)
	EXPOSE_SETTER(TiUITextWidgetProxy, setHintText)
	EXPOSE_SETTER(TiUITextWidgetProxy, setKeyboardToolbar)
	EXPOSE_SETTER(TiUITextWidgetProxy, setKeyboardToolbarColor)
	EXPOSE_SETTER(TiUITextWidgetProxy, setKeyboardToolbarHeight)
	EXPOSE_SETTER(TiUITextWidgetProxy, setKeyboardType)
	EXPOSE_SETTER(TiUITextWidgetProxy, setMaxLength)
	EXPOSE_SETTER(TiUITextWidgetProxy, setReturnKeyType)
	EXPOSE_SETTER(TiUITextWidgetProxy, setSuppressReturn)
	EXPOSE_SETTER(TiUITextWidgetProxy, setTextAlign)
	EXPOSE_SETTER(TiUITextWidgetProxy, setValue)
	EXPOSE_SETTER(TiUITextWidgetProxy, setVerticalAlign)

	EXPOSE_GETTER(TiUITextWidgetProxy, getAppearance)
	EXPOSE_GETTER(TiUITextWidgetProxy, getAutocapitalization)
	EXPOSE_GETTER(TiUITextWidgetProxy, getAutocorrect)
	EXPOSE_GETTER(TiUITextWidgetProxy, getAutoLink)
	EXPOSE_GETTER(TiUITextWidgetProxy, getClearOnEdit)
	EXPOSE_GETTER(TiUITextWidgetProxy, getColor)
	EXPOSE_GETTER(TiUITextWidgetProxy, getEditable)
	EXPOSE_GETTER(TiUITextWidgetProxy, getEllipsize)
	EXPOSE_GETTER(TiUITextWidgetProxy, getEnabled)
	EXPOSE_GETTER(TiUITextWidgetProxy, getEnableReturnKey)
	EXPOSE_GETTER(TiUITextWidgetProxy, getFont)
	EXPOSE_GETTER(TiUITextWidgetProxy, getHintText)
	EXPOSE_GETTER(TiUITextWidgetProxy, getKeyboardToolbar)
	EXPOSE_GETTER(TiUITextWidgetProxy, getKeyboardToolbarColor)
	EXPOSE_GETTER(TiUITextWidgetProxy, getKeyboardToolbarHeight)
	EXPOSE_GETTER(TiUITextWidgetProxy, getKeyboardType)
	EXPOSE_GETTER(TiUITextWidgetProxy, getMaxLength)
	EXPOSE_GETTER(TiUITextWidgetProxy, getReturnKeyType)
	EXPOSE_GETTER(TiUITextWidgetProxy, getSuppressReturn)
	EXPOSE_GETTER(TiUITextWidgetProxy, getTextAlign)
	EXPOSE_GETTER(TiUITextWidgetProxy, getValue)
	EXPOSE_GETTER(TiUITextWidgetProxy, getVerticalAlign)

	EXPOSE_METHOD(TiUITextWidgetProxy, blur)
	EXPOSE_METHOD(TiUITextWidgetProxy, focus)
	EXPOSE_METHOD(TiUITextWidgetProxy, hasText)
	EXPOSE_METHOD(TiUITextWidgetProxy, setSelection)

	void setIsTextArea(bool);
	void setIsTextfield(bool);

	bb::cascades::AbstractTextControl *getNativeTextControl();

private:
	TiUITextWidget *_textWidget;
	bb::cascades::AbstractTextControl *_nativeTextWidget;
	bb::cascades::TextField *_textField;
	bb::cascades::TextArea *_textArea;
	bool _isTextArea;
	bool _isTextfield;
};

} /* namespace TiUI */
#endif /* TIUITEXTWIDGETPROXY_H_ */
