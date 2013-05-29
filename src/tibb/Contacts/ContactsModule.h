/*
 * TiContactsObject.h
 *
 *  Created on: May 22, 2013
 *      Author: penrique
 */

#ifndef CONTACTSMODULE_H_
#define CONTACTSMODULE_H_

#include "TiProxy.h"
typedef TiProxy* (*CREATEOBJECTCALLBACK)(NativeObjectFactory*);

class ContactsModule: public TiProxy {
public:
	ContactsModule(NativeObjectFactory* objectFactory);
	virtual ~ContactsModule();
	virtual void onCreateStaticMembers();
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

	static Handle<Value> _createPerson(void*, TiObject*, const Arguments& args);
	static Handle<Value> _getAllPeople(void*, TiObject*, const Arguments& args);

};

#endif /* CONTACTSMODULE_H_ */
