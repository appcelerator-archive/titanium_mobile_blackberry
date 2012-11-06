/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_ABSTRACT_WINDOW_H
#define TI_ABSTRACT_WINDOW_H

#include <bb/cascades/Container>

namespace titanium {

class AbstractWindow : public bb::cascades::Container {
    Q_OBJECT

protected:
    virtual void focus() = 0;
    virtual void blur() = 0;
};

} // namespace titanium

#endif
