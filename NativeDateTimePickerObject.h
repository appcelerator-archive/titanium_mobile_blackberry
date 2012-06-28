/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEDATETIMEPICKER_H_
#define NATIVEDATETIMEPICKER_H_

#include "NativeControlObject.h"

/*
 * NativeDateTimePicker
 *
 * UI: DateTimePicker control
 */

namespace bb
{
namespace cascades
{
class DateTimePicker;
};
};


class NativeDateTimePickerObject : public NativeControlObject
{
public:
    static NativeDateTimePickerObject* createDateTimePicker();
    virtual int getObjectType() const;
    virtual int setValue(TiObject* obj);
    virtual int setType(TiObject* obj);
    virtual int setMinDate(TiObject* obj);
    virtual int setMaxDate(TiObject* obj);
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual void completeInitialization();
    virtual NAHANDLE getNativeHandle() const;

protected:
    virtual ~NativeDateTimePickerObject();

private:
    explicit NativeDateTimePickerObject();
    //Not copy-constructible; Not assignable.
    NativeDateTimePickerObject(const NativeDateTimePickerObject& obj);
    NativeDateTimePickerObject& operator=(const NativeDateTimePickerObject& obj);

    bb::cascades::DateTimePicker* dateTimePicker_;
    float left_;
    float top_;
};

//Event handler for DateTimePicker object
class DateTimePickerEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit DateTimePickerEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~DateTimePickerEventHandler() {}

public slots:
    void setValue(QDateTime value)
    {
        eventContainer_->setDataProperty("value", value.toString().toUtf8().constData());
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    DateTimePickerEventHandler(const DateTimePickerEventHandler& eHandler);
    DateTimePickerEventHandler& operator=(const DateTimePickerEventHandler& eHandler);
};

#endif /* NATIVEDATETIMEPICKER_H_ */
