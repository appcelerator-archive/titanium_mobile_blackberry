/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewSection.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetGetObject.h"
#include "TiUtils.h"

TiUITableViewSection::TiUITableViewSection() : TiProxy() {
	rowsInSection = Persistent<Array>::New(Array::New());
	Handle<Object> header = Object::New();
	header->Set(String::New("header"), String::New(" "));
	header->Set(String::New("isHeader"), Boolean::New(true));
	addRow(header);
}

void TiUITableViewSection::addRow(Handle<Value> row)
{
	uint32_t index = rowsInSection->Length();

	rowsInSection->Set(index, row);
}

Handle<Array> TiUITableViewSection::getRowsInSection(){
	return rowsInSection;
}


TiUITableViewSection::~TiUITableViewSection() {
	// TODO Auto-generated destructor stub
}

void TiUITableViewSection::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "add", this, _add);
    TiPropertySetGetObject::createProperty(this, "title", this, _setTitle, _getTitle);
    TiPropertySetGetObject::createProperty(this, "subTitle", this, _setSubTitle, _getSubTitle);
}

Handle<Value> TiUITableViewSection::_add(void* userContext, TiObject*, const Arguments& args) {
	HandleScope scope;
	TiUITableViewSection* section = (TiUITableViewSection*)userContext;
	section->addRow(args[0]);
	return Undefined();
}

void TiUITableViewSection::_setTitle(void* userContext, Handle<Value> val)
{
	TiUITableViewSection *section = (TiUITableViewSection*)userContext;
	Handle<Array> sect = section->getRowsInSection();
	Handle<Object> header = sect->Get(0)->ToObject();
	header->Set(String::New("header"), val);
}

void TiUITableViewSection::_setSubTitle(void* userContext, Handle<Value> val)
{
	TiUITableViewSection *section = (TiUITableViewSection*)userContext;
	Handle<Array> sect = section->getRowsInSection();
	Handle<Object> header = sect->Get(0)->ToObject();
	header->Set(String::New("subHeader"), val);
}

Handle<Value> TiUITableViewSection::_getTitle(void* userContext)
{
	HandleScope scope;
	TiUITableViewSection *section = (TiUITableViewSection*)userContext;
	Handle<Array> sect = section->getRowsInSection();
	Handle<Object> header = sect->Get(0)->ToObject();
	return scope.Close(header->Get(String::New("header")));
}

Handle<Value> TiUITableViewSection::_getSubTitle(void* userContext)
{
	HandleScope scope;
	TiUITableViewSection *section = (TiUITableViewSection*)userContext;
	Handle<Array> sect = section->getRowsInSection();
	Handle<Object> header = sect->Get(0)->ToObject();
	if(header->Has(String::New("header")))
		return scope.Close(header->Get(String::New("header")));
	return Undefined();
}

