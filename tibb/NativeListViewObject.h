/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTVIEWOBJECT_H_
#define NATIVELISTVIEWOBJECT_H_

#include "NativeControlObject.h"
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
    static NativeListViewObject* createListView(TiObject* tiObject);
    virtual int getObjectType() const;
    virtual int setData(TiObject* obj);
    virtual int initialize();
    virtual QVariant getListViewElementFromIndex(QVariantList var);
    virtual NAHANDLE getNativeHandle() const;
    virtual int scrollToIndex(int index);

protected:
    virtual ~NativeListViewObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeListViewObject(TiObject* tiObject);
    //Not copy-constructible; Not assignable.
    NativeListViewObject(const NativeListViewObject& obj);
    NativeListViewObject& operator=(const NativeListViewObject& obj);

    bb::cascades::ListView* listView_;
};

class ListViewItemFactory: public bb::cascades::ListItemManager
{
public:
    ListViewItemFactory() {};
    bb::cascades::VisualNode* createItem(bb::cascades::ListView* list, const QString& type);
    void updateItem(bb::cascades::ListView* list, bb::cascades::VisualNode* listItem, const QString& type,
                    const QVariantList& indexPath, const QVariant& data);
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
    void selectionChanged(QVariantList var, bool);
private:
    TiEventContainer* eventContainer_;
    NativeListViewObject* owner_;

    // Disable copy ctor & assignment operator
    ListViewEventHandler(const ListViewEventHandler& eHandler);
    ListViewEventHandler& operator=(const ListViewEventHandler& eHandler);
};

#endif /* NATIVELISTVIEWOBJECT_H_ */
