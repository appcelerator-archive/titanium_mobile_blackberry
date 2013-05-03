/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIANIMATION_H_
#define TIUIANIMATION_H_

#include "TiProxy.h"

class TiUIAnimation : public TiProxy
{
public:
    static TiUIAnimation* createAnimation(NativeObjectFactory* objectFactory);

//    void setData(const QByteArray& data, const QString& mimeType);

protected:
    virtual ~TiUIAnimation();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIAnimation();
    TiUIAnimation(const TiUIAnimation&);
    TiUIAnimation& operator=(const TiUIAnimation&);
};

#endif TIUIANIMATION_H_
