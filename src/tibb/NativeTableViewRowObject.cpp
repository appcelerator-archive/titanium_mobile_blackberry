/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTableViewRowObject.h"

#include <bb/cascades/Container>
#include <bb/cascades/VisualNode>

#include "TableView/TableViewRowData.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

using namespace bb::cascades;

NativeTableViewRowObject::NativeTableViewRowObject(TiObject* object)
    : NativeControlObject(object, N_TYPE_TABLE_VIEW_ROW)
    , data_(new TableViewRowData(object)) {
    // Prevent the data object from getting destroyed
    // when it is removed from the data model. It should live
    // until this native object is deleted.
    data_->setParent(data_.data());
}

NativeTableViewRowObject::~NativeTableViewRowObject() {
}

void NativeTableViewRowObject::removeHeader() {
	data_->setProperty("header", "");
}

int NativeTableViewRowObject::addChildNativeObject(NativeObject* obj) {
    if (!data_->content()) {
        data_->setContent(this);
    }
    return addChildImpl(obj);
}

int NativeTableViewRowObject::setLeftImage(TiObject* obj) {
    QString imagePath = V8ValueToQString(obj->getValue());
    data_->setProperty("leftImage", QUrl(getResourcePath(imagePath)));
    return NATIVE_ERROR_OK;
}

int NativeTableViewRowObject::setTitle(TiObject* obj) {
    data_->setProperty("title", V8ValueToQString(obj->getValue()));
    return NATIVE_ERROR_OK;
}

int NativeTableViewRowObject::setHeader(TiObject* obj) {
    data_->setProperty("header", V8ValueToQString(obj->getValue()));
    return NATIVE_ERROR_OK;
}

int NativeTableViewRowObject::setSubHeader(TiObject* obj) {
    data_->setProperty("subHeader", V8ValueToQString(obj->getValue()));
    return NATIVE_ERROR_OK;
}

QVariant NativeTableViewRowObject::data() const {
    return QVariant::fromValue(static_cast<QObject*>(data_.data()));
}

