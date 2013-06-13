/*
 * TiPropertySetGetObject.cpp
 *
 *  Created on: May 24, 2013
 *      Author: penrique
 */

#include "TiPropertySetGetObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include <iostream>

TiPropertySetGetObject::TiPropertySetGetObject(const char* propertyName):
        TiObject(propertyName),
        context_(NULL),
        setCallback_(NULL),
        getCallback_(NULL)
{
}

TiPropertySetGetObject::~TiPropertySetGetObject()
{
}

VALUE_MODIFY TiPropertySetGetObject::setValue(Handle<Value> value)
{
    if (setCallback_ != NULL)
    {
    	(setCallback_)(context_, value);
    }
	return VALUE_MODIFY_ALLOW;
}

Handle<Value> TiPropertySetGetObject::getValue() const
{
    if (getCallback_ == NULL)
    {
        return Undefined();
    }
    return (getCallback_)(context_);
}


void TiPropertySetGetObject::createProperty(TiObject* parent, const char* name, void* context,
		SET_PROPERTY_CALLBACK scb, GET_PROPERTY_CALLBACK gcb)
{
	TiPropertySetGetObject *obj = new TiPropertySetGetObject(name);
	obj->context_ = context;
	obj->setCallback_ = scb;
	obj->getCallback_ = gcb;
	parent->addMember(obj);

	std::string methodName = name;
	std::string getter;
	std::string setter;

	methodName[0] = toupper(methodName[0]);
	getter = "get" + methodName;
	setter = "set" + methodName;

	TiPropertySetFunctionObject::addPropertySetter(parent, obj, setter.c_str());
	TiPropertyGetFunctionObject::addPropertyGetter(parent, obj, getter.c_str());

}

VALUE_MODIFY TiPropertySetGetObject::onValueChange(Handle<Value> oldValue, Handle<Value> newValue)
{
	return VALUE_MODIFY_ALLOW;
}


