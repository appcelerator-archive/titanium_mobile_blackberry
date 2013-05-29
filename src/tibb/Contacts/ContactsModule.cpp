/*
 * TiContactsObject.cpp
 *
 *  Created on: May 22, 2013
 *      Author: penrique
 */

#include <bb/pim/contacts/ContactListFilters>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/Contact>
#include "TiGenericFunctionObject.h"
#include "NativeMessageStrings.h"
#include "TiMessageStrings.h"
#include <iostream>
#include <QObject>
#include "ContactsModule.h"
#include "ContactsPersonProxy.h"

using namespace bb::pim::contacts;

ContactsModule::ContactsModule(NativeObjectFactory* objectFactory)
	: TiProxy("Contacts")
{
    setNativeObjectFactory(objectFactory);
	// TODO Auto-generated constructor stub

}

void ContactsModule::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
	ContactsModule* obj = new ContactsModule(objectFactory);
    parent->addMember(obj);
}

void ContactsModule::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "getAllPeople", this, _getAllPeople);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getPersonByID", this, _getPersonByID);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createPerson", this, ContactsPersonProxy::createProxy);


}
Handle<Value> ContactsModule::_getPersonByID(void* userContext, TiObject*, const Arguments& args) {

    if (args.Length() < 1 || (!args[0]->IsNumber() && !args[0]->IsNumberObject()))
    {
        v8::ThrowException(String::New(Native::Msg::Expected_argument_of_type_integer));
        return Undefined();
    }

    Handle<Number> num = Handle<Number>::Cast(args[0]);
	Contact c = ContactService().contactDetails((int)num->Value());
	return ContactsPersonProxy::createPerson(c, userContext, args);
}
Handle<Value> ContactsModule::_getAllPeople(void* userContext, TiObject*, const Arguments& args) {

	bb::pim::contacts::ContactService service;
	bb::pim::contacts::ContactListFilters filter;

	QList<bb::pim::contacts::Contact> list = service.contacts(filter);

	Local<Array> array = Array::New(list.size());

	std::cout << "Creating array with " << list.size() << " items" << std::endl;
	for(int i = 0, len = list.size(); i < len; i++) {
		bb::pim::contacts::Contact contact = list.at(i);
		array->Set(i, ContactsPersonProxy::createPerson(contact,userContext, args));
	}
	std::cout << "End loop" << std::endl;

	return array;
}

ContactsModule::~ContactsModule() {
	// TODO Auto-generated destructor stub
}
