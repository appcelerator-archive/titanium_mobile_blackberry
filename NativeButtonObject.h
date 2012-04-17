/*
 * NativeButtonObject.h
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#ifndef NATIVEBUTTONOBJECT_H_
#define NATIVEBUTTONOBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/Button>

class NativeButtonObject : public NativeControlObject
{
public:
    NativeButtonObject();
    virtual ~NativeButtonObject();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int setLabel(const char* text);
private:
    bb::cascades::Button* button_;
};

#endif /* NATIVEBUTTONOBJECT_H_ */
