/*
 * TiUINavigationWindow.h
 *
 *  Created on: May 13, 2014
 *      Author: penrique
 */

#ifndef TIUINAVIGATIONWINDOW_H_
#define TIUINAVIGATIONWINDOW_H_

#include <TiCore.h>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>

namespace TiUI {

class TiUINavigationWindow : public Ti::TiWindowProxy
{
public:
	CREATE_PROXY(TiUINavigationWindow)
	TiUINavigationWindow(const char*);
	virtual ~TiUINavigationWindow();

	Ti::TiValue close(Ti::TiValue);
	Ti::TiValue open(Ti::TiValue);
	Ti::TiValue pop(Ti::TiValue);
	Ti::TiValue push(Ti::TiValue);
	Ti::TiValue remove(Ti::TiValue);

	EXPOSE_METHOD(TiUINavigationWindow, close)
	EXPOSE_METHOD(TiUINavigationWindow, open)
	EXPOSE_METHOD(TiUINavigationWindow, pop)
	EXPOSE_METHOD(TiUINavigationWindow, push)
	EXPOSE_METHOD(TiUINavigationWindow, remove)

	TI_CREATE_SETTER_GETTER(TiUINavigationWindow, setWindow, getWindow);
	TI_CREATE_SETTER_GETTER(TiUINavigationWindow, setRootWindow, getRootWindow);
	TI_CREATE_SETTER_GETTER(TiUINavigationWindow, setBackButtonsVisible, getBackButtonsVisible);
	TI_CREATE_SETTER_GETTER(TiUINavigationWindow, setPeekEnabled, getPeekEnabled);

	virtual void removeWindow(Ti::TiWindowProxy*);
	virtual void addWindow(Ti::TiWindowProxy*);
	QList<Ti::TiWindowProxy*> getAllWindows();
private:
	Ti::TiWindowProxy *_rootWindow;
	bb::cascades::NavigationPane *_navigationPane;
	QList<Ti::TiWindowProxy*> _allWindows;
};

class TiUINavigationWindowEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiUINavigationWindowEventHandler(TiUINavigationWindow *);
	TiUINavigationWindow* _proxy;
	Ti::TiWindowProxy* windowFromPage(bb::cascades::Page*);
public slots:
	void onPagePoped(bb::cascades::Page*);
	void onPagePushed(bb::cascades::Page*);
	void onPageFocused(bb::cascades::Page*);
};

} /* namespace TiUI */
#endif /* TIUINAVIGATIONWINDOW_H_ */
