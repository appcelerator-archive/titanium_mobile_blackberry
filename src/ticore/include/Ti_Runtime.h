/*
 * TiRuntime.h
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
 */

#ifndef TIRUNTIME_H_
#define TIRUNTIME_H_
#include <bb/cascades/Application>
#include <v8.h>

using namespace v8;

typedef Handle<Object> (*ModuleStartup)();

namespace Ti
{
class TiRuntime {
public:
	TiRuntime(bb::cascades::Application *);
	virtual ~TiRuntime();
	void executeString(QString, QString);
	void registerModule(QString, ModuleStartup);
	static Handle<Value> GC(const Arguments &);
	static Handle<Value> _require(const Arguments &);
	static Handle<Value> _include(const Arguments & args);
	static TiRuntime* Instance();
	int start();
private:
	bb::cascades::Application *app;
	Handle<ObjectTemplate> globalTemplate;
	Handle<Context> globalContext;
};
}
#endif /* TIRUNTIME_H_ */
