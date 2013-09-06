/*
 * TiValue.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIVALUE_H_
#define TI_TIVALUE_H_

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>

#include <v8.h>

namespace bb
{
namespace cascades
{
class Color;
}
}

using namespace v8;

namespace Ti {
class TiProxy;

class TiValue
{
public:
	TiValue(Handle<Value>);
	TiValue(const Arguments&);
	TiValue();
	virtual ~TiValue();
	QString 			toString();
	bb::cascades::Color toColor();
	Handle<Value> 		toJSValue();
	TiProxy *			toProxy();
	bool 				toBool();
	double 				toNumber();
	QList<Ti::TiValue>	toList();
	QMap<QString, Ti::TiValue> toMap();

	void 				setString(QString);
	void 				setNumber(double);
	void 				setMap(QMap<QString, Ti::TiValue>);
	void 				setBool(bool);
	void 				setProxy(Ti::TiProxy*);
	void 				setList(QList<Ti::TiValue>);
	void				setNull();
	void				setUndefined();

	bool				isList();
	bool				isNull();
	bool				isUndefined();
	bool				isProxy();
	bool				isNumber();
	bool				isMap();
	bool				isString();

private:

	Ti::TiProxy* _proxy;
	QString _string;
	double _number;
	bool _bool;
	Handle<Value> _jsValue;
	QList<Ti::TiValue> _list;
	QMap<QString, Ti::TiValue> _map;
	void setValue(Handle<Value> value);

};

} /* namespace Ti */
#endif /* TIVALUE_H_ */
