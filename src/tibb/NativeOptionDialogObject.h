/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOPTIONDIALOGOBJECT_H_
#define NATIVEOPTIONDIALOGOBJECT_H_

#include "NativeProxyObject.h"
#include <bb/system/SystemListDialog>
#include <bb/system/SystemUiButton>
#include "EventHandler.h"

class NativeOptionDialogObject: public NativeProxyObject
{
public:
	static NativeOptionDialogObject* createDialog(TiObject *);
	void show();
	void hide();
	void setOptions(QStringList);
	void setTitle(QString);
	void setSelectedIndex(int);
	void setEventFactory(TiEventContainerFactory* containerFactory){
		setupEvents(containerFactory);
	}
protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);
	virtual ~NativeOptionDialogObject();

private:
	explicit NativeOptionDialogObject(TiObject *);
	NativeOptionDialogObject(const NativeOptionDialogObject&);
	NativeOptionDialogObject& operator=(const NativeOptionDialogObject&);
	bb::system::SystemListDialog *dialog_;
	QStringList buttonNames_;
	int selectedIndex_;

};

using namespace titanium;

class NativeOptionDialogEventHandler : public EventHandler
{
    Q_OBJECT

public:
    explicit  NativeOptionDialogEventHandler(TiEventContainer* eventContainer)
      : EventHandler(eventContainer) { }

public slots:

    void clicked(bb::system::SystemUiResult::Type);
};

#endif /* NATIVEOPTIONDIALOGOBJECT_H_ */
