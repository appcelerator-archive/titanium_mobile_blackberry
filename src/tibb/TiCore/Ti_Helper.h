/*
 * TiHelper.h
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
 */

#ifndef TI_TIHELPER_H_
#define TI_TIHELPER_H_

#include <v8.h>
#include <QString>
#include <bb/cascades/Color>

using namespace v8;

namespace Ti
{
class TiHelper {
public:
	TiHelper();
	virtual ~TiHelper();
	static void Log(QString);
	static Handle<Value> Log(Handle<Value>);
	static Handle<Value> Log(const Arguments &args);
	static Handle<Value> Alert(const Arguments &args);
	static QString QStringFromValue(Handle<Value>);
	static float FloatFromValue(Handle<Value>);
	static char* QStringToChar(QString);
	static bb::cascades::Color ColorFromObject(Handle<Value> obj);

	static Handle<Value> ValueFromQString(QString);
};
}
#endif /* TIHELPER_H_ */
