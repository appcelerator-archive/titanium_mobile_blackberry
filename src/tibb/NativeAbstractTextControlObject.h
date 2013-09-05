/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEABSTRACTTEXTCONTROLOBJECT_H_
#define NATIVEABSTRACTTEXTCONTROLOBJECT_H_

#include "NativeControlObject.h"
#include <string>

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
    virtual void updateLayout(QRectF rect);
    //virtual void resize(float width, float height);

protected:
    explicit NativeAbstractTextControlObject(TiObject* tiObject, NATIVE_TYPE objType = N_TYPE_UNDEFINED);
    virtual ~NativeAbstractTextControlObject();

    virtual bb::cascades::AbstractTextControl* getTextControl() const;
    virtual void setTextControl(bb::cascades::AbstractTextControl* textControl);

private:
    // Disable copy ctor & assignment operator
    NativeAbstractTextControlObject(const NativeAbstractTextControlObject& textControl);
    NativeAbstractTextControlObject& operator=(const NativeAbstractTextControlObject& textControl);
    float computeValue(std::string value);

    bb::cascades::AbstractTextControl* textControl_;
    double ppi_;
};


#endif /* NATIVEABSTRACTTEXTCONTROLOBJECT_H_ */
