/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TINETWORK_H_
#define TINETWORK_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiNetwork
 *
 * The top level network module.
 * The Network module is used to access networking related functionality.
 *
 * Titanium.Network namespace
 */
class TiNetwork : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiNetwork();
    virtual void onCreateStaticMembers();

private:
    TiNetwork();
    explicit TiNetwork(NativeObjectFactory* objectFactory);
    TiNetwork(const TiNetwork&);
    TiNetwork& operator=(const TiNetwork&);

    NativeObjectFactory* objectFactory_;
};

#endif /* TINETWORK_H_ */
