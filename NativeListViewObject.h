/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTVIEWOBJECT_H_
#define NATIVELISTVIEWOBJECT_H_

#include "NativeControlObject.h"
#include "TiObject.h"
#include <QtCore/qobject.h>

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
class VisualNode;
};
};

#include <bb/cascades/ListItemManager>
#include <bb/cascades/StandardListItem>

class TiEventContainer;
class TiCascadesEventHandler;
class ListViewEventHandler;

class NativeListViewObject : public NativeControlObject
{
public:
    static NativeListViewObject* createListView();
    virtual int getObjectType() const;
    virtual int setTop(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setWidth(TiObject* obj);
    virtual int setData(TiObject* obj);
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual QVariant getListViewElementFromIndex(QVariantList var);
    virtual NAHANDLE getNativeHandle() const;
    virtual int scrollToIndex(int index);

protected:
    virtual ~NativeListViewObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeListViewObject();
    //Not copy-constructible; Not assignable.
    NativeListViewObject(const NativeListViewObject& obj);
    NativeListViewObject& operator=(const NativeListViewObject& obj);

    bb::cascades::ListView* listView_;
    float left_;
    float top_;
};

class ListViewItemFactory: public bb::cascades::ListItemManager
{
public:
    ListViewItemFactory() {};

    bb::cascades::VisualNode* createItem(bb::cascades::ListView* list, const QString& type)
    {
        bb::cascades::StandardListItem* item = new bb::cascades::StandardListItem();
        return item;
    }

    void updateItem(bb::cascades::ListView* list, bb::cascades::VisualNode* listItem, const QString& type,
                    const QVariantList& indexPath, const QVariant& data)
    {
        // Trying to parse the title from v8 object
        if (data.canConvert<v8ToNativeBridge*>())
        {
            v8ToNativeBridge* v8Bridge = data.value<v8ToNativeBridge*>();
            Persistent<Value> propValue = v8Bridge->getValue();
            if (propValue->IsObject())
            {
                Local<Array> propAr = propValue->ToObject()->GetPropertyNames();
                uint32_t arLenght = propAr->Length();
                for (uint32_t j = 0; j < arLenght; ++j)
                {
                    Handle<String> propString = Handle<String>::Cast(propAr->Get(j));
                    String::Utf8Value propNameUTF(propString);
                    if (strcmp(*propNameUTF, "title") == 0)
                    {
                        Local<Value> titleValue = propValue->ToObject()->Get(propString);
                        Local<String> valueStr = titleValue->ToString();
                        String::Utf8Value valueUTF(valueStr);
                        ((bb::cascades::StandardListItem*)listItem)->setTitleText(*valueUTF);
                        break;
                    }
                }
            }
        }
    }
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
        QString strIndex = var[0].toString().toStdString().c_str();
        eventContainer_->setDataProperty("index", var[0].toString().toStdString().c_str());
        QVariant property;
        Persistent<Value> propValue;
        if (owner_)
        {
            property = owner_->getListViewElementFromIndex(var);
            if (property.canConvert<v8ToNativeBridge*>())
            {
                v8ToNativeBridge* v8Bridge = property.value<v8ToNativeBridge*>();
                propValue = v8Bridge->getValue();
            }
        }
        eventContainer_->setDataModelProperty("rowData", propValue);
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
