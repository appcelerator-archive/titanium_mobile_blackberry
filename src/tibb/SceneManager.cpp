/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "SceneManager.h"

#include <bb/cascades/Application>

#include "Scene.h"

using namespace bb::cascades;

namespace titanium {

SceneManager::SceneManager() {
}

void SceneManager::presentScene(Scene* scene) {
    QObject::connect(scene, SIGNAL(onClose(Scene*)), this, SLOT(removeWindow(Scene*)));

    // Change the state of the currently active scene
    // to BACKSTAGE before removing it from the screen.
    Scene* currentScene = activeScene();
    if (currentScene) {
        Q_ASSERT(currentScene->state() == Scene::STATE_ONSTAGE);
        currentScene->changeState(Scene::STATE_BACKSTAGE);
    }

    // Set the application's active scene pane
    // to present the scene to the display.
    Application::instance()->setScene(scene->pane());

    // Change the state of the new activate scene to
    // ONSTAGE now that it's being presented to the screen.
    Q_ASSERT(scene->state() != Scene::STATE_ONSTAGE);
    scene->changeState(Scene::STATE_ONSTAGE);

    scenes_.append(scene);
}

Scene* SceneManager::activeScene() const {
    if (scenes_.isEmpty()) {
        return NULL;
    }
    return scenes_.last();
}

bool SceneManager::removeScene(Scene* scene) {
    // Find the scene in the stack and remove it.
    int index = scenes_.indexOf(scene);
    if (index == -1) {
        // No scene found in the stack.
        return false;
    }
    scenes_.removeAt(index);

    // If the scene being removed was active,
    // change states and bring the next scene
    // in the scene stack onto the screen.
    if (index == scenes_.count()) {
        scene->changeState(Scene::STATE_BACKSTAGE);

        Scene* nextScene = activeScene();
        Application::instance()->setScene(nextScene->pane());
        nextScene->changeState(Scene::STATE_ONSTAGE);
    }

    return true;
}

} // namespace titanium

