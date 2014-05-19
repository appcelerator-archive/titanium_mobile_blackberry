/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/ContactPhoto>
#include <bb/pim/contacts/ContactPostalAddress>
#include <bb/pim/contacts/ContactAttributeBuilder>
#include <bb/pim/contacts/ContactPostalAddressBuilder>
#include <QtAlgorithms>
#include <QFile>
#include <TiCore.h>

#include "ContactsPersonProxy.h"
#include "../TiGenericFunctionObject.h"
#include "../TiPropertyGetObject.h"
#include "../V8Utils.h"
#include "../TiUtils.h"
#include "../TiBlobObject.h"

using namespace bb::pim::contacts;

ContactsPersonProxy::ContactsPersonProxy() :
        TiProxy("Person")
{
    ContactService service;
    ContactBuilder builder;
    isEditing = false;
    contact_ = service.createContact(builder, false);

}
ContactsPersonProxy::ContactsPersonProxy(Contact contact) :
        TiProxy("Person")
{
	isEditing = false;
    contact_ = contact;
}
ContactsPersonProxy::~ContactsPersonProxy()
{
}
ContactsPersonProxy* ContactsPersonProxy::createPerson(NativeObjectFactory* objectFactory) {
    ContactsPersonProxy* obj = new ContactsPersonProxy;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;

}
void ContactsPersonProxy::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();

    createSettersAndGetters("address", _setAddress, _getAddress);
    createSettersAndGetters("birthday", _setBirthday, _getBirthday);
    createSettersAndGetters("created", _setCreated, _getCreated);
    createSettersAndGetters("department", _setDepartment, _getDepartment);
    createSettersAndGetters("email", _setEmail, _getEmail);
    createSettersAndGetters("firstName", _setFirstName, _getFirstName);
    createSettersAndGetters("fullName", _setFullName, _getFullName);
    createSettersAndGetters("firstPhonetic", _setFirstPhonetic, _getFirstPhonetic);
    createSettersAndGetters("id", _setId, _getId);
    createSettersAndGetters("image", _setImage, _getImage);
    createSettersAndGetters("instantMessage", _setInstantMessage, _getInstantMessage);
    createSettersAndGetters("jobTitle", _setJobTitle, _getJobTitle);
    createSettersAndGetters("kind", _setKind, _getKind);
    createSettersAndGetters("lastName", _setLastName, _getLastName);
    createSettersAndGetters("lastPhonetic", _setLastPhonetic, _getLastPhonetic);
    createSettersAndGetters("middleName", _setMiddleName, _getMiddleName);
    createSettersAndGetters("middlePhonetic", _setMiddlePhonetic, _getMiddlePhonetic);
    createSettersAndGetters("modified", _setModified, _getModified);
    createSettersAndGetters("nickname", _setNickname, _getNickname);
    createSettersAndGetters("note", _setNote, _getNote);
    createSettersAndGetters("organization", _setOrganization, _getOrganization);
    createSettersAndGetters("phone", _setPhone, _getPhone);
    createSettersAndGetters("prefix", _setPrefix, _getPrefix);
    createSettersAndGetters("recordId", _setRecordId, _getRecordId);
    createSettersAndGetters("relatedNames", _setRelatedNames, _getRelatedNames);
    createSettersAndGetters("suffix", _setSuffix, _getSuffix);
    createSettersAndGetters("url", _setUrl, _getUrl);

}

ContactId ContactsPersonProxy::getPersonId()
{
	return contact_.id();
}
void ContactsPersonProxy::openConnection() {
    isEditing = true;
	builder_ = contact_.edit();
}
void ContactsPersonProxy::closeConnection() {
	ContactService().updateContact(contact_);
	isEditing = false;
}

Contact ContactsPersonProxy::getFullContact()
{
    return ContactService().contactDetails(contact_.id());
}

Handle<Value> ContactsPersonProxy::getSubkind(AttributeSubKind::Type subkind)
{
    QList<ContactAttribute> array = getFullContact().attributes();

    for (int i = 0, len = array.length(); i < len; i++) {
        ContactAttribute attr = array.at(i);
        if (attr.subKind() == subkind) {
            QString name = attr.value();
            return String::New(name.toUtf8().constData());
        }
    }
    return String::New("");
}

