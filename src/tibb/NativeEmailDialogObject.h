/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEEMAILDIALOGOBJECT_H_
#define NATIVEEMAILDIALOGOBJECT_H_

#include "NativeProxyObject.h"
#include "PropertyDelegate.h"
#include <QVector>

enum N_EMAIL_PROPS {
    N_EMAIL_PROP_HTML,
    N_EMAIL_PROP_MESSAGE,
    N_EMAIL_PROP_SUBJECT,
    N_EMAIL_PROP_TO,
    N_EMAIL_PROP_CC,
    N_EMAIL_PROP_BCC,
    N_EMAIL_PROP_FROM
};

class NativeEmailDialogObject : public NativeProxyObject,
	                         public titanium::PropertyDelegateBase<NativeEmailDialogObject> {
public:
    static NativeEmailDialogObject* createEmailDialog(TiObject* tiObject);

    virtual NATIVE_TYPE getObjectType() const {
        return N_TYPE_EMAILDIALOG;
    }

    Q_INVOKABLE void open();
    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);

    int setHtml(TiObject* value);
    int setMessageBody(TiObject* value);
    int setSubject(TiObject* value);
    int setToRecipients(TiObject* value);
    int setCCRecipients(TiObject* value);
    int setBCCRecipients(TiObject* value);
    int setFromRecipients(TiObject *value);

    void addAttachment(/* Ti.Filesystem */);
protected:
    virtual ~NativeEmailDialogObject();

private:
    explicit NativeEmailDialogObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeEmailDialogObject(const NativeEmailDialogObject&);
    NativeEmailDialogObject& operator=(const NativeEmailDialogObject&);

    bool _html;
    QString _subject;
    QString _messageBody;
    QVector<QString> _fromRecipients;
    QVector<QString> _toRecipients;
    QVector<QString> _bccRecipients;
    QVector<QString> _ccRecipients;
};

#endif

