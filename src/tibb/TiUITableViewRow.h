/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITABLEVIEWROW_H_
#define TIUITABLEVIEWROW_H_

#include "TiUIBase.h"

class TiUITableViewRow : public TiUIBase {
public:
    static TiUITableViewRow* createTableViewRow(NativeObjectFactory* factory);

protected:
    virtual ~TiUITableViewRow();

    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    explicit TiUITableViewRow();

    // Disable copy ctor & assignment operator
    TiUITableViewRow(const TiUITableViewRow& obj);
    TiUITableViewRow& operator=(const TiUITableViewRow& obj);
};

#endif