Handle<Value> ContactsPersonProxy::getKind(AttributeKind::Type kind)
{
    QList<ContactAttribute> array = getFullContact().attributes();

    for (int i = 0, len = array.length(); i < len; i++) {
        ContactAttribute attr = array.at(i);
        if (attr.kind() == kind) {
            QString name = attr.value();
            return String::New(name.toUtf8().constData());
        }
    }
    return String::New("");
}

void ContactsPersonProxy::setContactDetails(AttributeKind::Type kind, AttributeSubKind::Type subKind, Handle<Value> value)
{
    QString val = titanium::V8ValueToQString(value);
    if(!isEditing) {
    	builder_ = contact_.edit();
    }
    ContactAttributeBuilder attribute;
    attribute.setKind(kind);
    attribute.setSubKind(subKind);
    attribute.setValue(val);
    builder_.addAttribute(attribute);
    if(!isEditing) {
    	ContactService().updateContact(contact_);
    }
}

// SETTERS

void ContactsPersonProxy::_setAddress(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    if(!obj->isEditing) {
    	obj->builder_ = obj->contact_.edit();
    }

    // The value passed in *MUST* be an object containing arrays of objects
    // http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Contacts.Person-property-address
    if(!value->IsObject()) return;

	// Get the JS Object and it's properties
	Local<Object> addressObject = value->ToObject();
	Local<Array> addressProperties = addressObject->GetPropertyNames();

	// Look for properties, such as "work", "home", or "other"
	for(int i = 0, len = addressProperties->Length(); i < len; i++)
	{
		// Get the key and value or each main object
		// { work: [ ... ] }"
		Local<String> addressKey = addressProperties->Get(i)->ToString();
		Local<Value> addressValue = addressObject->Get(addressKey);

		// Create the subkind from the key of the object
		AttributeSubKind::Type subKind = AttributeSubKind::Other;
		QString _key = titanium::V8ValueToQString(addressKey);
		if(_key.toLower() == "work") {
			subKind = AttributeSubKind::Work;
		}
		if(_key.toLower() == "home") {
			subKind = AttributeSubKind::Home;
		}

		// The value of the individual address object *MUST* be an array of address objects
		// [ { street: '12 Main St' }, { street: '21 Meh St' } ]
		if(!addressValue->IsArray()) return;
		// Cast the value of the array to a v8 Array and look for addresses
		Local<Array> addresses = Local<Array>::Cast(addressValue);
		for(int i = 0, len = addresses->Length(); i < len; i++)
		{
			// Create the new address builder object and set the subkind
			ContactPostalAddressBuilder addressBuilder;
			addressBuilder.setSubKind(subKind);

			// Get the actual address object from the array of address objects
			// This *MUST* be an object with keys and values
			// { street: '12 Main St' }
			Local<Value> currentAddress = addresses->Get(Number::New(i));
			if(!currentAddress->IsObject()) return;
			// Get the individual address object and look for it's properties
			Local<Object> currentAddressObject = currentAddress->ToObject();
			Local<Array> currentAddressProperties = currentAddressObject->GetPropertyNames();

			// Go through the keys and value of this object, one at a time
			for(int i = 0, len = currentAddressProperties->Length(); i < len; i++)
			{
				Local<String> currentAddressKey = currentAddressProperties->Get(i)->ToString();
				Local<Value> currentAddressValue = currentAddressObject->Get(currentAddressKey);

				// The value *MUST* be a string
				if(!currentAddressValue->IsString()) return;

				// Cast it to a String and get the UTF8 strings
				Local<String> currentAddressStringValue = currentAddressValue->ToString();

				// Convert them to QStrings for better manipulation
				QString _key = titanium::V8ValueToQString(currentAddressKey);
				QString _value = titanium::V8ValueToQString(currentAddressStringValue);

				// Start populating the address builder
				if(_key.toLower() == "city"){
					addressBuilder.setCity(_value);
				}
				if(_key.toLower() == "label"){
					addressBuilder.setLabel(_value);
				}
				if(_key.toLower() == "line1"){
					addressBuilder.setLine1(_value);
				}
				if(_key.toLower() == "line2") {
					addressBuilder.setLine2(_value);
				}
				if(_key.toLower() == "street") {
					if(_value.contains("\n")) {
						QStringList l = _value.split('\n');
						addressBuilder.setLine1(l.at(0));
						l.removeAt(0);
						addressBuilder.setLine2(l.join(""));
					} else {
						addressBuilder.setLine1(_value);
					}
				}
				if(_key.toLower() == "zip"){
					addressBuilder.setPostalCode(_value);
				}
				if(_key.toLower() == "county"){
					addressBuilder.setRegion(_value);
				}
				if(_key.toLower() == "country"){
					addressBuilder.setCountry(_value);
				}
			}
			// Once finished with an address, add it to the contact
				obj->builder_.addPostalAddress(addressBuilder);
		}
	 }
    // Once done, update the contact
    if(!obj->isEditing) {
    	ContactService().updateContact(obj->contact_);
    }
}
void ContactsPersonProxy::_setBirthday(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    QDateTime bd;
    if(TiUtils::getDateTime(value, bd) == NATIVE_ERROR_OK)
    {
        QString val = titanium::V8ValueToQString(value);
        if(!obj->isEditing) {
        	obj->builder_ = obj->contact_.edit();
    	}
        ContactAttributeBuilder attribute;
        attribute.setKind(AttributeKind::Date);
        attribute.setSubKind(AttributeSubKind::DateBirthday);
        attribute.setValue(bd);
        obj->builder_.addAttribute(attribute);
        if(!obj->isEditing) {
        	ContactService().updateContact(obj->contact_);
        }

    }
    else
    {
    	Ti::TiHelper::Log("[WARN] Birthday MUST be a Date object");
    }
}
void ContactsPersonProxy::_setCreated(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setDepartment(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Group, AttributeSubKind::GroupDepartment, value);
}
void ContactsPersonProxy::_setEmail(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    if(!value->IsObject()) return;

	Handle<Object> emailObject = value->ToObject();
	Local<Array> emailProperties = emailObject->GetPropertyNames();
	for(int i = 0, len = emailProperties->Length(); i < len; i++)
	{
		Local<String> allEmailsKey = emailProperties->Get(i)->ToString();
		Local<Value> allEmailsValue = emailObject->Get(allEmailsKey);

		AttributeSubKind::Type subKind = AttributeSubKind::Other;

		QString allEmailsKeyString = titanium::V8ValueToQString(allEmailsKey).toLower();
		if(allEmailsKeyString == "work")
		{
			subKind = AttributeSubKind::Work;
		}
		else
		if(allEmailsKeyString == "personal")
		{
			subKind = AttributeSubKind::Personal;
		}
		else
		if(allEmailsKeyString == "home")
		{
			subKind = AttributeSubKind::Home;
		}

		if(!allEmailsValue->IsArray()) return;

		Local<Array> emails = Local<Array>::Cast(allEmailsValue);
		for(int i = 0, len = emails->Length(); i < len; i++)
		{
			Local<Value> emailValue = emails->Get(Number::New(i));
			if(emailValue->IsString() || emailValue->IsNumber())
			{
				 obj->setContactDetails(AttributeKind::Email, subKind, emailValue);
			}
			else
			{
				// Something goes here, throw an error?
			}
		}
	}
}
void ContactsPersonProxy::_setFirstName(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NameGiven, value);
}
void ContactsPersonProxy::_setFirstPhonetic(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NamePhoneticGiven, value);
}
void ContactsPersonProxy::_setFullName(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not implemented yet
}
void ContactsPersonProxy::_setId(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setImage(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not implemented yet
}
void ContactsPersonProxy::_setInstantMessage(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    if(!value->IsObject()) return;

    Handle<Object> messageObject = value->ToObject();
	Local<Array> messageProperties = messageObject->GetPropertyNames();

	for(int i = 0, len = messageProperties->Length(); i < len; i++)
	{
		Local<String> messageKey = messageProperties->Get(i)->ToString();
		Local<Value> messageValue = messageObject->Get(messageKey);

		AttributeSubKind::Type subKind = AttributeSubKind::Other;
		QString messageKeyString = titanium::V8ValueToQString(messageKey).toLower();

		if(messageKeyString == "aim") {
			subKind = AttributeSubKind::InstantMessagingAim;
		} else
		if(messageKeyString == "aliwangwang") {
			subKind = AttributeSubKind::InstantMessagingAliwangwang;
		} else
		if(messageKeyString == "bbmpin") {
			subKind = AttributeSubKind::InstantMessagingBbmPin;
		} else
		if(messageKeyString == "googletalk") {
			subKind = AttributeSubKind::InstantMessagingGoogleTalk;
		} else
		if(messageKeyString == "icq") {
			subKind = AttributeSubKind::InstantMessagingIcq;
		} else
		if(messageKeyString == "irc") {
			subKind = AttributeSubKind::InstantMessagingIrc;
		} else
		if(messageKeyString == "jabber") {
			subKind = AttributeSubKind::InstantMessagingJabber;
		} else
		if(messageKeyString == "msLcs") {
			subKind = AttributeSubKind::InstantMessagingMsLcs;
		} else
		if(messageKeyString == "msn") {
			subKind = AttributeSubKind::InstantMessagingMsn;
		} else
		if(messageKeyString == "qq") {
			subKind = AttributeSubKind::InstantMessagingQq;
		} else
		if(messageKeyString == "sametime") {
			subKind = AttributeSubKind::InstantMessagingSametime;
		} else
		if(messageKeyString == "skype") {
			subKind = AttributeSubKind::InstantMessagingSkype;
		} else
		if(messageKeyString == "yahoomessenger") {
			subKind = AttributeSubKind::InstantMessagingYahooMessenger;
		} else
		if(messageKeyString == "yahoomessengerjapan") {
			subKind = AttributeSubKind::InstantMessagingYahooMessengerJapan;
		}

		if(!messageValue->IsArray()) return;

		Local<Array> messages = Local<Array>::Cast(messageValue);
		for(int i = 0, len = messages->Length(); i < len; i++)
		{
			Local<Value> currentMessage = messages->Get(Number::New(i));
			if(!currentMessage->IsString()) return;

			obj->setContactDetails(AttributeKind::InstantMessaging, subKind, currentMessage);
		}
	}
}
void ContactsPersonProxy::_setJobTitle(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::Title, value);
}
void ContactsPersonProxy::_setKind(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setLastName(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NameSurname, value);
}
void ContactsPersonProxy::_setLastPhonetic(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NamePhoneticSurname, value);
}
void ContactsPersonProxy::_setMiddleName(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NameMiddle, value);
}
void ContactsPersonProxy::_setMiddlePhonetic(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setModified(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setNickname(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NameNickname, value);
}
void ContactsPersonProxy::_setNote(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Note, AttributeSubKind::Other, value);
}
void ContactsPersonProxy::_setOrganization(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::OrganizationAffiliation, AttributeSubKind::OrganizationAffiliationName, value);
}
void ContactsPersonProxy::_setPhone(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    if(!value->IsObject()) return;

    Handle<Object> phoneObject = value->ToObject();
	Local<Array> phoneProperties = phoneObject->GetPropertyNames();

	for(int i = 0, len = phoneProperties->Length(); i < len; i++)
	{
		Local<String> phoneKey = phoneProperties->Get(i)->ToString();
		Local<Value> phoneValue = phoneObject->Get(phoneKey);

		AttributeSubKind::Type subKind = AttributeSubKind::Other;
		QString phoneStringValue = titanium::V8ValueToQString(phoneKey);

		if(phoneStringValue == "home") {
			subKind = AttributeSubKind::Home;
		} else
		if(phoneStringValue == "work") {
			subKind = AttributeSubKind::Work;
		} else
		if(phoneStringValue == "mobile") {
			subKind = AttributeSubKind::PhoneMobile;
		}

		if(!phoneValue->IsArray()) return;

		Local<Array> phones = Local<Array>::Cast(phoneValue);
		for(int i = 0, len = phones->Length(); i < len; i++)
		{
			Local<Value> currentMessage = phones->Get(Number::New(i));
			if(!currentMessage->IsString()) return;

			obj->setContactDetails(AttributeKind::Phone, subKind, currentMessage);
		}
	}
}
void ContactsPersonProxy::_setPrefix(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NamePrefix, value);
}
void ContactsPersonProxy::_setRecordId(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setRelatedNames(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}
void ContactsPersonProxy::_setSuffix(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    obj->setContactDetails(AttributeKind::Name, AttributeSubKind::NameSuffix, value);
}
void ContactsPersonProxy::_setUrl(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    // not supported
}

// GETTERS

Handle<Value> ContactsPersonProxy::_getAddress(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    QList<ContactPostalAddress> array = obj->getFullContact().postalAddresses();
    Handle<Array> ar = Array::New(array.length());
    for(int i = 0, len = array.length(); i < len; i++)
    {
        ContactPostalAddress address = array.at(i);
        Handle<Object> addressObject = Object::New();

        addressObject->Set(String::New("label"), String::New(address.label().toUtf8().constData()));
        addressObject->Set(String::New("line1"), String::New(address.line1().toUtf8().constData()));
        addressObject->Set(String::New("line2"), String::New(address.line2().toUtf8().constData()));
        addressObject->Set(String::New("city"), String::New(address.city().toUtf8().constData()));
        addressObject->Set(String::New("region"), String::New(address.region().toUtf8().constData()));
        addressObject->Set(String::New("country"), String::New(address.country().toUtf8().constData()));
        addressObject->Set(String::New("postalCode"), String::New(address.postalCode().toUtf8().constData()));
        addressObject->Set(String::New("latitude"), Number::New(address.latitude()));
        addressObject->Set(String::New("longitude"), Number::New(address.longitude()));
        ar->Set(i, addressObject);
    }

    return ar;
}
Handle<Value> ContactsPersonProxy::_getBirthday(void* userContext) {
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::DateBirthday);
}
Handle<Value> ContactsPersonProxy::_getCreated(void* userContext) {
    return String::New("not supported");
}
Handle<Value> ContactsPersonProxy::_getDepartment(void* userContext) {
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::GroupDepartment);
}
Handle<Value> ContactsPersonProxy::_getEmail(void* userContext) {
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    QList<ContactAttribute> emails = obj->getFullContact().emails();
    Handle <Array> emailArray = Array::New(emails.length());

    for (int i = 0, len = emails.length(); i < len; i++)
    {
        ContactAttribute email = emails.at(i);
        QString kind;
        Handle <Object> jsObject = Object::New();
        switch (email.subKind()) {
        case AttributeSubKind::Other:
            kind = "other";
            break;
        case AttributeSubKind::Home:
            kind = "home";
            break;
        case AttributeSubKind::Work:
            kind = "work";
            break;
        case AttributeSubKind::NameAlias:
            kind = "nameAlias";
            break;
        case AttributeSubKind::Personal:
            kind = "personal";
            break;
        default:
            kind = "other";
            break;
        }
        jsObject->Set(
                String::New(kind.toUtf8().constData()),
                String::New(email.value().toUtf8().constData())
        );
        emailArray->Set(i, jsObject);
    }

    return emailArray;
}
Handle<Value> ContactsPersonProxy::_getFirstName(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameGiven);
}
Handle<Value> ContactsPersonProxy::_getFirstPhonetic(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NamePhoneticGiven);
}
Handle<Value> ContactsPersonProxy::_getFullName(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameDisplayName);
}
Handle<Value> ContactsPersonProxy::_getId(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return Number::New(obj->contact_.id());
}
Handle<Value> ContactsPersonProxy::_getImage(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    ContactPhoto photo = obj->getFullContact().primaryPhoto();

    if(photo.isValid()) {

        TiBlobObject *blob = TiBlobObject::createBlob(obj->getNativeObjectFactory());
        Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(obj->getValue());
        Local<Object> proxy = templ->NewInstance();
        blob->setValue(proxy);
        TiObject::setTiObjectToJsObject(proxy, blob);

        QFile filePath(photo.largePhoto());
        blob->setData(filePath.readAll(), "");

        blob->release();
        HandleScope scope;
        return scope.Close(proxy);
    }

    return False();
}
Handle<Value> ContactsPersonProxy::_getInstantMessage(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    QList<ContactAttribute> array = obj->getFullContact().filteredAttributes(AttributeKind::InstantMessaging);

    Handle<Array> ar = Array::New(array.length());
    for(int i = 0, len = array.length(); i < len; i++) {
        QString type;
        Handle<Object> jsObject = Object::New();
        switch(array.at(i).subKind())
        {
        case AttributeSubKind::InstantMessagingAim: type = "aim"; break;
        case AttributeSubKind::InstantMessagingAliwangwang: type = "aliwangwang"; break;
        case AttributeSubKind::InstantMessagingBbmPin: type = "bbmPin"; break;
        case AttributeSubKind::InstantMessagingGoogleTalk: type = "googleTalk"; break;
        case AttributeSubKind::InstantMessagingIcq: type = "icq"; break;
        case AttributeSubKind::InstantMessagingIrc: type = "irc"; break;
        case AttributeSubKind::InstantMessagingJabber: type = "jabber"; break;
        case AttributeSubKind::InstantMessagingMsLcs: type = "msLcs"; break;
        case AttributeSubKind::InstantMessagingMsn: type = "msn"; break;
        case AttributeSubKind::InstantMessagingQq: type = "qq"; break;
        case AttributeSubKind::InstantMessagingSametime: type = "sametime"; break;
        case AttributeSubKind::InstantMessagingSkype: type = "skype"; break;
        case AttributeSubKind::InstantMessagingYahooMessenger: type = "yahooMessenger"; break;
        case AttributeSubKind::InstantMessagingYahooMessengerJapan: type = "yahooMessenger"; break;
        default: type = "other"; break;
        }
        jsObject->Set(String::New(type.toUtf8().constData()), String::New(array.at(i).value().toUtf8().constData()));
        ar->Set(i, jsObject);
    }
    return ar;
}
Handle<Value> ContactsPersonProxy::_getJobTitle(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::Title);
}
Handle<Value> ContactsPersonProxy::_getKind(void* userContext)
{
    return String::New("not supported");
}
Handle<Value> ContactsPersonProxy::_getLastName(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameSurname);
}
Handle<Value> ContactsPersonProxy::_getLastPhonetic(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NamePhoneticSurname);
}
Handle<Value> ContactsPersonProxy::_getMiddleName(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameMiddle);
}
Handle<Value> ContactsPersonProxy::_getMiddlePhonetic(void* userContext)
{
    return String::New("not supported");
}
Handle<Value> ContactsPersonProxy::_getModified(void* userContext)
{
    return String::New("not supported");
}
Handle<Value> ContactsPersonProxy::_getNickname(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameNickname);
}
Handle<Value> ContactsPersonProxy::_getNote(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getKind(AttributeKind::Note);
}
Handle<Value> ContactsPersonProxy::_getOrganization(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::OrganizationAffiliationName);
}
Handle<Value> ContactsPersonProxy::_getPhone(void* userContext) {
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    QList<ContactAttribute> array = obj->getFullContact().filteredAttributes(AttributeKind::Phone);

    Handle<Array> ar = Array::New(array.length());
    for(int i = 0, len = array.length(); i < len; i++) {
        QString type;
        Handle<Object> jsObject = Object::New();
        switch(array.at(i).subKind())
        {
        case AttributeSubKind::Other: type = "other"; break;
        case AttributeSubKind::Home: type = "home"; break;
        case AttributeSubKind::Work: type = "work"; break;
        case AttributeSubKind::PhoneMobile: type = "mobile"; break;
        default: type = "other"; break;
        }
        jsObject->Set(String::New(type.toUtf8().constData()), String::New(array.at(i).value().toUtf8().constData()));
        ar->Set(i, jsObject);
    }
    return ar;
}
Handle<Value> ContactsPersonProxy::_getPrefix(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NamePrefix);
}
Handle<Value> ContactsPersonProxy::_getRecordId(void* userContext)
{
    // not supperted
    return ContactsPersonProxy::_getId(userContext);
}
Handle<Value> ContactsPersonProxy::_getRelatedNames(void* userContext)
{
    return String::New("not supported");
}
Handle<Value> ContactsPersonProxy::_getSuffix(void* userContext)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
    return obj->getSubkind(AttributeSubKind::NameSuffix);
}
Handle<Value> ContactsPersonProxy::_getUrl(void* userContext)
{
    // not supperted
    return String::New("not supported");
}
