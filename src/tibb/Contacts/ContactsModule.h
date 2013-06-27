/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef CONTACTSMODULE_H_
#define CONTACTSMODULE_H_

#include "TiProxy.h"
typedef TiProxy* (*CREATEOBJECTCALLBACK)(NativeObjectFactory*);

class ContactsModule: public TiProxy {
public:
    ContactsModule();
    virtual ~ContactsModule();
    virtual void onCreateStaticMembers();
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

    static Handle<Value> _getPeopleWithName(void*, TiObject*, const Arguments& args);
    static Handle<Value> _createPerson(void*, TiObject*, const Arguments& args);
    static Handle<Value> _getAllPeople(void*, TiObject*, const Arguments& args);
    static Handle<Value> _getPersonByID(void*, TiObject*, const Arguments& args);
    static Handle<Value> _removePerson(void*, TiObject*, const Arguments& args);

};

#endif /* CONTACTSMODULE_H_ */
