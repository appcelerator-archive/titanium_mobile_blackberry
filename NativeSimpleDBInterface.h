/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESIMPLEDB_H_
#define NATIVESIMPLEDB_H_

#include <QSqlDatabase>
#include <QString>

#include <list>
#include <string>


/*
 * NativeSimpleDBInterface
 *
 * A simple interface to setting and getting persistent key and value string pairs
 */
class NativeSimpleDBInterface
{
public:
    NativeSimpleDBInterface(std::string dbPath, std::string table);
    virtual ~NativeSimpleDBInterface();

    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);

    bool contains(const std::string& key);
    std::list<std::string> keys();
    void remove(const std::string& key);

private:
    // Disable copy ctor & assignment operator
    NativeSimpleDBInterface(const NativeSimpleDBInterface& indicator);
    NativeSimpleDBInterface& operator=(const NativeSimpleDBInterface& indicator);

    void open();

    QSqlDatabase db_;
    QString dbPath_;
    QString table_;
};

#endif /* NATIVESIMPLEDB_H_ */
