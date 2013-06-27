/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETEXTAREAOBJECT_H_
#define NATIVETEXTAREAOBJECT_H_

#include "NativeAbstractTextControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class TextArea;
}
}


class NativeTextAreaObject : public NativeAbstractTextControlObject
{
public:
    static NativeTextAreaObject* createTextArea(TiObject* tiObject);
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual int setHintText(TiObject* obj);
    virtual int setKeyboardType(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setPasswordMask(TiObject* obj);
    virtual void resize(float width, float height);
    void updateValue(QString value);

protected:
    virtual ~NativeTextAreaObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeTextAreaObject(TiObject* tiObject);
    //this class is neither copy-constructible nor assignable
    NativeTextAreaObject(const NativeTextAreaObject& textArea);
    NativeTextAreaObject& operator=(const NativeTextAreaObject& textArea);

    bb::cascades::TextArea* textArea_;
};

//Event handler for textArea object
class TextAreaEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit TextAreaEventHandler(TiEventContainer* eventContainer, NativeTextAreaObject* owner)
        : eventContainer_(eventContainer)
        , owner_(owner)
    {
        Q_ASSERT(owner_);
        owner_->addRef();
    }
    virtual ~TextAreaEventHandler()
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
    NativeTextAreaObject* owner_;

    // Disable copy ctor & assignment operator
    TextAreaEventHandler(const TextAreaEventHandler& eHandler);
    TextAreaEventHandler& operator=(const TextAreaEventHandler& eHandler);
};

#endif /* NATIVEAREAOBJECT_H_ */
