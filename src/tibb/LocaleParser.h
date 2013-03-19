/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef LOCALEPARSER_H_
#define LOCALEPARSER_H_

#include <QLocale>
#include <QObject>
#include <QMap>
#include <bb/data/XmlDataAccess>

class LocaleParser {
public:
	LocaleParser();
	virtual ~LocaleParser();
	static LocaleParser *sharedInstance();
	QString getString(QString value1, QString value2);
	QString getLocaleLanguage();
	QString getLocaleCountry();
	QString getLocale();
	void setLocale(QString value);
private:
	QMap<QString, QString> stringsMap_;
	QString localeLanguage_;
	QString localeCountry_;
	QString locale_;
};

#endif /* LOCALEPARSER_H_ */
