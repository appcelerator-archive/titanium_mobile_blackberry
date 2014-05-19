/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef CONTACTSCONTACTPROXY_H_
#define CONTACTSCONTACTPROXY_H_

#include "../TiProxy.h"
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactBuilder>
#include <iostream>

using namespace bb::pim::contacts;

class ContactsPersonProxy: public TiProxy
{
public:
    ContactsPersonProxy();
    ContactsPersonProxy(bb::pim::contacts::Contact);
    virtual ~ContactsPersonProxy();
    virtual void onCreateStaticMembers();

    void openConnection();
    void closeConnection();

    static ContactsPersonProxy* createPerson(NativeObjectFactory* objectFactory);
    static Handle<Value> createContact(bb::pim::contacts::Contact, const Arguments&);
    static Handle<Value> createPerson(bb::pim::contacts::Contact contact, void* userContext, const Arguments& args)
    {
        return TiProxy::createProxy(new ContactsPersonProxy(contact), userContext, args);
    };
    static Handle<Value> createProxy(void* userContext, TiObject*, const Arguments& args)
    {
    	ContactsPersonProxy *contact = new ContactsPersonProxy();
    	contact->openConnection();
    	Handle<Value> contactProxy = TiProxy::createProxy(contact, userContext, args);
    	contact->closeConnection();
    	return contactProxy;
    };
    ContactId getPersonId();

protected:


private:


    static void _setAddress(void*, Handle<Value>);
    static void _setBirthday(void*, Handle<Value>);
    static void _setCreated(void*, Handle<Value>);
    static void _setDepartment(void*, Handle<Value>);
    static void _setEmail(void*, Handle<Value>);
    static void _setFirstName(void*, Handle<Value>);
    static void _setFirstPhonetic(void*, Handle<Value>);
    static void _setFullName(void*, Handle<Value>);
    static void _setId(void*, Handle<Value>);
    static void _setImage(void*, Handle<Value>);
    static void _setInstantMessage(void*, Handle<Value>);
    static void _setJobTitle(void*, Handle<Value>);
    static void _setKind(void*, Handle<Value>);
    static void _setLastName(void*, Handle<Value>);
    static void _setLastPhonetic(void*, Handle<Value>);
    static void _setMiddleName(void*, Handle<Value>);
    static void _setMiddlePhonetic(void*, Handle<Value>);
    static void _setModified(void*, Handle<Value>);
    static void _setNickname(void*, Handle<Value>);
    static void _setNote(void*, Handle<Value>);
    static void _setOrganization(void*, Handle<Value>);
    static void _setPhone(void*, Handle<Value>);
    static void _setPrefix(void*, Handle<Value>);
    static void _setRecordId(void*, Handle<Value>);
    static void _setRelatedNames(void*, Handle<Value>);
    static void _setSuffix(void*, Handle<Value>);
    static void _setUrl(void*, Handle<Value>);

    static Handle<Value> _getAddress(void*);
    static Handle<Value> _getBirthday(void*);
    static Handle<Value> _getCreated(void*);
    static Handle<Value> _getDepartment(void*);
    static Handle<Value> _getEmail(void*);
    static Handle<Value> _getFirstName(void*);
    static Handle<Value> _getFirstPhonetic(void*);
    static Handle<Value> _getFullName(void*);
    static Handle<Value> _getId(void*);
    static Handle<Value> _getImage(void*);
    static Handle<Value> _getInstantMessage(void*);
    static Handle<Value> _getJobTitle(void*);
    static Handle<Value> _getKind(void*);
    static Handle<Value> _getLastName(void*);
    static Handle<Value> _getLastPhonetic(void*);
    static Handle<Value> _getMiddleName(void*);
    static Handle<Value> _getMiddlePhonetic(void*);
    static Handle<Value> _getModified(void*);
    static Handle<Value> _getNickname(void*);
    static Handle<Value> _getNote(void*);
    static Handle<Value> _getOrganization(void*);
    static Handle<Value> _getPhone(void*);
    static Handle<Value> _getPrefix(void*);
    static Handle<Value> _getRecordId(void*);
    static Handle<Value> _getRelatedNames(void*);
    static Handle<Value> _getSuffix(void*);
    static Handle<Value> _getUrl(void*);

    bool isEditing;
    void setContactDetails(AttributeKind::Type, AttributeSubKind::Type, Handle<Value>);
    Handle<Value> getSubkind(bb::pim::contacts::AttributeSubKind::Type);
    Handle<Value> getKind(bb::pim::contacts::AttributeKind::Type);
    bb::pim::contacts::Contact getFullContact();
    bb::pim::contacts::Contact contact_;
    bb::pim::contacts::ContactBuilder builder_;
};

#endif /* CONTACTSCONTACTPROXY_H_ */
