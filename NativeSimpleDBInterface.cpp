/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeSimpleDBInterface.h"

#include "NativeException.h"
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

    if (!db_.open())
    {
        throw NativeException(QString(Native::Msg::Failed_to_open_database).arg(dbPath_, db_.lastError().text()).toStdString());
    }

    QSqlQuery query(db_);
    query.exec("CREATE TABLE IF NOT EXISTS " + table_ + " (simpleKey VARCHAR(255) PRIMARY KEY, simpleValue TEXT)");
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Create_table_failed).arg(dbPath_, table_, sqlError.text()).toStdString());
    }
}

string NativeSimpleDBInterface::get(const string& key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("SELECT simpleValue FROM " + table_ + " WHERE simpleKey = :simpleKey");
    QString keyQString = QString::fromUtf8(key.c_str());
    query.bindValue(":simpleKey", keyQString);
    query.exec();
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Failed_to_get_key).arg(dbPath_, keyQString, sqlError.text()).toStdString());
    }

    if (query.next())
    {
        return query.value(0).toString().toStdString();
    }
    return "";
}

void NativeSimpleDBInterface::set(const string& key, const string& value)
{
    open();
    QSqlQuery query(db_);
    query.prepare("INSERT INTO " + table_ + " (simpleKey, simpleValue) VALUES (:simpleKey, :simpleValue)");
    QString keyQString = QString::fromUtf8(key.c_str());
    query.bindValue(":simpleKey", keyQString);
    query.bindValue(":simpleValue", QString::fromUtf8(value.c_str()));
    query.exec();
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Failed_to_set_key).arg(dbPath_, keyQString, sqlError.text()).toStdString());
    }
}

bool NativeSimpleDBInterface::contains(const string& key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("SELECT simpleValue FROM " + table_ + " WHERE simpleKey = :simpleKey");
    QString keyQString = QString::fromUtf8(key.c_str());
    query.bindValue(":simpleKey", keyQString);
    query.exec();
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Failed_to_check_for_key).arg(dbPath_, keyQString, sqlError.text()).toStdString());
    }

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
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Failed_to_get_keys).arg(dbPath_, sqlError.text()).toStdString());
    }

    while (query.next())
    {
        ret.push_back(query.value(0).toString().toStdString());
    }
    return ret;
}

void NativeSimpleDBInterface::remove(const string& key)
{
    open();
    QSqlQuery query(db_);
    query.prepare("DELETE FROM " + table_ + " WHERE simpleKey = :simpleKey");
    QString keyQString = QString::fromUtf8(key.c_str());
    query.bindValue(":simpleKey", keyQString);
    query.exec();
    QSqlError sqlError = query.lastError();
    if (sqlError.isValid())
    {
        throw NativeException(QString(Native::Msg::Failed_to_remove_key).arg(dbPath_, keyQString, sqlError.text()).toStdString());
    }
}
