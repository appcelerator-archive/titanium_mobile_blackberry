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
#include <bb/cascades/TitleBar>
#include <bb/cascades/Sheet>
#include <bb/device/DisplayInfo>

#include "EventHandler.h"
#include "PageScene.h"
#include "SceneManager.h"
#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "TiOrientation.h"
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
    : NativeControlObject(tiObject, N_TYPE_WINDOW), modalSheet_(NULL), title_(" ")
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

int NativeWindowObject::setOrientationModes(TiObject* obj) {
    Handle<Value> val = obj->getValue();
    if (!val->IsArray()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    // Convert the array of modes into a bitwise flags value.
    Handle<Array> modes = Handle<Array>::Cast(val);
    uint32_t modeCount = modes->Length();
    int flags = 0;
    for (uint32_t i = 0; i < modeCount; i++) {
        int32_t flag = modes->Get(i)->Int32Value();
        flags |= Orientation::toSceneMode(static_cast<Orientation::Type>(flag));
    }

    scene_.setOrientationModes(flags);

    return NATIVE_ERROR_OK;
}

//titanium::PageScene NativeWindowObject::getScene()
//{
//	return scene_;
//}

int NativeWindowObject::setTitle(TiObject* obj) {
	title_ = QString::fromUtf8(*String::Utf8Value(obj->getValue()));
    scene_.titleBar()->setTitle(title_);
    return NATIVE_ERROR_OK;
}

void NativeWindowObject::open(bool modal)
{
	if(SceneManager::instance()->activeScene() == NULL) {
		// At least one scene needs to be in place, AKA: one window needs to be opened.
		modal = false;
	}
	if(modal) {
	    scene_.titleBar()->setTitle(title_);
		modalSheet_ = bb::cascades::Sheet::create();
		modalSheet_->setContent(scene_.pane());
		modalSheet_->setPeekEnabled(false);
		modalSheet_->open();
		scene_.changeState(Scene::STATE_ONSTAGE);
	} else {
	    SceneManager::instance()->presentScene(&scene_);
	}
    events_["open"]->container()->fireEvent();
}

void NativeWindowObject::close()
{
    if (scene_.state() == Scene::STATE_CLOSED) {
        // This window is not currently open.
        return;
    }
    if(modalSheet_ == NULL) {
    	scene_.close();
    } else {
    	modalSheet_->close();
    }
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
    NativeControlObject::setupEvents(factory);
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

