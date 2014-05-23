/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiResultSetObject.h"

#include "NativeResultSetObject.h"
#include "TiResultSetObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetObject.h"
#include "NativeException.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiMessageStrings.h"


const static TiProperty g_tiProperties[] =
{
    {"rowCount", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_RESULTSET_PROP_ROWCOUNT},
    {"fieldCount", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_RESULTSET_PROP_FIELDCOUNT}
};


TiResultSetObject::TiResultSetObject()
    : TiProxy("ResultSet") {
    objectFactory_ = NULL;
}

TiResultSetObject::TiResultSetObject(NativeObjectFactory* objectFactory)
    : TiProxy("ResultSet") {
    objectFactory_ = objectFactory;
}

TiResultSetObject::~TiResultSetObject() {
}

void TiResultSetObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory) {
}

TiResultSetObject* TiResultSetObject::createResultSet(NativeObjectFactory* objectFactory) {
	TiResultSetObject* obj = new TiResultSetObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiResultSetObject::initializeTiObject(TiObject* parentContext) {
    if (!isInitialized()) {
        TiProxy::initializeTiObject(parentContext);
        NativeResultSetObject* obj = (NativeResultSetObject*)getNativeObjectFactory()->createNativeObject(N_TYPE_RESULTSET, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiResultSetObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    setTiResultSetMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties)); // property setter/getter
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isValidRow", this, _isValidRow);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fieldByName", this, _fieldByName);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "field", this, _field);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "next", this, _next);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fieldName", this, _fieldName);
}

// Properties boiler plate
void TiResultSetObject::setTiResultSetMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueModify, _getValue, this);
        // For all properties that have write permissions, add a setter method, e.g., myLabel.text=<my text>; myLabel.setText(<my text>);
        if (props[i].permissions & TI_PROP_PERMISSION_WRITE)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "set";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertySetFunctionObject::addPropertySetter(this, value, name.c_str());
        }
        // For all properties that have read permissions, add a getter method, e.g., var test=myLabel.text; var test=myLabel.getText();
        if (props[i].permissions & TI_PROP_PERMISSION_READ)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "get";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
        }
        value->release();
    }
}

Handle<Value> TiResultSetObject::_getValue(int propertyNumber, void* context)
{
	TiResultSetObject* self = (TiResultSetObject*) context;
    NativeResultSetObject* object = (NativeResultSetObject*)self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value, context);
    }
    return value.getValue();
}

VALUE_MODIFY TiResultSetObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
	TiResultSetObject* self = (TiResultSetObject*) context;
    NativeResultSetObject* object = (NativeResultSetObject*)self->getNativeObject();
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value, self))
    {
    case NATIVE_ERROR_OK:
        modify = VALUE_MODIFY_ALLOW;
        break;
    case NATIVE_ERROR_NOTSUPPORTED:
        modify = VALUE_MODIFY_NOT_SUPPORTED;
        break;
    default:
        modify = VALUE_MODIFY_INVALID;
        break;
    }
    object->release();
    return modify;
}
// End properties boiler plate

Handle<Value> TiResultSetObject::_isValidRow(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	bool isVaildRow = nativeResultSet->isValidRow();

    return handleScope.Close(Boolean::New(isVaildRow));
}

Handle<Value> TiResultSetObject::_fieldByName(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	if (args.Length() < 1) {
		return ThrowException(String::New(Ti::Msg::Missing_argument));
	}

	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	string value = nativeResultSet->fieldByName(TiObject::getSTDStringFromValue(args[0]));

	int index = nativeResultSet->fieldIndexByName(TiObject::getSTDStringFromValue(args[0]));
	if (nativeResultSet->fieldType(index) == STRING_FIELD) {
		return handleScope.Close(String::New(value.c_str()));
	}
	else {
		return handleScope.Close(Number::New(atof(value.c_str())));
	}
}

Handle<Value> TiResultSetObject::_fieldName(void* userContext, TiObject*, const Arguments& args)
{
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	int index = args[0]->ToNumber()->Value();
	string name = nativeResultSet->fieldName(index);
	if(name.size() > 0)
		return handleScope.Close(String::New(name.c_str()));
	return handleScope.Close(Undefined());
}

Handle<Value> TiResultSetObject::_field(void* userContext, TiObject*, const Arguments& args) {

	HandleScope handleScope;
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	int index  = Handle<Integer>::Cast(args[0])->Value();
	string value = nativeResultSet->field(index);

    if (nativeResultSet->fieldType(index) == STRING_FIELD) {
		return handleScope.Close(String::New(value.c_str()));
	}
	else {
		return handleScope.Close(Number::New(atof(value.c_str())));
	}
}

Handle<Value> TiResultSetObject::_next(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	bool isVaildRow = nativeResultSet->next();

	return handleScope.Close(Boolean::New(isVaildRow));
}

Handle<Value> TiResultSetObject::_close(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiResultSetObject* obj = (TiResultSetObject*) userContext;
	NativeResultSetObject* nativeResultSet = (NativeResultSetObject*) obj->getNativeObject();
	nativeResultSet->close();

	return Undefined();
}


