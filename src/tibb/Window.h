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
    Window(struct Node* layout)
        : layout_(layout) { }

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

    // Returns the root layout node for this window's view tree.
    struct Node* layoutNode() const {
        return layout_;
    }

signals:
    void onFocus();
    void onBlur();
    void onActionAdded(bb::cascades::ActionItem* item);

private:
    struct Node* layout_;
};

} // namespace titanium

#endif
