/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEABSTRACTTEXTCONTROLOBJECT_H_
#define NATIVEABSTRACTTEXTCONTROLOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class AbstractTextControl;
}
}

/*
 * NativeAbstractTextControlObject
 *
 * UI: Abstract Text Control
 */

class NativeAbstractTextControlObject : public NativeControlObject
{
public:
    virtual int setText(TiObject* obj);
    virtual int setFont(TiObject* obj);
    virtual int setColor(TiObject* obj);
    virtual int setTextAlign(TiObject* obj);

protected:
    explicit NativeAbstractTextControlObject(TiObject* tiObject);
    virtual ~NativeAbstractTextControlObject();

    virtual bb::cascades::AbstractTextControl* getTextControl() const;
    virtual void setTextControl(bb::cascades::AbstractTextControl* textControl);

private:
    // Disable copy ctor & assignment operator
    NativeAbstractTextControlObject(const NativeAbstractTextControlObject& textControl);
    NativeAbstractTextControlObject& operator=(const NativeAbstractTextControlObject& textControl);

    bb::cascades::AbstractTextControl* textControl_;
};


#endif /* NATIVEABSTRACTTEXTCONTROLOBJECT_H_ */
