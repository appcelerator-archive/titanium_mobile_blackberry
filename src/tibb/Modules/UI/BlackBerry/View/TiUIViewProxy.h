/*
 * TiUIViewProxy.h
 *
 *  Created on: Jul 14, 2013
 *      Author: penrique
 */

#ifndef TIUIVIEWPROXY_H_
#define TIUIVIEWPROXY_H_

#include <TiCore.h>

namespace TiUI {

class TiUIViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIViewProxy);
	TiUIViewProxy(const char*);
	virtual ~TiUIViewProxy();
	void setVisible(Ti::TiValue);
	EXPOSE_SETTER(TiUIViewProxy, setVisible)
};
}
#endif /* TIUIVIEWPROXY_H_ */
