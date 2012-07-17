/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEPROXYOBJECT_H_
#define NATIVEPROXYOBJECT_H_

#include "NativeObject.h"
#include "TiEventContainer.h"
#include <QHash>


class EventPair : public TiBase
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

    /* Disable copy ctor and assignment */
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

    EventPairSmartPtr& operator=(const EventPairSmartPtr& eventPtr);
    EventPair* operator->() const;
    EventPair* get() const;

private:
    EventPair* eventPtr_;
};


/*
 * NativeProxyObject
 *
 * This class is the Native representation of the Proxy Module, it implements
 * its functionality to be inherited by subclasses.
 *
 * It inherits directly from the NativeObject abstract class and is the
 * inherited by all NativeObjects for which the associated Ti object is a
 * derivative of Ti.Proxy
 *
 */
class NativeProxyObject: public NativeObject
{
public:
    virtual int fireEvent(const char* name, const TiObject* event) const;
    virtual int removeEventHandler(const char* eventName, int eventId);
    virtual int setEventHandler(const char* eventName, TiEvent* event);

    // Ti event types (tet)
    static const char* tetCHANGE;
    static const char* tetCLICK;

protected:
    NativeProxyObject();
    virtual ~NativeProxyObject();

    int getNextEventId();

    QHash<QString, EventPairSmartPtr> events_;

private:
    // disable copy-ctor and assignment
    NativeProxyObject(const NativeProxyObject&);
    NativeProxyObject& operator=(const NativeProxyObject&);

};

#endif /* NATIVEPROXYOBJECT_H_ */
