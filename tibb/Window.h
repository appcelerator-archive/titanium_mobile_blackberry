/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_WINDOW_H
#define TI_WINDOW_H

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>

namespace titanium {

class Window : public bb::cascades::Container {
    Q_OBJECT

public:
    virtual void focus() {
        emit onFocus();
    }

    virtual void blur() {
        emit onBlur();
    }

    virtual void addAction(bb::cascades::ActionItem* item) {
        fprintf(stderr, "Widow::addAction()\n");
        emit onActionAdded(item);
    }

signals:
    void onFocus();
    void onBlur();
    void onActionAdded(bb::cascades::ActionItem* item);
};

} // namespace titanium

#endif
