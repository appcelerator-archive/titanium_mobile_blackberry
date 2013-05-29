/*
 * ContactsContactProxy.cpp
 *
 *  Created on: May 23, 2013
 *      Author: penrique
 */

#include "ContactsPersonProxy.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetObject.h"
#include "V8Utils.h"
#include "TiBlobObject.h"
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/ContactBuilder>
#include <bb/pim/contacts/ContactPhoto>
#include <bb/pim/contacts/ContactAttributeBuilder>
#include <QFile>
#include <iostream>
#include <QtAlgorithms>

using namespace bb::pim::contacts;

ContactsPersonProxy::ContactsPersonProxy() :
		TiProxy()
{
	ContactService service;
	ContactBuilder builder;
	contact_ = service.createContact(builder, false);
}
ContactsPersonProxy::ContactsPersonProxy(Contact contact) :
		TiProxy()
{
	contact_ = contact;
}
ContactsPersonProxy::~ContactsPersonProxy()
{
	// TODO Auto-generated destructor stub
}
ContactsPersonProxy* ContactsPersonProxy::createPerson(
		NativeObjectFactory* objectFactory) {
	ContactsPersonProxy* obj = new ContactsPersonProxy;
	obj->setNativeObjectFactory(objectFactory);
	obj->initializeTiObject(NULL);
	return obj;

}
void ContactsPersonProxy::onCreateStaticMembers() {
	TiProxy::onCreateStaticMembers();

	createSettersAndGetters("address", NULL, _getAddress);
	createSettersAndGetters("birthday", NULL, _getBirthday);
	createSettersAndGetters("created", NULL, _getCreated);
	createSettersAndGetters("department", NULL, _getDepartment);
	createSettersAndGetters("email", NULL, _getEmail);
	createSettersAndGetters("firstName", _setFirstName, _getFirstName);
	createSettersAndGetters("fullName", NULL, _getFullName);
	createSettersAndGetters("firstPhonetic", NULL, _getFirstPhonetic);
	createSettersAndGetters("id", NULL, _getId);
	createSettersAndGetters("image", NULL, _getImage);
	createSettersAndGetters("instantMessage", NULL, _getInstantMessage);
	createSettersAndGetters("jobTitle", NULL, _getJobTitle);
	createSettersAndGetters("kind", NULL, _getKind);
	createSettersAndGetters("lastName", _setLastName, _getLastName);
	createSettersAndGetters("lastPhonetic", NULL, _getLastPhonetic);
	createSettersAndGetters("middleName", NULL, _getMiddleName);
	createSettersAndGetters("middlePhonetic", NULL, _getMiddlePhonetic);
	createSettersAndGetters("modified", NULL, _getModified);
	createSettersAndGetters("nickname", NULL, _getNickname);
	createSettersAndGetters("note", NULL, _getNote);
	createSettersAndGetters("organization", NULL, _getOrganization);
	createSettersAndGetters("phone", NULL, _getPhone);
	createSettersAndGetters("prefix", NULL, _getPrefix);
	createSettersAndGetters("recordId", NULL, _getRecordId);
	createSettersAndGetters("relatedNames", NULL, _getRelatedNames);
	createSettersAndGetters("suffix", NULL, _getSuffix);
	createSettersAndGetters("url", NULL, _getUrl);

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
	return Undefined();
}

Handle<Value> ContactsPersonProxy::getKind(AttributeKind::Type kind)
{
	QList<ContactAttribute> array =	getFullContact().attributes();

	for (int i = 0, len = array.length(); i < len; i++) {
		ContactAttribute attr = array.at(i);
		if (attr.kind() == kind) {
			QString name = attr.value();
			return String::New(name.toUtf8().constData());
		}
	}
	return Undefined();
}

void ContactsPersonProxy::_setFirstName(void* userContext, Handle<Value> value)
{
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	QString val = titanium::V8ValueToQString(value);

	ContactBuilder builder = obj->contact_.edit();

	ContactAttributeBuilder attribute;
	attribute.setKind(AttributeKind::Name);
	attribute.setSubKind(AttributeSubKind::NameGiven);
	attribute.setValue(val);

	builder.addAttribute(attribute);

	ContactService().updateContact(obj->contact_);
}

void ContactsPersonProxy::_setLastName(void* userContext, Handle<Value> value)
{
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	QString val = titanium::V8ValueToQString(value);

	ContactBuilder builder = obj->contact_.edit();

	ContactAttributeBuilder attribute;
	attribute.setKind(AttributeKind::Name);
	attribute.setSubKind(AttributeSubKind::NameSurname);
	attribute.setValue(val);
	builder.addAttribute(attribute);

	ContactService service;
	service.updateContact(obj->contact_);
}
Handle<Value> ContactsPersonProxy::_getAddress(void* userContext)
{
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	ContactPostalAddress address =
			obj->getFullContact().postalAddresses()[0];
	QString add = address.label();
	return String::New(add.toUtf8().constData());
}
Handle<Value> ContactsPersonProxy::_getBirthday(void* userContext) {
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	return obj->getSubkind(AttributeSubKind::DateBirthday);
}
Handle<Value> ContactsPersonProxy::_getCreated(void* userContext) {
	return Undefined();
}
Handle<Value> ContactsPersonProxy::_getDepartment(void* userContext) {
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	return obj->getSubkind(AttributeSubKind::GroupDepartment);
}
Handle<Value> ContactsPersonProxy::_getEmail(void* userContext) {
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

	QList<ContactAttribute> emails =
			obj->getFullContact().emails();
	Handle < Array > emailArray = Array::New(emails.length());
	for (int i = 0, len = emails.length(); i < len; i++) {
		ContactAttribute email = emails.at(i);
		QString kind;
		Handle < Object > jsObject = Object::New();
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
		jsObject->Set(String::New(kind.toUtf8().constData()),
				String::New(email.value().toUtf8().constData()));
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

	return Boolean::New(false);
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
	// Not yet implemented
	return Undefined();
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
	// Not supported
	return Undefined();
}
Handle<Value> ContactsPersonProxy::_getModified(void* userContext)
{
	// Not supported
	return Undefined();
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
	return Undefined();
}
Handle<Value> ContactsPersonProxy::_getRelatedNames(void* userContext)
{
	return ContactsPersonProxy::_getId(userContext);
}
Handle<Value> ContactsPersonProxy::_getSuffix(void* userContext)
{
	ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;
	return obj->getSubkind(AttributeSubKind::NameSuffix);
}
Handle<Value> ContactsPersonProxy::_getUrl(void* userContext)
{
	// not supperted
	return Undefined();
}
