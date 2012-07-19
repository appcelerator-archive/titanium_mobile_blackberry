/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAlertDialogObject.h"
#include "TiEventContainerFactory.h"

NativeAlertDialogObject::NativeAlertDialogObject()
{
}

NativeAlertDialogObject::~NativeAlertDialogObject()
{
}

NativeAlertDialogObject* NativeAlertDialogObject::createAlertDialog()
{
    return new NativeAlertDialogObject();
}

int NativeAlertDialogObject::getObjectType() const
{
    return N_TYPE_ALERTDIALOG;
}

int NativeAlertDialogObject::initialize()
{
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setTitle(TiObject* obj)
{
    int error = NativeControlObject::getString(obj, alertTitle_);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setMessage(TiObject* obj)
{
    int error = NativeControlObject::getString(obj, alertMessage_);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::show()
{
    dialog_create_alert(&nativeDialog_);
    dialog_set_alert_message_text(nativeDialog_, alertMessage_.toUtf8().constData());
    dialog_set_title_text(nativeDialog_, alertTitle_.toUtf8().constData());
    dialog_set_background_alpha(nativeDialog_, 0.0);
    dialog_set_cover_sensitivity(nativeDialog_, DIALOG_COVER_SENSITIVITY_ALPHA_TEST);

    dialog_add_button(nativeDialog_, DIALOG_CANCEL_LABEL, true, NULL, true);
    dialog_add_button(nativeDialog_, DIALOG_OK_LABEL, true, NULL, true);
    dialog_show(nativeDialog_);
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::hide()
{
    dialog_cancel(nativeDialog_);
    dialog_destroy(nativeDialog_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeAlertDialogObject::getNativeHandle() const
{
    return NULL;
}
