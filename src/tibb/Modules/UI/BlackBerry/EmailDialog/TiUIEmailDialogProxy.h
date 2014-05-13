/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIEMAILDIALOGPROXY_H_
#define TI_TIUIEMAILDIALOGPROXY_H_

#include "TiCore.h"

namespace TiUI {

class TiUIEmailDialogProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiUIEmailDialogProxy)
	TiUIEmailDialogProxy(const char*);
	virtual ~TiUIEmailDialogProxy();

	Ti::TiValue addAttachment(Ti::TiValue);
	Ti::TiValue isSupported(Ti::TiValue);
	Ti::TiValue open(Ti::TiValue);

	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setBarColor, getBarColor)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setBccRecipients, getBccRecipients)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setCcRecipients, getCcRecipients)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setHtml, getHtml)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setMessageBody, getMessageBody)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setSubject, getSubject)
	TI_CREATE_SETTER_GETTER(TiUIEmailDialogProxy, setToRecipients, getToRecipients)

	TI_CREATE_GETTER(TiUIEmailDialogProxy, getCANCELLED)
	TI_CREATE_GETTER(TiUIEmailDialogProxy, getFAILED)
	TI_CREATE_GETTER(TiUIEmailDialogProxy, getSAVED)
	TI_CREATE_GETTER(TiUIEmailDialogProxy, getSENT)

	EXPOSE_METHOD(TiUIEmailDialogProxy, addAttachment)
	EXPOSE_METHOD(TiUIEmailDialogProxy, isSupported)
	EXPOSE_METHOD(TiUIEmailDialogProxy, open)
private:
    bool _html;
    QString _subject;
    QString _messageBody;
    QList<QString> _fromRecipients;
    QList<QString> _toRecipients;
    QList<QString> _bccRecipients;
    QList<QString> _ccRecipients;

};

}
#endif /* TIUIEMAILDIALOGPROXY_H_ */
