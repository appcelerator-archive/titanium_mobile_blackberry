/*
 * TiSceneManager.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: penrique
 */

#include "Ti_SceneManager.h"
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>

static Ti::TiSceneManager* _instance = NULL;

Ti::TiSceneManager::TiSceneManager() {
	// TODO Auto-generated constructor stub

}

Ti::TiSceneManager::~TiSceneManager() {
	// TODO Auto-generated destructor stub
}

void Ti::TiSceneManager::addPane(bb::cascades::AbstractPane* pane)
{
	if(_scenes.contains(pane)) {
		_scenes.removeOne(pane);
	}
	_scenes.append(pane);
	bb::cascades::Application::instance()->setScene(pane);
	pane->setParent(0);
}

void Ti::TiSceneManager::removePane(bb::cascades::AbstractPane* pane)
{
	if(_scenes.contains(pane)) {
		_scenes.removeOne(pane);
	}

	if(_scenes.size() > 0)
	{
		bb::cascades::AbstractPane *_pane = NULL;
		_pane = _scenes.last();
		bb::cascades::Application::instance()->setScene(_pane);
		_pane->setParent(0);
	}
}

void Ti::TiSceneManager::Open(bb::cascades::AbstractPane* pane)
{
	Ti::TiSceneManager::Instance()->addPane(pane);
}

void Ti::TiSceneManager::Close(bb::cascades::AbstractPane* pane)
{
	Ti::TiSceneManager::Instance()->removePane(pane);
}

Ti::TiSceneManager* Ti::TiSceneManager::Instance()
{
	if(_instance == NULL)
	{
		_instance = new Ti::TiSceneManager();
	}
	return _instance;
}
