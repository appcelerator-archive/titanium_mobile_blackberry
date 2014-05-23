/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "LocaleParser.h"

static LocaleParser* _instance;

LocaleParser::LocaleParser() {
	setLocale(QLocale().name());
}

LocaleParser::~LocaleParser() {

}

QString LocaleParser::getString(QString value1, QString value2)
{
	if(stringsMap_.contains(value1))
		return stringsMap_.value(value1);

	if(value2 != "undefined")
		return value2;

	return value1;
}

QString LocaleParser::getLocale() {
	return locale_;
}

QString LocaleParser::getLocaleLanguage() {
	return localeLanguage_;
}

QString LocaleParser::getLocaleCountry() {
	return localeCountry_;
}

void LocaleParser::setLocale(QString value)
{
	stringsMap_.empty();
	localeLanguage_ = QString(value.left(2).toLower());
	localeCountry_ = QString(value.right(2).toUpper());
	locale_ = value;
    QString localeFile = QString("app/native/_private_assets_/i18n/");
    		localeFile.append(localeLanguage_);
    		localeFile.append("/strings.xml");

    bb::data::XmlDataAccess xda;
    QVariant xml = xda.load(localeFile, "resources/string");
    if(xda.hasError()) return;
    // TODO: Handle error

    QList<QVariant> list = xml.toList();
    for(int i = 0; i < list.length(); i++) {
    	QVariant rawItem = list.at(i);
    	QVariantMap item = rawItem.toMap();
    	stringsMap_.insert(item.value("name").toString(), item.value(".data").toString());
    }

}

LocaleParser *LocaleParser::sharedInstance()
{
	if(_instance == NULL)
		_instance = new LocaleParser();
	return _instance;
}
