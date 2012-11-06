/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWindowObject.h"

#include <bb/cascades/Application>
#include <bb/cascades/Page>

#include "AbstractWindow.h"
#include "WindowGroup.h"

using namespace bb::cascades;
using namespace titanium;

static WindowGroup* group = NULL;

class Window : public AbstractWindow {
    Q_OBJECT

  public:
    virtual void focus() {
    }

    virtual void blur() {
    }
};

void NativeWindowObject::open()
{
    if (group == NULL) {
        group = new WindowGroup();

        Page* page = Page::create();
        page->setContent(group);
        Application::instance()->setScene(page);
    }
    group->insertWindow(static_cast<AbstractWindow*>(container_));
}

void NativeWindowObject::close()
{
    group->removeWindow(container_);
}

int NativeWindowObject::initialize()
{
    if (container_ != NULL || page_ != NULL) {
        return NATIVE_ERROR_OK;
    }

    container_ = new Window();
    page_ = Page::create();
    page_->setContent(container_);

    return NATIVE_ERROR_OK;
}

