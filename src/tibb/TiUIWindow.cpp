/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWindow.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetGetObject.h"
#include "NativeWindowObject.h"
#include "Modules/UI/BlackBerry/NavButton/NavButtonProxy.h"

TiUIWindow::TiUIWindow()
    : TiUIBase("Window"),
      isModal(false)
{
}

TiUIWindow::~TiUIWindow()
{
}

TiUIWindow* TiUIWindow::createWindow(NativeObjectFactory* objectFactory)
{
    TiUIWindow* obj = new TiUIWindow;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

Handle<Value> TiUIWindow::_getModal(void* userContext)
{
	HandleScope scope;
	TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
	return scope.Close(Boolean::New(self->isModal));
}

void TiUIWindow::_setModal(void* userContext, Handle<Value> value)
{
	TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
	self->isModal = value->ToBoolean()->Value();
}

Handle<Value> TiUIWindow::_getLeftNavButton(void* userContext)
{
	return Undefined();
}
void TiUIWindow::_setLeftNavButton(void* userContext, Handle<Value> value)
{
	Handle<Value> _a = value->ToObject()->GetHiddenValue(String::New("proxy"));
	if(_a.IsEmpty()) return;

	Handle<External> _b = Handle<External>::Cast(_a);
	if(_b.IsEmpty()) return;

	TiUI::NavButtonProxy *_proxy = NULL;

	if(_b->Value())
	{
		_proxy = static_cast<TiUI::NavButtonProxy*>(_b->Value());
	}
	if(_proxy != NULL)
	{
		TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
	    NativeWindowObject* window = static_cast<NativeWindowObject*>(self->getNativeObject());
	    window->scene_.titleBar()->setDismissAction(_proxy->getNativeItem());
	}
}
Handle<Value> TiUIWindow::_getRightNavButton(void* userContext)
{
	return Undefined();
}
void TiUIWindow::_setRightNavButton(void* userContext, Handle<Value> value)
{
	Handle<Value> _a = value->ToObject()->GetHiddenValue(String::New("proxy"));
	if(_a.IsEmpty()) return;

	Handle<External> _b = Handle<External>::Cast(_a);
	if(_b.IsEmpty()) return;

	TiUI::NavButtonProxy *_proxy = NULL;

	if(_b->Value())
	{
		_proxy = static_cast<TiUI::NavButtonProxy*>(_b->Value());
	}
	if(_proxy != NULL)
	{
		TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
	    NativeWindowObject* window = static_cast<NativeWindowObject*>(self->getNativeObject());
	    window->scene_.titleBar()->setAcceptAction(_proxy->getNativeItem());
	}
}


void TiUIWindow::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addAction", this, _addAction);
    TiPropertySetGetObject::createProperty(this, "modal", this, _setModal, _getModal);
    TiPropertySetGetObject::createProperty(this, "rightNavButton", this, _setRightNavButton, _getRightNavButton);
    TiPropertySetGetObject::createProperty(this, "leftNavButton", this, _setLeftNavButton, _getRightNavButton);


}

void TiUIWindow::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_WINDOW, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIWindow::_open(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope scope;
    TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
    NativeWindowObject* window = static_cast<NativeWindowObject*>(self->getNativeObject());

    vector<ObjectEntry>::iterator it;
    for (it = self->childControls_.begin(); it != self->childControls_.end(); it++)
    {
        (*it)->setupEvents();
    }

    if(args.Length() > 0 && args[0]->IsObject())
    {
    	Local<Object> modal = args[0]->ToObject();
    	Local<Boolean> isTrue = modal->Get(String::New("modal"))->ToBoolean();
    	self->isModal = isTrue->Value();
    	window->open(isTrue->Value());
    }
    else
    {
    	window->open(self->isModal);
    }
    window->release(); // XXX(josh): Do we really want to release now?

    return Undefined();
}

Handle<Value> TiUIWindow::_close(void* userContext, TiObject*, const Arguments&)
{
    HandleScope scope;
    TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
    NativeWindowObject* window = static_cast<NativeWindowObject*>(self->getNativeObject());

    window->close();

    return Undefined();
}

Handle<Value> TiUIWindow::_addAction(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWindow* self = static_cast<TiUIWindow*>(userContext);
    NativeWindowObject* window = static_cast<NativeWindowObject*>(self->getNativeObject());

    bool hasImage = args.Length() > 2;
    if (args.Length() < 2) {
        return ThrowException(Exception::Error(String::New("Missing arguments: addAction(title, [image], triggerCallback)")));
    }
    if (!args[hasImage ? 2 : 1]->IsFunction()) {
        return ThrowException(Exception::Error(String::New("'triggerCallback' argument must be function.")));
    }

    QString title = QString::fromUtf8(*String::Utf8Value(args[0]));
    Handle<Function> triggerCallback = Handle<Function>::Cast(args[hasImage ? 2 : 1]);
    QString image;
    if (hasImage) {
        image = QString::fromUtf8(*String::Utf8Value(args[1]));
    }

    window->addAction(title, image, triggerCallback);

    return Undefined();
}
