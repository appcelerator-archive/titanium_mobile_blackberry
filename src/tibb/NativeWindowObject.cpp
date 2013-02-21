/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWindowObject.h"

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
#include <bb/cascades/Image>
#include <bb/cascades/Page>
#include <bb/device/DisplayInfo>

#include "EventHandler.h"
#include "PageScene.h"
#include "SceneManager.h"
#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "Window.h"

using namespace bb::cascades;
using namespace titanium;
using namespace v8;

NativeObject* NativeWindowObject::createWindow(TiObject* tiObject, NativeObjectFactory* factory)
{
    NativeObject* obj = new NativeWindowObject(tiObject);
    return obj;
}

NativeWindowObject::NativeWindowObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_WINDOW)
{
}

int NativeWindowObject::addChildNativeObject(NativeObject* obj)
{
    return addChildImpl(obj);
}

void NativeWindowObject::updateLayout(QRectF rect) {
    layoutNode_.element._measuredWidth = rect.width();
    layoutNode_.element._measuredHeight = rect.height();
    struct Node* root = nodeRequestLayout(&layoutNode_);
    if (root) {
        nodeLayout(root);
    }
}

void NativeWindowObject::open()
{
    SceneManager::instance()->presentScene(&scene_);
    events_["open"]->container()->fireEvent();
}

void NativeWindowObject::close()
{
    if (scene_.state() == Scene::STATE_CLOSED) {
        // This window is not currently open.
        return;
    }
    scene_.close();
    events_["close"]->container()->fireEvent();
}

class ActionItemTriggerHandler : public QObject
{
    Q_OBJECT

public:
    explicit ActionItemTriggerHandler(TiObject* recv, Handle<Function> callback)
        : recv_(recv)
        , callback_(Persistent<Function>::New(callback)) { }

    virtual ~ActionItemTriggerHandler() {
        callback_.Dispose();
    }

public slots:
    void triggered() {
        HandleScope scope;
        callback_->Call(recv_->getValue()->ToObject(), 0, NULL);
    }

private:
    TiObject* recv_;
    Persistent<Function> callback_;
};

void NativeWindowObject::addAction(const QString& title, const QString& image, Handle<Function> triggerCallback)
{
    ActionItem* item = ActionItem::create();
    item->setTitle(title);
    if (!image.isEmpty()) {
        item->setImageSource(getResourcePath(image));
    }
    QObject::connect(item, SIGNAL(triggered()), new ActionItemTriggerHandler(tiObject_, triggerCallback), SLOT(triggered()));
    scene_.addAction(item);
}

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

    setContainer(scene_.mainWindow());
    return NATIVE_ERROR_OK;
}

void NativeWindowObject::setupEvents(TiEventContainerFactory* factory)
{
    TiEventContainer* eventFocus = factory->createEventContainer();
    eventFocus->setDataProperty("type", "focus");
    events_.insert("focus", EventPairSmartPtr(eventFocus, new FocusEventHandler(eventFocus)));
    QObject::connect(container_, SIGNAL(onFocus()), events_["focus"]->handler(), SLOT(onFocus()));

    TiEventContainer* eventBlur = factory->createEventContainer();
    eventBlur->setDataProperty("type", "blur");
    events_.insert("blur", EventPairSmartPtr(eventBlur, new BlurEventHandler(eventBlur)));
    QObject::connect(container_, SIGNAL(onBlur()), events_["blur"]->handler(), SLOT(onBlur()));

    TiEventContainer* eventOpen = factory->createEventContainer();
    eventOpen->setDataProperty("type", "open");
    events_.insert("open", EventPairSmartPtr(eventOpen, new EventHandler(eventOpen)));

    TiEventContainer* eventClose = factory->createEventContainer();
    eventClose->setDataProperty("type", "close");
    events_.insert("close", EventPairSmartPtr(eventClose, new EventHandler(eventClose)));
}

