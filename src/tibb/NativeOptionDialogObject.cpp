/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeOptionDialogObject.h"
#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"


NativeOptionDialogObject::NativeOptionDialogObject(TiObject * obj) : NativeProxyObject(obj)
{
	dialog_ = new bb::system::SystemListDialog();
	selectedIndex_ = -1;
}

NativeOptionDialogObject *NativeOptionDialogObject::createDialog(TiObject *obj)
{
	return new NativeOptionDialogObject(obj);
}

void NativeOptionDialogObject::show()
{
	dialog_->show();
}

void NativeOptionDialogObject::hide()
{
	dialog_->cancel();
}

void NativeOptionDialogObject::setTitle(QString str)
{
	dialog_->setTitle(str);
}
void NativeOptionDialogObject::setSelectedIndex(int index)
{
	selectedIndex_ = index;
	if(buttonNames_.length() > 0)
	{
		setOptions(buttonNames_);
	}
}
void NativeOptionDialogObject::setOptions(QStringList options)
{
	buttonNames_ = options;
	dialog_->clearList();
	for(int i = 0, len = options.length(); i < len; i++)
	{
		dialog_->appendItem(options.at(i), true, selectedIndex_ == i);
	}
}

void NativeOptionDialogObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeProxyObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new NativeOptionDialogEventHandler(eventClick)));
    QObject::connect(dialog_, SIGNAL(finished(bb::system::SystemUiResult::Type)), events_[tetCLICK]->handler(), SLOT(clicked(bb::system::SystemUiResult::Type)));

}

NativeOptionDialogObject::~NativeOptionDialogObject() {

}

void NativeOptionDialogEventHandler::clicked(bb::system::SystemUiResult::Type)
{
	bb::system::SystemListDialog* dialog = static_cast<bb::system::SystemListDialog*>(sender());
	bb::system::SystemUiButton* selectedButton = dialog->buttonSelection();
	if (selectedButton == NULL)
	{
		return;
	}
	int index = -1;
	if(dialog->selectedIndices().length() > 0)
	{
		index = dialog->selectedIndices().at(0);
	}
	TiEventContainer* container = getEventContainer();
	container->setDataProperty("index", index);
	container->setDataProperty("cancel", selectedButton == dialog->cancelButton());
	container->fireEvent();
}


