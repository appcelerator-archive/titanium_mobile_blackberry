/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETABLEVIEWOBJECT_H_
#define NATIVETABLEVIEWOBJECT_H_

#include "NativeControlObject.h"
#include <QObject>

/*
 * NativeTableView
 *
 * UI: TableView control
 */

namespace bb
{
namespace cascades
{
class ListView;
class VisualNode;
};
};

#include <bb/cascades/ListItemProvider>
#include <bb/cascades/ListItemTypeMapper>
#include <bb/cascades/StandardListItem>

class TiEventContainer;
class TiCascadesEventHandler;
class TableViewEventHandler;

class NativeTableViewObject : public NativeControlObject
{
public:
    static NativeTableViewObject* createTableView(TiObject* tiObject);
    virtual NATIVE_TYPE getObjectType() const;
    virtual int setData(TiObject* obj);
    virtual int initialize();
    virtual QVariant getTableViewElementFromIndex(QVariantList var);
    virtual NAHANDLE getNativeHandle() const;
    virtual int scrollToIndex(int index);

protected:
    virtual ~NativeTableViewObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeTableViewObject(TiObject* tiObject);
    //Not copy-constructible; Not assignable.
    NativeTableViewObject(const NativeTableViewObject& obj);
    NativeTableViewObject& operator=(const NativeTableViewObject& obj);
    TiObject* createRowObject(v8::Local<v8::Object> item);
    bb::cascades::ListView* tableView_;
};

class TableViewRowFactory : public bb::cascades::ListItemProvider,
                            public bb::cascades::ListItemTypeMapper
{
public:
    TableViewRowFactory(NativeTableViewObject* tableView)
      : tableView_(tableView) {
    }

    bb::cascades::VisualNode* createItem(bb::cascades::ListView* list, const QString& type);
    void updateItem(bb::cascades::ListView* list, bb::cascades::VisualNode* listItem, const QString& type,
                    const QVariantList& indexPath, const QVariant& data);

    QString itemType(const QVariant &data, const QVariantList &indexPat);

private:
    NativeTableViewObject* tableView_;
};

//Event handler for button object
class TableViewEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit TableViewEventHandler(TiEventContainer* eventContainer, NativeTableViewObject* owner)
    {
        eventContainer_ = eventContainer;
        owner_ = owner;
    }
    virtual ~TableViewEventHandler() {}

public slots:
    void triggered(QVariantList var);

private:
    TiEventContainer* eventContainer_;
    NativeTableViewObject* owner_;

    // Disable copy ctor & assignment operator
    TableViewEventHandler(const TableViewEventHandler& eHandler);
    TableViewEventHandler& operator=(const TableViewEventHandler& eHandler);
};

#endif /* NATIVETABLEVIEWOBJECT_H_ */
