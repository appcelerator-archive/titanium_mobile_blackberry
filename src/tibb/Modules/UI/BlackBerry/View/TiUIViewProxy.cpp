/*
 * TiUIViewProxy.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: penrique
 */

#include "TiUIViewProxy.h"
#include "TiUIView.h"
#include <unistd.h>
namespace TiUI {

TiUIViewProxy::TiUIViewProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetter("visible", _setVisible);
	setView(new TiUIView(this));
}

TiUIViewProxy::~TiUIViewProxy()
{

}

void TiUIViewProxy::setVisible(Ti::TiValue value)
{
	view->setVisible(value.toBool());
}

}
