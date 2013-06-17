/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewRow.h"

#include "NativeTableViewRowObject.h"

TiUITableViewRow::TiUITableViewRow()
    : TiUIBase("") { }

TiUITableViewRow::~TiUITableViewRow() { }

TiUITableViewRow* TiUITableViewRow::createTableViewRow(NativeObjectFactory* factory) {
    TiUITableViewRow* row = new TiUITableViewRow();
    row->setNativeObjectFactory(factory);
    row->initializeTiObject(NULL);
    return row;
}

void TiUITableViewRow::initializeTiObject(TiObject* parentContext) {
    if (isInitialized()) return;
    TiUIBase::initializeTiObject(parentContext);
    NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TABLE_VIEW_ROW, this);
    setNativeObject(obj);
    obj->release();
}

void TiUITableViewRow::onCreateStaticMembers() {
    TiUIBase::onCreateStaticMembers();
}

