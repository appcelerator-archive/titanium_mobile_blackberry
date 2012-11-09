/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCENE_MANAGER_H
#define TI_SCENE_MANAGER_H

#include <QList>
#include <QObject>

namespace titanium {

class Scene;

class SceneManager : public QObject {
    Q_OBJECT

public:
    /**
     * Returns the scene manager for this application.
     */
    static SceneManager* instance() {
        static SceneManager* instance = new SceneManager();
        return instance;
    }

    /**
     * Present a scene making it the active instance
     * for the application. The previously active scene
     * will be hidden and the new active scene
     * will take over the device's screen.
     */
    void presentScene(Scene* scene);

    /**
     * Returns the currently active scene being
     * displayed on the device's screen. If there
     * is no active scene returns NULL.
     */
    Scene* activeScene() const;

public slots:
    /**
     * Called once a scene is closed and should
     * be removed from the scene stack. If the scene
     * is active it will be removed from the screen.
     */
    bool removeScene(Scene* scene);

private:
    SceneManager();

    QList<Scene*> scenes_;
};

} // namespace titanium

#endif
