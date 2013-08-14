/*
 * TiProperty.h
 *
 *  Created on: Jul 11, 2013
 *      Author: penrique
 */

#ifndef TI_TIPROPERTY_H_
#define TI_TIPROPERTY_H_

#include <v8.h>
#include <QString>

namespace Ti
{
class TiProxy;
class TiValue;
}

using namespace v8;

typedef void (*PROPERTY_SETTER)(Ti::TiProxy*, Ti::TiValue);
typedef Ti::TiValue (*PROPERTY_GETTER)(Ti::TiProxy*);
typedef Ti::TiValue (*PROPERTY_FUNCTION)(Ti::TiProxy*, Ti::TiValue);


namespace Ti
{
class TiProperty
{
public:
	virtual ~TiProperty();
	TiProperty(QString _name);
	static void createFunction(Ti::TiProxy* _proxy, QString _name, PROPERTY_FUNCTION _callback);
	static void createSetter(Ti::TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback);
	static void createGetter(Ti::TiProxy* _proxy, QString _name, PROPERTY_GETTER _getterCallback);
	static void createProperty(Ti::TiProxy* _proxy, QString _name, PROPERTY_SETTER _setterCallback,  PROPERTY_GETTER _getterCallback);

	static Handle<Value> onInvoke(const Arguments& args);
	Handle<Value> getValue();
	Handle<Value> setValue(Handle<Value>);

	PROPERTY_FUNCTION callback;
	PROPERTY_SETTER setterCallback;
	PROPERTY_GETTER getterCallback;
	Persistent<Function> value;
	bool isFunction;
	Ti::TiProxy* proxy;
	QString name;
};
}
#endif /* TIPROPERTY_H_ */
