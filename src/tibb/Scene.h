/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCENE_H
#define TI_SCENE_H

#include <bb/cascades/AbstractPane>
#include <bb/cascades/ActionItem>
#include <QObject>
#include <QScopedPointer>

namespace titanium {

class WindowGroup;

class Scene : public QObject {
    Q_OBJECT

public:
    explicit Scene(bb::cascades::AbstractPane* pane)
        : pane_(pane)
        , state_(STATE_CLOSED) {
    }

    /**
     * Returns the root pane for this scene.
     */
    bb::cascades::AbstractPane* pane() const {
        return pane_.data();
    }

    /**
     * Close the scene and signal scene manager
     * to remove it from the screen and scene stack.
     */
    virtual void close() {
        emit onClose(this);
    }

    /**
     * The various states the scene can go
     * through during its lifetime.
     *
     * Currently there's two states for tracking
     * when the scene is on or off the screen.
     * The state can change between these two
     * as this scene and other instances are
     * presented and closed while the application runs.
     */
    enum State {
        // The scene enters this state after
        // being activated and presented to the screen.
        // During this state the scene's root pane
        // is being drawn to the device's display.
        STATE_ONSTAGE,

        // The scene enters this state before
        // being deactived and removed from the screen.
        // The root pane of the scene will be removed
        // and no longer drawn to the display.
        STATE_BACKSTAGE,

        // Scene is closed and not attached to a scene manager.
        // This is the initial state a scene enters upon creation.
        STATE_CLOSED
    };

    /**
     * Called when the scene's state has changed.
     */
    virtual void changeState(State newState) {
        state_ = newState;
    }

    /**
     * Returns the current state of this scene.
     */
    State state() const {
        return state_;
    }

protected:
    void setPane(bb::cascades::AbstractPane* pane) {
        pane->setParent(this);
        pane_.reset(pane);
    }

signals:
    /**
     * Emitted by a scene once it has closed and should
     * be removed from the screen by the scene manager.
     */
    void onClose(Scene* scene);

private:
    QScopedPointer<bb::cascades::AbstractPane> pane_;
    State state_;
};

} // namespace titanium

#endif
