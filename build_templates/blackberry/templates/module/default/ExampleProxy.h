/*
 * TestProxy.h
 *
 *  Created on: Sep 6, 2013
 *      Author: penrique
 */

#ifndef NATIVE___MODULE_NAME___TESTPROXY_H_
#define NATIVE___MODULE_NAME___TESTPROXY_H_

#include "TiCore.h"

class ExampleProxy : Ti::TiProxy
{
public:
	CREATE_PROXY(ExampleProxy)
	ExampleProxy(const char*);
	virtual ~ExampleProxy();
};

#endif /* NATIVE___MODULE_NAME___TESTPROXY_H_ */
