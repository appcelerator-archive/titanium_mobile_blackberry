/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIEmailDialogProxy.h"
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/PpsObject>

namespace TiUI {

TiUIEmailDialogProxy::TiUIEmailDialogProxy(const char* name) :
		Ti::TiProxy(name),
		_html(false)
{

	createPropertyGetter("CANCELLED", _getCANCELLED);
	createPropertyGetter("FAILED", _getFAILED);
	createPropertyGetter("SAVED", _getSAVED);
	createPropertyGetter("SENT", _getSENT);

	createPropertySetterGetter("barColor", _setBarColor,  _getBarColor);
	createPropertySetterGetter("bccRecipients", _setBccRecipients,  _getBccRecipients);
	createPropertySetterGetter("ccRecipients", _setCcRecipients,  _getCcRecipients);
	createPropertySetterGetter("html", _setHtml,  _getHtml);
	createPropertySetterGetter("messageBody", _setMessageBody,  _getMessageBody);
	createPropertySetterGetter("subject", _setSubject,  _getSubject);
	createPropertySetterGetter("toRecipients", _setToRecipients,  _getToRecipients);

	createPropertyFunction("addAttachment", _addAttachment);
	createPropertyFunction("isSupported", _isSupported);
	createPropertyFunction("open", _open);

}

TiUIEmailDialogProxy::~TiUIEmailDialogProxy()
{
}

TI_GETTER_DEFER(TiUIEmailDialogProxy, getBarColor)
void TiUIEmailDialogProxy::setBarColor(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIEmailDialogProxy, getBccRecipients)
void TiUIEmailDialogProxy::setBccRecipients(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> allValues = value.toList();
	foreach(Ti::TiValue current, allValues)
	{
		_bccRecipients.append(current.toString());
	}
}
TI_GETTER_DEFER(TiUIEmailDialogProxy, getCcRecipients)
void TiUIEmailDialogProxy::setCcRecipients(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> allValues = value.toList();
	foreach(Ti::TiValue current, allValues)
	{
		_ccRecipients.append(current.toString());
	}
}

TI_GETTER_DEFER(TiUIEmailDialogProxy, getHtml)
void TiUIEmailDialogProxy::setHtml(Ti::TiValue value)
{
	_html = value.toBool();
}
TI_GETTER_DEFER(TiUIEmailDialogProxy, getMessageBody)
void TiUIEmailDialogProxy::setMessageBody(Ti::TiValue value)
{
	_messageBody = value.toString();
}
TI_GETTER_DEFER(TiUIEmailDialogProxy, getSubject)
void TiUIEmailDialogProxy::setSubject(Ti::TiValue value)
{
	_subject = value.toString();
}
TI_GETTER_DEFER(TiUIEmailDialogProxy, getToRecipients)
void TiUIEmailDialogProxy::setToRecipients(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> allValues = value.toList();
	foreach(Ti::TiValue current, allValues)
	{
		_toRecipients.append(current.toString());
	}
}

Ti::TiValue TiUIEmailDialogProxy::getCANCELLED()
{
	return Ti::TiValue();
}
Ti::TiValue TiUIEmailDialogProxy::getFAILED()
{
	return Ti::TiValue();
}
Ti::TiValue TiUIEmailDialogProxy::getSAVED()
{
	return Ti::TiValue();
}
Ti::TiValue TiUIEmailDialogProxy::getSENT()
{
	return Ti::TiValue();
}

Ti::TiValue TiUIEmailDialogProxy::addAttachment(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIEmailDialogProxy::isSupported(Ti::TiValue)
{
	Ti::TiValue val;
	val.setBool(true);
	return val;
}
Ti::TiValue TiUIEmailDialogProxy::open(Ti::TiValue)
{

	// http://supportforums.blackberry.com/t5/Native-Development/Email-Card-not-prepopulating/m-p/2279435/highlight/true#M12814
    QVariantList to;
	foreach(QString str, _toRecipients)
    {
		to << str;
	}

    QVariantList cc;
	foreach(QString str, _ccRecipients)
    {
		cc.append(str);
	}

    QVariantList bcc;
	foreach(QString str, _bccRecipients)
    {
		bcc.append(str);
	}

    QVariantMap data;
	data.insert("to", to);
	data.insert("cc", cc);
	data.insert("bcc", bcc);
	data.insert("subject", _subject);
	data.insert("body", _messageBody);

    bool ok;
    QVariantMap emailData;
    emailData.insert("data", data);

	bb::system::InvokeRequest request;
    request.setAction("bb.action.COMPOSE");
    request.setMimeType("message/rfc822");
    request.setData(bb::PpsObject::encode(emailData, &ok));


    bb::system::InvokeManager *manager = new bb::system::InvokeManager();
    manager->invoke(request);
    delete manager;


	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
