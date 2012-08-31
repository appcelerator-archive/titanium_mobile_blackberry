/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETEXTFIELDOBJECT_H_
#define NATIVETEXTFIELDOBJECT_H_

#include "NativeAbstractTextControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class TextField;
}
}


class NativeTextFieldObject : public NativeAbstractTextControlObject
{
public:
    static NativeTextFieldObject* createTextField(TiObject* tiObject);
    virtual int getObjectType() const;
    virtual int initialize();
    virtual int setHintText(TiObject* obj);
    virtual int setValue(TiObject* obj);
    void updateValue(QString value);

protected:
    virtual ~NativeTextFieldObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeTextFieldObject(TiObject* tiObject);
    //this class is neither copy-constructible nor assignable
    NativeTextFieldObject(const NativeTextFieldObject& textField);
    NativeTextFieldObject& operator=(const NativeTextFieldObject& textField);

    bb::cascades::TextField* textField_;
};

//Event handler for textField object
class TextFieldEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit TextFieldEventHandler(TiEventContainer* eventContainer, NativeTextFieldObject* owner)
        : eventContainer_(eventContainer)
        , owner_(owner)
    {
        Q_ASSERT(owner_);
        owner_->addRef();
    }
    virtual ~TextFieldEventHandler()
    {
        Q_ASSERT(owner_);
        owner_->release();
    }

public slots:
    void textChanging(QString str)
    {
        owner_->updateValue(str);
        eventContainer_->setDataProperty("value", str.toUtf8().constData());
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;
    NativeTextFieldObject* owner_;

    // Disable copy ctor & assignment operator
    TextFieldEventHandler(const TextFieldEventHandler& eHandler);
    TextFieldEventHandler& operator=(const TextFieldEventHandler& eHandler);
};

#endif /* NATIVETEXTFIELDOBJECT_H_ */
