/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_WINDOW_H
#define TI_WINDOW_H

#include <bb/cascades/Container>

namespace titanium {

class Scene;

class Window : public bb::cascades::Container {
    Q_OBJECT

public:
    Window(Scene* scene);

    Scene* scene() const {
        return scene_;
    }

    void focus();
    void blur();

signals:
    void onFocus();
    void onBlur();

private:
    Scene* scene_;
};

} // namespace titanium

#endif
