/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeEmailDialogObject.h"
#include "NativeControlObject.h"
#include "TiObject.h"
#include "V8Utils.h"
#include <bb/cascades/InvokeQuery>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/CardPeek>
#include <bb/PpsObject>
#include <iostream>

static NativeEmailDialogObject::PropertyInfo properties[] = {
    { N_EMAIL_PROP_HTML, 0, &NativeEmailDialogObject::setHtml },
    { N_EMAIL_PROP_MESSAGE, 0, &NativeEmailDialogObject::setMessageBody },
    { N_EMAIL_PROP_SUBJECT, 0, &NativeEmailDialogObject::setSubject },
    { N_EMAIL_PROP_TO, 0, &NativeEmailDialogObject::setToRecipients },
    { N_EMAIL_PROP_CC, 0, &NativeEmailDialogObject::setCCRecipients },
    { N_EMAIL_PROP_BCC, 0, &NativeEmailDialogObject::setBCCRecipients },
    { N_EMAIL_PROP_FROM, 0, &NativeEmailDialogObject::setFromRecipients }
};

static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeEmailDialogObject* NativeEmailDialogObject::createEmailDialog(TiObject* tiObject)
{
    return new NativeEmailDialogObject(tiObject);
}

NativeEmailDialogObject::NativeEmailDialogObject(TiObject* tiObject)
    : NativeProxyObject(tiObject),
      PropertyDelegateBase<NativeEmailDialogObject>(this, properties, propertyCount) {

	_html = false;
	_messageBody = "";
	_subject = "";
}

NativeEmailDialogObject::~NativeEmailDialogObject()
{
}

int NativeEmailDialogObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeEmailDialogObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

int NativeEmailDialogObject::setHtml(TiObject* value)
{
	NativeControlObject::getBoolean(value, &_html);
	return NATIVE_ERROR_OK;
}

int NativeEmailDialogObject::setMessageBody(TiObject* value)
{
	_messageBody = titanium::V8ValueToQString(value->getValue());
	return NATIVE_ERROR_OK;

}

int NativeEmailDialogObject::setFromRecipients(TiObject* value)
{
	NativeControlObject::getStringArray(value, _fromRecipients);
	return NATIVE_ERROR_OK;

}
int NativeEmailDialogObject::setSubject(TiObject* value)
{
	_subject = titanium::V8ValueToQString(value->getValue());
	return NATIVE_ERROR_OK;
}


int NativeEmailDialogObject::setCCRecipients(TiObject* value)
{
	NativeControlObject::getStringArray(value, _ccRecipients);
	return NATIVE_ERROR_OK;
}

int NativeEmailDialogObject::setBCCRecipients(TiObject* value)
{
	NativeControlObject::getStringArray(value, _bccRecipients);
	return NATIVE_ERROR_OK;
}

int NativeEmailDialogObject::setToRecipients(TiObject* value)
{
	NativeControlObject::getStringArray(value, _toRecipients);
	return NATIVE_ERROR_OK;
}

void NativeEmailDialogObject::addAttachment(/* Ti.Filesystem */)
{
	// TODO: Add attachments
}

void NativeEmailDialogObject::open() {

	// http://supportforums.blackberry.com/t5/Native-Development/Email-Card-not-prepopulating/m-p/2279435/highlight/true#M12814
    QVariantList to;
	for(int i = 0, len = _toRecipients.count(); i < len; i++) {
		to << _toRecipients.at(i);
	}

    QVariantList cc;
	for(int i = 0, len = _ccRecipients.count(); i < len; i++) {
		cc << _ccRecipients.at(i);
	}

    QVariantList bcc;
	for(int i = 0, len = _bccRecipients.count(); i < len; i++) {
		bcc << _bccRecipients.at(i);
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
}

