/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWindowObject.h"

#include <bb/cascades/Application>
#include <bb/cascades/Page>

#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"
#include "Window.h"
#include "WindowGroup.h"

using namespace bb::cascades;

static titanium::WindowGroup* group = NULL;

NativeObject* NativeWindowObject::createWindow(TiObject* tiObject, NativeObjectFactory* factory)
{
    NativeObject* obj = new NativeWindowObject(tiObject);
    return obj;
}

NativeWindowObject::NativeWindowObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
{
}

int NativeWindowObject::addChildNativeObject(NativeObject* obj)
{
    return addChildImpl(obj);
}

void NativeWindowObject::open()
{
    events_["open"]->container->fireEvent();

    if (group == NULL) {
        group = new titanium::WindowGroup();

        Page* page = Page::create();
        page->setContent(group);
        Application::instance()->setScene(page);
    }
    group->insertWindow(static_cast<titanium::Window*>(container_));
}

void NativeWindowObject::close()
{
    group->removeWindow(static_cast<titanium::Window*>(container_));
    events_["close"]->container->fireEvent();
}

class EventHandler : public QObject
{
    Q_OBJECT

public:
    explicit EventHandler(TiEventContainer* container)
        : container_(container) { }

    virtual ~EventHandler() { }

protected:
    TiEventContainer* getEventContainer() const {
        return container_;
    }

private:
    TiEventContainer* container_;
};

class FocusEventHandler : public EventHandler
{
    Q_OBJECT

public:
    explicit FocusEventHandler(TiEventContainer* container)
        : EventHandler(container) { }

public slots:
    void onFocus()
    {
        getEventContainer()->fireEvent();
    }
};

class BlurEventHandler : public EventHandler
{
    Q_OBJECT

public:
    explicit BlurEventHandler(TiEventContainer* container)
        : EventHandler(container) { }

public slots:
    void onBlur() {
        getEventContainer()->fireEvent();
    }
};

#include "NativeWindowObject.moc"

int NativeWindowObject::initialize()
{
    if (container_ != NULL) {
        return NATIVE_ERROR_OK;
    }

    container_ = new titanium::Window();

    return NATIVE_ERROR_OK;
}

void NativeWindowObject::setupEvents(TiEventContainerFactory* factory)
{
    TiEventContainer* eventFocus = factory->createEventContainer();
    eventFocus->setDataProperty("type", "focus");
    events_.insert("focus", EventPairSmartPtr(eventFocus, new FocusEventHandler(eventFocus)));
    QObject::connect(container_, SIGNAL(onFocus()), events_["focus"]->handler, SLOT(onFocus()));

    TiEventContainer* eventBlur = factory->createEventContainer();
    eventBlur->setDataProperty("type", "blur");
    events_.insert("blur", EventPairSmartPtr(eventBlur, new BlurEventHandler(eventBlur)));
    QObject::connect(container_, SIGNAL(onBlur()), events_["blur"]->handler, SLOT(onBlur()));

    TiEventContainer* eventOpen = factory->createEventContainer();
    eventOpen->setDataProperty("type", "open");
    events_.insert("open", EventPairSmartPtr(eventOpen, new EventHandler(eventOpen)));

    TiEventContainer* eventClose = factory->createEventContainer();
    eventClose->setDataProperty("type", "close");
    events_.insert("close", EventPairSmartPtr(eventClose, new EventHandler(eventClose)));
}

