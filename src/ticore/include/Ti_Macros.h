#ifndef TI_MACROS_H_
#define TI_MACROS_H_

/**
 * Makes the getter return Undefined() which will return a value if a setter for the same
 * property was assigned.
 *
 * Ti::TiValue Ti::TiMyProxy::getPropery()
 * {
 * 		return Ti::TiValue();
 * }
 */
#define TI_GETTER_DEFER(PROXY_CLASS, METHOD) \
	Ti::TiValue PROXY_CLASS::METHOD() \
	{ \
		return Ti::TiValue(); \
	} \

#define TI_CREATE_SETTER(PROXY_CLASS, SETTER_METHOD) \
	static void _##SETTER_METHOD(TiProxy* proxy, Ti::TiValue value) \
	{ 	\
			PROXY_CLASS* mProxy = static_cast<PROXY_CLASS*>(proxy);	\
			mProxy->SETTER_METHOD(value);	\
	} \
	void SETTER_METHOD(Ti::TiValue);

#define TI_CREATE_GETTER(PROXY_CLASS, GETTER_METHOD) \
	static Ti::TiValue _##GETTER_METHOD(Ti::TiProxy* proxy) \
	{ 	\
			PROXY_CLASS* mProxy = static_cast<PROXY_CLASS*>(proxy);	\
			return mProxy->GETTER_METHOD();	\
	} \
	Ti::TiValue GETTER_METHOD();

#define TI_CREATE_SETTER_GETTER(PROXY_CLASS, SETTER_METHOD, GETTER_METHOD) \
		TI_CREATE_SETTER(PROXY_CLASS, SETTER_METHOD) \
		TI_CREATE_GETTER(PROXY_CLASS, GETTER_METHOD)

#endif
