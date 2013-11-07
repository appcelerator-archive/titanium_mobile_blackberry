/*
 * NavButtonProxy.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: penrique
 */

#include "NavButtonProxy.h"

namespace TiUI
{

NavButtonProxy::NavButtonProxy(const char* name) : Ti::TiProxy(name)
{
	createPropertySetterGetter("title", _setTitle, _getTitle);
	_item = new bb::cascades::ActionItem();
	QObject::connect(_item, SIGNAL(triggered()), new NavButtonEventHandler(this), SLOT(triggered()));
}

bb::cascades::ActionItem *NavButtonProxy::getNativeItem()
{
	return _item;
}

Ti::TiValue NavButtonProxy::getTitle()
{
	Ti::TiValue val;
	val.setString(_item->title());
	return val;
}
void NavButtonProxy::setTitle(Ti::TiValue value)
{
	_item->setTitle(value.toString());
}

NavButtonProxy::~NavButtonProxy() {
	_item->deleteLater();
}

NavButtonEventHandler::NavButtonEventHandler(NavButtonProxy* proxy) : _proxy(proxy)
{
}
NavButtonEventHandler::~NavButtonEventHandler()
{
}

void NavButtonEventHandler::triggered()
{
	Ti::TiEventParameters params;
	_proxy->fireEvent(Ti::TiConstants::EventClick, params);
}

}
