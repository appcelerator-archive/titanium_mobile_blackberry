/*
 * ApplicationMenuProxy.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: penrique
 */

#include "ApplicationMenuProxy.h"
#include <bb/cascades/Menu>
#include <bb/cascades/ActionItem>

static bb::cascades::Menu* _appMenu = NULL;
static TiUI::ApplicationMenuEventHandler* _appMenuEventHandler = NULL;

namespace TiUI {

ApplicationMenuProxy::ApplicationMenuProxy(const char* name) :
	Ti::TiProxy(name)
{
	createPropertySetterGetter("items", _setItems, _getItems);
	createPropertyFunction("addItem", _addItem);
	createPropertyFunction("removeItem", _removeItem);
	createPropertyFunction("removeAllItems", _removeAllItems);

	if(_appMenu == NULL)
	{
		_appMenu = new bb::cascades::Menu();
		_appMenuEventHandler = new ApplicationMenuEventHandler();
		bb::cascades::Application::instance()->setMenu(_appMenu);
	}
	_appMenuEventHandler->addProxy(this);
}

ApplicationMenuProxy::~ApplicationMenuProxy()
{
	_appMenuEventHandler->removeProxy(this);
}

void ApplicationMenuProxy::setItems(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> items = value.toList();
	foreach(Ti::TiValue item, items)
	{
		addItem(item);
	}
}
Ti::TiValue ApplicationMenuProxy::getItems()
{
	QList<Ti::TiValue> list;

	for(int i = 0, len = _appMenu->actionCount(); i < len; i++)
	{
		bb::cascades::ActionItem* item = _appMenu->actionAt(i);
		QMap<QString, Ti::TiValue> map;
		Ti::TiValue title;
		title.setString(item->title());
		map.insert("title", title);

		Ti::TiValue icon;
		QString src = item->imageSource().toString();
		src.replace("asset:///", "");
		src.replace(Ti::TiConstants::ResourcesDir, "");
		icon.setString(src);
		map.insert("icon", icon);

		Ti::TiValue obj;
		obj.setMap(map);
		list.append(obj);
	}

	Ti::TiValue val;
	val.setList(list);
	return val;
}
Ti::TiValue ApplicationMenuProxy::addItem(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();

	if(!value.isMap()) return val;
	QMap<QString, Ti::TiValue> current = value.toMap();
	bb::cascades::ActionItem *item = new bb::cascades::ActionItem();
	if(current.contains("title"))
	{
		Ti::TiValue title = current["title"];
		item->setTitle(title.toString());
	}
	if(current.contains("icon"))
	{
		Ti::TiValue icon = current["icon"];
		QString path = QString("asset:///").append(icon.toString()).replace("////","///");
		item->setImageSource(QUrl(path));
	}
	QObject::connect(item, SIGNAL(triggered()), _appMenuEventHandler, SLOT(onClick()));
	_appMenu->addAction(item);
	return val;
}
Ti::TiValue ApplicationMenuProxy::removeItem(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();
	if(!value.isNumber()) return val;

	bb::cascades::ActionItem *item = _appMenu->actionAt((int)value.toNumber());
	if(item != NULL)
	{
		_appMenu->removeAction(item);
	}
	return val;
}
Ti::TiValue ApplicationMenuProxy::removeAllItems(Ti::TiValue)
{
	while(_appMenu->actionCount() > 0)
	{
		bb::cascades::ActionItem *item = _appMenu->actionAt(_appMenu->actionCount() - 1);
		if(item != NULL)
		{
			_appMenu->removeAction(item);
		}
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

ApplicationMenuEventHandler::ApplicationMenuEventHandler() : QObject(NULL)
{

}
ApplicationMenuEventHandler::~ApplicationMenuEventHandler()
{

}
void ApplicationMenuEventHandler::addProxy(ApplicationMenuProxy* proxy)
{
	_proxies.append(proxy);
}
void ApplicationMenuEventHandler::removeProxy(ApplicationMenuProxy* proxy)
{
	if(_proxies.contains(proxy))
	{
		_proxies.removeOne(proxy);
	}
}

void ApplicationMenuEventHandler::onClick()
{
	bb::cascades::ActionItem *item = static_cast<bb::cascades::ActionItem*>(sender());
	int index = -1;
	for(int i = 0, len = _appMenu->actionCount(); i < len; i++)
	{
		bb::cascades::ActionItem* current = _appMenu->actionAt(i);
		if(item == current) {
			index = i;
			break;
		}
	}
	Ti::TiEventParameters eventParams;
	eventParams.addParam("type", Ti::TiConstants::EventClick);
	eventParams.addParam("index", index);

	foreach(ApplicationMenuProxy* proxy, _proxies)
	{
		proxy->fireEvent(Ti::TiConstants::EventClick, eventParams);
	}
}
} /* namespace TiUI */
