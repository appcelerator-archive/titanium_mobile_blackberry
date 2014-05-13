/*
 * TiUINavigationWindow.cpp
 *
 *  Created on: May 13, 2014
 *      Author: penrique
 */

#include "TiUINavigationWindow.h"
#include "../NavButton/NavButtonProxy.h"


namespace TiUI {

TiUINavigationWindow::TiUINavigationWindow(const char* name) : Ti::TiWindowProxy(name), _rootWindow(NULL)
{

	createPropertySetterGetter("window", _setWindow, _getWindow);
	createPropertySetterGetter("rootWindow", _setRootWindow, _getRootWindow);
	createPropertySetterGetter("backButtonsVisible", _setBackButtonsVisible, _getBackButtonsVisible);
	createPropertySetterGetter("peekEnabled", _setPeekEnabled, _getPeekEnabled);

	createPropertyFunction("close", _close);
	createPropertyFunction("open", _open);
	createPropertyFunction("pop", _pop);
	createPropertyFunction("push", _push);
	createPropertyFunction("remove", _remove);

	TiUINavigationWindowEventHandler *event = new TiUINavigationWindowEventHandler(this);
	_navigationPane = new bb::cascades::NavigationPane();
	QObject::connect(_navigationPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)), event, SLOT(onPagePoped(bb::cascades::Page*)));
	QObject::connect(_navigationPane, SIGNAL(pushTransitionEnded(bb::cascades::Page*)), event, SLOT(onPagePushed(bb::cascades::Page*)));
	QObject::connect(_navigationPane, SIGNAL(topChanged(bb::cascades::Page*)), event, SLOT(onPageFocused(bb::cascades::Page*)));
	setPane(_navigationPane);
}

TiUINavigationWindow::~TiUINavigationWindow()
{

}

Ti::TiValue TiUINavigationWindow::close(Ti::TiValue val)
{
	if(val.isProxy())
	{
		Ti::TiWindowProxy *win = static_cast<Ti::TiWindowProxy*>(val.toProxy());
		bb::cascades::Page *winPage = static_cast<bb::cascades::Page*>(win->getPane());
		if(_navigationPane->top() == winPage)
		{
			return pop(val);
		}
		else
		{
			return remove(val);
		}
	}
	while(_navigationPane->count() > 1)
	{
		_navigationPane->pop();
	}
	while(_allWindows.size() > 1) {
		_allWindows.removeLast();
	}
	return Ti::TiWindowProxy::close(val);
}
Ti::TiValue TiUINavigationWindow::open(Ti::TiValue val)
{
	if(val.isProxy())
	{
		return push(val);
	}
	return Ti::TiWindowProxy::open(val);
}
Ti::TiValue TiUINavigationWindow::pop(Ti::TiValue val)
{
	_navigationPane->pop();
	return Ti::TiValue();
}
Ti::TiValue TiUINavigationWindow::push(Ti::TiValue val)
{
	Ti::TiWindowProxy *win = static_cast<Ti::TiWindowProxy*>(val.toProxy());
	_navigationPane->push(static_cast<bb::cascades::Page*>(win->getPane()));
	win->getPane()->setParent(NULL);
	_allWindows.append(win);
	return Ti::TiValue();
}
Ti::TiValue TiUINavigationWindow::remove(Ti::TiValue val)
{
	Ti::TiWindowProxy *win = static_cast<Ti::TiWindowProxy*>(val.toProxy());
	_navigationPane->remove(static_cast<bb::cascades::Page*>(win->getPane()));
	return Ti::TiValue();
}

void TiUINavigationWindow::setWindow(Ti::TiValue val)
{
	if(_navigationPane->count() == 0)
	{
		_rootWindow = static_cast<Ti::TiWindowProxy*>(val.toProxy());
		push(val);
	}
}

void TiUINavigationWindow::setRootWindow(Ti::TiValue val)
{
	setWindow(val);
}

void TiUINavigationWindow::setBackButtonsVisible(Ti::TiValue val)
{
	_navigationPane->setBackButtonsVisible(val.toBool());
}

void TiUINavigationWindow::setPeekEnabled(Ti::TiValue val)
{
	_navigationPane->setPeekEnabled(val.toBool());
}

Ti::TiValue TiUINavigationWindow::getWindow()
{
	Ti::TiValue val;
	if(_rootWindow != NULL)
	{
		val.setProxy(_rootWindow);
	}
	return val;
}
Ti::TiValue TiUINavigationWindow::getRootWindow()
{
	return getWindow();
}
Ti::TiValue TiUINavigationWindow::getBackButtonsVisible()
{
	Ti::TiValue val;
	val.setBool(_navigationPane->backButtonsVisible());
	return val;
}
Ti::TiValue TiUINavigationWindow::getPeekEnabled()
{
	Ti::TiValue val;
	val.setBool(_navigationPane->isPeekEnabled());
	return val;
}

QList<Ti::TiWindowProxy*> TiUINavigationWindow::getAllWindows()
{
	return _allWindows;
}

void TiUINavigationWindow::removeWindow(Ti::TiWindowProxy* win)
{
	_allWindows.removeOne(win);
}
void TiUINavigationWindow::addWindow(Ti::TiWindowProxy* win)
{
	_allWindows.append(win);
}

TiUINavigationWindowEventHandler::TiUINavigationWindowEventHandler(TiUINavigationWindow *proxy) : _proxy(proxy)
{
}

Ti::TiWindowProxy* TiUINavigationWindowEventHandler::windowFromPage(bb::cascades::Page* page)
{
	foreach(Ti::TiWindowProxy* windowProxy, _proxy->getAllWindows())
	{
		if(windowProxy != NULL && static_cast<bb::cascades::Page*>(windowProxy->getPane()) == page)
		{
			return windowProxy;
		}
	}
	return NULL;
}
void TiUINavigationWindowEventHandler::onPagePoped(bb::cascades::Page* page)
{
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		{
			Ti::TiEventParameters _params;
			window->fireEvent(Ti::TiConstants::EventBlur, _params);
		}
		{
			Ti::TiEventParameters _params;
			window->fireEvent(Ti::TiConstants::EventClose, _params);
		}
		window->makeWeak();
		_proxy->removeWindow(window);
	}
}

void TiUINavigationWindowEventHandler::onPagePushed(bb::cascades::Page* page)
{
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		//_proxy->addWindow(window);
		window->clearWeak();
		Ti::TiEventParameters _params;
		window->fireEvent(Ti::TiConstants::EventOpen, _params);
	}
}

void TiUINavigationWindowEventHandler::onPageFocused(bb::cascades::Page* page)
{
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		foreach(Ti::TiWindowProxy* proxies, _proxy->getAllWindows())
		{
			if(proxies->isFocused())
			{
				Ti::TiEventParameters _params;
				proxies->fireEvent(Ti::TiConstants::EventBlur, _params);
			}
		}
		Ti::TiEventParameters _params;
		window->fireEvent(Ti::TiConstants::EventFocus, _params);
	}
}

} /* namespace TiUI */
