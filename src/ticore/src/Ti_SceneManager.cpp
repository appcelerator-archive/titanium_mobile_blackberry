/*
 * TiSceneManager.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_SceneManager.h"
#include "Ti_WindowProxy.h"
#include "Ti_EventParameters.h"
#include "Ti_Constants.h"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>

static Ti::TiSceneManager* _instance = NULL;

Ti::TiSceneManager::TiSceneManager() {
	// TODO Auto-generated constructor stub

}

Ti::TiSceneManager::~TiSceneManager() {
	// TODO Auto-generated destructor stub
}

void Ti::TiSceneManager::addPane(Ti::TiWindowProxy* window)
{
	if(_windows.contains(window)) {
		_windows.removeOne(window);
	}

	if(_windows.size() > 0)
	{
		Ti::TiWindowProxy *lastWindow = _windows.last();
		Ti::TiEventParameters eventParams;
		eventParams.addParam("type", Ti::TiConstants::EventBlur);
		lastWindow->fireEvent(Ti::TiConstants::EventBlur, eventParams);
	}

	_windows.append(window);

	bb::cascades::AbstractPane *pane = window->getPane();
	bb::cascades::Application::instance()->setScene(pane);
	pane->setParent(0);

	Ti::TiEventParameters eventParams;
	eventParams.addParam("type", Ti::TiConstants::EventFocus);
	window->fireEvent(Ti::TiConstants::EventFocus, eventParams);
}

void Ti::TiSceneManager::removePane(Ti::TiWindowProxy* window)
{
	if(!_windows.contains(window)) return;

	_windows.removeOne(window);
	Ti::TiEventParameters eventParams;
	eventParams.addParam("type", Ti::TiConstants::EventBlur);
	window->fireEvent(Ti::TiConstants::EventBlur, eventParams);

	if(_windows.size() > 0)
	{
		Ti::TiWindowProxy *lastWindow = _windows.last();
		bb::cascades::AbstractPane *pane = lastWindow->getPane();
		bb::cascades::Application::instance()->setScene(pane);
		pane->setParent(0);

		Ti::TiEventParameters eventParams;
		eventParams.addParam("type", Ti::TiConstants::EventFocus);
		lastWindow->fireEvent(Ti::TiConstants::EventFocus, eventParams);
	} else {
		bb::cascades::Application::instance()->setScene(NULL);
	}
}

void Ti::TiSceneManager::Open(Ti::TiWindowProxy* window)
{
	{
		Ti::TiEventParameters eventParams;
		eventParams.addParam("type", "open");
		window->fireEvent(Ti::TiConstants::EventOpen, eventParams);
	}
	Ti::TiSceneManager::Instance()->addPane(window);
}

void Ti::TiSceneManager::Close(Ti::TiWindowProxy* window)
{
	Ti::TiSceneManager::Instance()->removePane(window);
	{
		Ti::TiEventParameters eventParams;
		eventParams.addParam("type", "close");
		window->fireEvent(Ti::TiConstants::EventClose, eventParams);
	}
}

Ti::TiSceneManager* Ti::TiSceneManager::Instance()
{
	if(_instance == NULL)
	{
		_instance = new Ti::TiSceneManager();
	}
	return _instance;
}
