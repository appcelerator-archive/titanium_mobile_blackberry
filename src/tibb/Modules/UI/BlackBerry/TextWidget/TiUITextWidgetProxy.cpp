/*
 * TiUITextWidgetProxy.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: penrique
 */

#include "TiUITextWidgetProxy.h"
#include "TextArea/TiUITextAreaProxy.h"
#include "TextField/TiUITextFieldProxy.h"
#include "../TiUIBlackberryModule.h"
#include <bb/cascades/VerticalAlignment>

namespace TiUI {

TiUITextWidgetProxy::TiUITextWidgetProxy(const char* name) :
		Ti::TiViewProxy(name),
		_textWidget(NULL),
		_nativeTextWidget(NULL),
		_isTextArea(false),
		_isTextfield(false),
		_textField(NULL),
		_textArea(NULL)
{
	createPropertySetterGetter("appearance", _setAppearance,  _getAppearance);
	createPropertySetterGetter("autocapitalization", _setAutocapitalization,  _getAutocapitalization);
	createPropertySetterGetter("autocorrect", _setAutocorrect,  _getAutocorrect);
	createPropertySetterGetter("autoLink", _setAutoLink,  _getAutoLink);
	createPropertySetterGetter("clearOnEdit", _setClearOnEdit,  _getClearOnEdit);
	createPropertySetterGetter("color", _setColor,  _getColor);
	createPropertySetterGetter("editable", _setEditable,  _getEditable);
	createPropertySetterGetter("ellipsize", _setEllipsize,  _getEllipsize);
	createPropertySetterGetter("enabled", _setEnabled,  _getEnabled);
	createPropertySetterGetter("enableReturnKey", _setEnableReturnKey,  _getEnableReturnKey);
	createPropertySetterGetter("font", _setFont,  _getFont);
	createPropertySetterGetter("hintText", _setHintText,  _getHintText);
	createPropertySetterGetter("keyboardType", _setKeyboardType,  _getKeyboardType);
	createPropertySetterGetter("maxLength", _setMaxLength,  _getMaxLength);
	createPropertySetterGetter("returnKeyType", _setReturnKeyType,  _getReturnKeyType);
	createPropertySetterGetter("suppressReturn", _setSuppressReturn,  _getSuppressReturn);
	createPropertySetterGetter("textAlign", _setTextAlign,  _getTextAlign);
	createPropertySetterGetter("value", _setValue,  _getValue);
	createPropertySetterGetter("verticalAlign", _setVerticalAlign,  _getVerticalAlign);

	createPropertyFunction("blur", _blur);
	createPropertyFunction("focus", _focus);
	createPropertyFunction("hasText", _hasText);
	createPropertyFunction("setSelection", _setSelection);

}



TiUITextWidgetProxy::~TiUITextWidgetProxy() {
	// TODO Auto-generated destructor stub
}

Handle<Value> TiUITextWidgetProxy::CreateTextArea(const Arguments& args)
{
	return TiUITextAreaProxy::CreateProxy(args);
}
Handle<Value> TiUITextWidgetProxy::CreateTextField(const Arguments& args)
{
	return TiUITextFieldProxy::CreateProxy(args);
}

bb::cascades::AbstractTextControl *TiUITextWidgetProxy::getNativeTextControl()
{
	return _nativeTextWidget;
}

void TiUITextWidgetProxy::setIsTextArea(bool flag)
{
	if(flag)
	{
		_isTextArea = flag;
		_textArea = static_cast<bb::cascades::TextArea*>(_nativeTextWidget);
	}
}
void TiUITextWidgetProxy::setIsTextfield(bool flag)
{
	if(flag)
	{
		_isTextfield = flag;
		_textField = static_cast<bb::cascades::TextField*>(_nativeTextWidget);
	}
}

void TiUITextWidgetProxy::setView(Ti::TiView* view)
{
	_textWidget = static_cast<TiUITextWidget*>(view);
	_nativeTextWidget = _textWidget->getTextControl();
	Ti::TiViewProxy::setView(_textWidget);
}

void TiUITextWidgetProxy::setAppearance(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setAutocapitalization(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setAutocorrect(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setAutoLink(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setClearOnEdit(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setBackgroundColor(Ti::TiValue val)
{
	Ti::TiViewProxy::setBackgroundColor(val);

	qDebug() << "TextField" << _textField;
    if(val.isNull()) {
    	if(_isTextArea)
    		_textArea->setBackgroundVisible(true);
    	if(_isTextfield)
    		_textField->setBackgroundVisible(true);
    } else {
    	if(_isTextArea)
    		_textArea->setBackgroundVisible(false);
    	if(_isTextfield)
    		_textField->setBackgroundVisible(false);
    }

}
void TiUITextWidgetProxy::setColor(Ti::TiValue val)
{
	_nativeTextWidget->textStyle()->setColor(val.toColor());
}
void TiUITextWidgetProxy::setEditable(Ti::TiValue val)
{
	if(_isTextArea)
		_textArea->setEditable(val.toBool());
}
void TiUITextWidgetProxy::setEllipsize(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setEnabled(Ti::TiValue val)
{
	_nativeTextWidget->setEnabled(val.toBool());
}
void TiUITextWidgetProxy::setEnableReturnKey(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setFont(Ti::TiValue val)
{
	Ti::TiHelper::applyFontToText(val, _nativeTextWidget);
}
void TiUITextWidgetProxy::setHintText(Ti::TiValue value)
{
	if(_isTextArea)
	{
		_textArea->setHintText(value.toString());
	}
	if(_isTextfield)
	{
		_textField->setHintText(value.toString());
	}
}
void TiUITextWidgetProxy::setKeyboardToolbar(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setKeyboardToolbarColor(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setKeyboardToolbarHeight(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setKeyboardType(Ti::TiValue val)
{
	if(!val.isNumber()) return;

	bb::cascades::TextAreaInputMode::Type aType;
    bb::cascades::TextFieldInputMode::Type fType;

    switch ((int)val.toNumber()){
        case KEYBOARD_TYPE_ASCII:
        	aType = bb::cascades::TextAreaInputMode::Text;
        	fType = bb::cascades::TextFieldInputMode::Text;
            break;
        case KEYBOARD_TYPE_EMAIL:
        	aType = bb::cascades::TextAreaInputMode::EmailAddress;
        	fType = bb::cascades::TextFieldInputMode::EmailAddress;
            break;
        case KEYBOARD_TYPE_NUMBERS_PUNCTUATION:
        	fType = bb::cascades::TextFieldInputMode::NumbersAndPunctuation;
            break;
        case KEYBOARD_TYPE_NAMEPHONE_PAD:
        case KEYBOARD_TYPE_PHONE_PAD:
        	fType = bb::cascades::TextFieldInputMode::PhoneNumber;
            break;
        case KEYBOARD_TYPE_URL:
        	fType = bb::cascades::TextFieldInputMode::Url;
            break;
        case KEYBOARD_TYPE_CHAT:
        	aType = bb::cascades::TextAreaInputMode::Chat;
        	fType = bb::cascades::TextFieldInputMode::Chat;
        	break;
        default:
        	aType = bb::cascades::TextAreaInputMode::Default;
        	fType = bb::cascades::TextFieldInputMode::Default;
        	break;
    }
    if(_isTextfield)
    	_textField->setInputMode(fType);
    if(_isTextArea)
    	_textArea->setInputMode(aType);
}
void TiUITextWidgetProxy::setMaxLength(Ti::TiValue val)
{
	if(_isTextArea)
		_textArea->setMaximumLength(val.toNumber());
}
void TiUITextWidgetProxy::setReturnKeyType(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setSuppressReturn(Ti::TiValue)
{
}
void TiUITextWidgetProxy::setTextAlign(Ti::TiValue val)
{
	bb::cascades::TextAlign::Type type = bb::cascades::TextAlign::Default;
	if(val.isString())
	{
		QString alignment = val.toString();
		if(alignment == "center")
			type = bb::cascades::TextAlign::Center;
		if(alignment == "left")
			type = bb::cascades::TextAlign::Left;
		if(alignment == "right")
			type = bb::cascades::TextAlign::Right;
	}
	else
	{
		type = (bb::cascades::TextAlign::Type)val.toNumber();
	}
	_nativeTextWidget->textStyle()->setTextAlign(type);
}
void TiUITextWidgetProxy::setValue(Ti::TiValue value)
{
	_nativeTextWidget->setText(value.toString());
}
void TiUITextWidgetProxy::setVerticalAlign(Ti::TiValue val)
{
	bb::cascades::VerticalAlignment::Type t = _nativeTextWidget->verticalAlignment();
	if(val.isString())
	{
		QString value = val.toString();
		if(value.toLower() == "bottom")
		{
			t = bb::cascades::VerticalAlignment::Bottom;
		} else if(value.toLower() == "top")
		{
			t = bb::cascades::VerticalAlignment::Top;
		} else if(value.toLower() == "center")
		{
			t = bb::cascades::VerticalAlignment::Center;
		}
	}
	else
	{
		t = (bb::cascades::VerticalAlignment::Type)val.toNumber();
	}
	_nativeTextWidget->setVerticalAlignment(t);
}

Ti::TiValue TiUITextWidgetProxy::getAppearance()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getAutocapitalization()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getAutocorrect()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getAutoLink()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getClearOnEdit()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getEditable()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getEllipsize()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getEnabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getEnableReturnKey()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getFont()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getHintText()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getKeyboardToolbar()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getKeyboardToolbarColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getKeyboardToolbarHeight()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getKeyboardType()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getMaxLength()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getReturnKeyType()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getSuppressReturn()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getTextAlign()
{
	Ti::TiValue val;
	val.setNumber((double)_nativeTextWidget->textStyle()->textAlign());
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getValue()
{
	Ti::TiValue val;
	val.setString(_nativeTextWidget->text());
	return val;
}
Ti::TiValue TiUITextWidgetProxy::getVerticalAlign()
{
	Ti::TiValue val;
	val.setNumber(_nativeTextWidget->verticalAlignment());
	return val;
}

Ti::TiValue TiUITextWidgetProxy::blur(Ti::TiValue)
{
	_nativeTextWidget->loseFocus();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::focus(Ti::TiValue)
{
	_nativeTextWidget->requestFocus();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextWidgetProxy::hasText(Ti::TiValue)
{
	Ti::TiValue val;
	val.setBool(!_nativeTextWidget->text().isEmpty());
	return val;
}
Ti::TiValue TiUITextWidgetProxy::setSelection(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

} /* namespace TiUI */
