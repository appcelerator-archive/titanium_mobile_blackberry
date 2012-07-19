/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeSimpleDBInterface.h"

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"

#include <QSqlError>
#include <QSqlQuery>

using namespace std;


NativeSimpleDBInterface::NativeSimpleDBInterface(string dbPath, string table)
    : db_(QSqlDatabase::addDatabase("QSQLITE"))
    , dbPath_(QString::fromUtf8(dbPath.c_str()))
    , table_(QString::fromUtf8(table.c_str()))
{
    db_.setDatabaseName(QString::fromUtf8(dbPath.c_str()));
}

NativeSimpleDBInterface::~NativeSimpleDBInterface()
{
    if (db_.isOpen())
    {
        db_.close();
    }
}

void NativeSimpleDBInterface::open()
{
    if (db_.isOpen())
    {
        return;
    }

    db_.open();
    Q_ASSERT(db_.isOpen());
    QSqlQuery query(db_);
    query.exec("CREATE TABLE IF NOT EXISTS " + table_ + " (simpleKey CHAR(10) PRIMARY KEY, simpleValue TEXT)");
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        NativeLoggerObject::getInstance()->log(QString(Native::Msg::Create_table_failed).arg(dbPath_, table_, sqlError.text()));
    }
}

string NativeSimpleDBInterface::get(string key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("SELECT simpleValue FROM " + table_ + " WHERE simpleKey = :simpleKey");
    query.bindValue(":simpleKey", QString::fromUtf8(key.c_str()));
    query.exec();

    if (query.next())
    {
        return query.value(0).toString().toStdString();
    }
    return "";
}

void NativeSimpleDBInterface::set(string key, string value)
{
    open();
    QSqlQuery query(db_);
    query.prepare("INSERT INTO " + table_ + " (simpleKey, simpleValue) VALUES (:simpleKey, :simpleValue)");
    query.bindValue(":simpleKey", QString::fromUtf8(key.c_str()));
    query.bindValue(":simpleValue", QString::fromUtf8(value.c_str()));
    query.exec();
}

bool NativeSimpleDBInterface::contains(string key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("SELECT simpleValue FROM " + table_ + " WHERE simpleKey = :simpleKey");
    query.bindValue(":simpleKey", QString::fromUtf8(key.c_str()));
    query.exec();

    if (query.next())
    {
        return true;
    }
    return false;
}

list<string> NativeSimpleDBInterface::keys()
{
    open();
    list<string> ret;
    QSqlQuery query(db_);
    query.prepare("SELECT simpleKey FROM " + table_);
    query.exec();

    while (query.next())
    {
        ret.push_back(query.value(0).toString().toStdString());
    }
    return ret;
}

void NativeSimpleDBInterface::remove(string key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("DELETE FROM " + table_ + " WHERE simpleKey = :simpleKey");
    query.bindValue(":simpleKey", QString::fromUtf8(key.c_str()));
    query.exec();
}
