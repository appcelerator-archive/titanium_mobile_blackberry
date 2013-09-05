
//
// ==================================================================================================
// Proxy Definition

#ifndef EXAMPLE_PROXY_H
#define EXAMPLE_PROXY_H

#include "TiCore.h"

class ExampleProxy: public Ti::TiProxy {
public:
	// **Required** Macro
	CREATE_PROXY(ExampleProxy)

	// **Required** Parameter `const char*`
	ExampleProxy(const char*);
	virtual ~ExampleProxy();

	// Setter prop example
	void setExampleProperty(Ti::TiValue);
	EXPOSE_SETTER(ExampleProxy, setExampleProperty)

	// Getter prop example
	Ti::TiValue getExampleProperty();
	EXPOSE_GETTER(ExampleProxy, getExampleProperty)

	// Method exampleMethod
	Ti::TiValue exampleMethod(Ti::TiValue);
	EXPOSE_METHOD(ExampleProxy, exampleMethod)

};

#endif /* EXAMPLE_PROXY_H */
// ==================================================================================================
