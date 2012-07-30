/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTVIEWOBJECT_H_
#define NATIVELISTVIEWOBJECT_H_

#include "NativeControlObject.h"

/*
 * NativeListView
 *
 * UI: ListView control
 */

namespace bb
{
namespace cascades
{
class ListView;
};
};


class NativeListViewObject : public NativeControlObject
{
public:
    static NativeListViewObject* createListView();
    virtual int getObjectType() const;
    virtual int setData(TiObject* obj);
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual QString getListViewElementFromIndex(QVariantList var);
    virtual NAHANDLE getNativeHandle() const;
    virtual int scrollToIndex(int index);

protected:
    virtual ~NativeListViewObject();

private:
    explicit NativeListViewObject();
    //Not copy-constructible; Not assignable.
    NativeListViewObject(const NativeListViewObject& obj);
    NativeListViewObject& operator=(const NativeListViewObject& obj);

    bb::cascades::ListView* listView_;
    float left_;
    float top_;
};

//Event handler for button object
class ListViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ListViewEventHandler(TiEventContainer* eventContainer, NativeListViewObject* owner)
    {
        eventContainer_ = eventContainer;
        owner_ = owner;
    }
    virtual ~ListViewEventHandler() {}

public slots:
    void selectionChanged(QVariantList var, bool)
    {
        eventContainer_->setDataProperty("index", var[0].toString().toStdString().c_str());
        QString str;
        if (owner_)
        {
            str = owner_->getListViewElementFromIndex(var);
        }
        //TODO later we may need to implement all complex data types instead of using just names, but for now it is fine
        eventContainer_->setComplexDataProperty("rowData", "title", str.toUtf8().constData());
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;
    NativeListViewObject* owner_;

    // Disable copy ctor & assignment operator
    ListViewEventHandler(const ListViewEventHandler& eHandler);
    ListViewEventHandler& operator=(const ListViewEventHandler& eHandler);
};

#endif /* NATIVELISTVIEWOBJECT_H_ */
