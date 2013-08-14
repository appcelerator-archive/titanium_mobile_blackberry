/*
 * TiTimer.h
 *
 *  Created on: Jul 12, 2013
 *      Author: penrique
 */

#ifndef TI_TITIMER_H_
#define TI_TITIMER_H_

#include <QObject>
#include <QTimer>

#include <v8.h>

using namespace v8;

namespace Ti
{
class TiTimer: public QObject {
	Q_OBJECT;
public:
	TiTimer(int);
	virtual ~TiTimer();
	static Handle<Value> SetTimeout(const Arguments &args);
	void setSingleShot(bool);
	void start();
	void stop();
	QTimer *timer;
	Persistent<Function> callback;
	bool singleShot;
public slots:
	void timeout();
};
}
#endif /* TITIMER_H_ */
