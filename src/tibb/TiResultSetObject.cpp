/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiResultSetObject.h"

#include "NativeException.h"
#include "NativeResultSetObject.h"
#include "TiBufferObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiMessageStrings.h"

const static TiProperty g_tiProperties[] = {
	{
		"connected", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_RESULTSET_PROP_CONNECTED
	},
};

TiResultSetObject::TiResultSetObject()
    : TiProxy("RESULTSET") {
}

TiResultSetObject::~TiResultSetObject() {
}

void TiResultSetObject::addObjectToParent(TiObject* parent) {
    TiResultSetObject* obj = new TiResultSetObject;
    parent->addMember(obj);
    obj->release();
}

TiResultSetObject* TiResultSetObject::createTCP(NativeObjectFactory* objectFactory) {
    TiResultSetObject* obj = new TiResultSetObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiResultSetObject::initializeTiObject(TiObject* parentContext) {
    if (!isInitialized()) {
    	TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_RESULTSET, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiResultSetObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    setTiBufferMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "connect", this, _connect);
}

void TiResultSetObject::setTiBufferMappingProperties(const TiProperty* props, int propertyCount) {
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++) {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueModify, _getValue, this);
        // For all properties that have write permissions, add a setter method, e.g., myLabel.text=<my text>; myLabel.setText(<my text>);
        if (props[i].permissions & TI_PROP_PERMISSION_WRITE) {
            c[0] = toupper(props[i].propertyName[0]);
            name = "set";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertySetFunctionObject::addPropertySetter(this, value, name.c_str());
        }
        // For all properties that have read permissions, add a getter method, e.g., var test=myLabel.text; var test=myLabel.getText();
        if (props[i].permissions & TI_PROP_PERMISSION_READ) {
            c[0] = toupper(props[i].propertyName[0]);
            name = "get";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
        }
        value->release();
    }
}

Handle<Value> TiResultSetObject::_getValue(int propertyNumber, void* context) {
    TiResultSetObject* self = (TiResultSetObject*) context;
    NativeResultSetObject* object = (NativeResultSetObject*)self->getNativeObject();
    TiObject value;
    if (object != NULL) {
        object->getPropertyValue(propertyNumber, &value, context);
    }
    return value.getValue();
}

VALUE_MODIFY TiResultSetObject::_valueModify(int propertyNumber, TiObject* value, void* context) {
    TiResultSetObject* self = (TiResultSetObject*) context;
    NativeResultSetObject* object = (NativeResultSetObject*)self->getNativeObject();
    if (object == NULL) {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value, self)) {
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

Handle<Value> TiResultSetObject::_connect(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/) {
    HandleScope handleScope;
    TiResultSetObject* obj = (TiResultSetObject*) userContext;
    NativeResultSetObject* nrs = (NativeResultSetObject*) obj->getNativeObject();
    try {
        nrs->connect();
    }
    catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}
