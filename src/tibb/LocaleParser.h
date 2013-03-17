/*
 * LocaleParser.h
 *
 *  Created on: Mar 15, 2013
 *      Author: penrique
 */

#ifndef LOCALEPARSER_H_
#define LOCALEPARSER_H_

#include <QLocale>
#include <QObject>
#include <QMap>
#include <bb/data/XmlDataAccess>
/*
namespace bb
{
namespace data
{
class XmlDataAccess;
}
}
*/
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
