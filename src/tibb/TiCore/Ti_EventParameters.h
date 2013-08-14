/*
 * TiEventParameters.h
 *
 *  Created on: Jul 13, 2013
 *      Author: penrique
 */

#ifndef TI_TIEVENTPARAMETERS_H_
#define TI_TIEVENTPARAMETERS_H_

#include "Ti_Proxy.h"
#include <QString>
#include <QMap>
#include <v8.h>

using namespace v8;
namespace Ti
{
class TiEventParameters {
public:
	TiEventParameters();
	virtual ~TiEventParameters();
	void addParam(QString, QString);
	void addParam(QString, int);
	void addParam(QString, double);
	void addParam(QString, TiProxy*);

	static void addParametersToObject(Ti::TiEventParameters*, Handle<Object>);
private:
	QMap<QString, QString> stringMap;
	QMap<QString, double> numberMap;
	QMap<QString, Ti::TiProxy*> proxyMap;

};
}
#endif /* TIEVENTPARAMETERS_H_ */
