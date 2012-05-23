/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETEXTFIELDOBJECT_H_
#define NATIVETEXTFIELDOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class TextField;
}
}

class TiEventContainer;
class TiCascadesEventHandler;

class NativeTextFieldObject : public NativeControlObject
{
public:
    static NativeTextFieldObject* createTextField();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual int setWidth(TiObject* obj);
    virtual int setHeight(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setTop(TiObject* obj);
    virtual int setHintText(const char* hint);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();
    virtual NAHANDLE getNativeHandle() const;

protected:
    virtual ~NativeTextFieldObject();

private:
    NativeTextFieldObject();
    //this class is neither copy-constructible nor assignable
    NativeTextFieldObject(const NativeTextFieldObject& obj);
    NativeTextFieldObject& operator=(const NativeTextFieldObject& obj);

    bb::cascades::TextField* textField_;
    TiEventContainer* eventFieldChanged_;
    TiCascadesEventHandler* eventHandler_;
    float left_;
    float top_;
};

#endif /* NATIVETEXTFIELDOBJECT_H_ */
