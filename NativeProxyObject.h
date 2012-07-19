/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEPROXYOBJECT_H_
#define NATIVEPROXYOBJECT_H_

#include "NativeObject.h"
#include <QHash>

class EventPair :
	public TiBase
{
public:
    EventPair(TiEventContainer* c, QObject* h)
        : container(c)
        , handler(h)
    {}

    ~EventPair()
    {
        delete container;
        delete handler;
    }

    bool isValid()
    {
        return container != NULL && handler != NULL;
    }

    TiEventContainer* container;
    QObject* handler;

private:
    EventPair()
        : container(NULL)
        , handler(NULL)
    {
        /* Default ctor must not be used */
        Q_ASSERT(false);
    }

    EventPair(const EventPair&);
    EventPair& operator=(const EventPair&);
};

class EventPairSmartPtr
{
public:
	EventPairSmartPtr();
	EventPairSmartPtr(const EventPairSmartPtr& eventPtr);
	explicit EventPairSmartPtr(EventPair* eventPtr);
	EventPairSmartPtr(TiEventContainer* c, QObject* h);
	~EventPairSmartPtr();
	const EventPairSmartPtr& operator = (const EventPairSmartPtr& eventPtr);
	EventPair* operator -> () const;
private:
	EventPair* eventPtr_;
};

class NativeProxyObject: public NativeObject
{
public:
    virtual int fireEvent(const char* name, const TiObject* event) const;
	virtual int setEventHandler(const char* eventName, TiEvent* event);
protected:
	NativeProxyObject();
	virtual ~NativeProxyObject();

    QHash<QString, EventPairSmartPtr> events_;

};

#endif /* NATIVEPROXYOBJECT_H_ */
