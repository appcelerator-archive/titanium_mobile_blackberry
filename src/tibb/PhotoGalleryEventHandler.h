/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef PHOTOGALLERYEVENTHANDLER_H_
#define PHOTOGALLERYEVENTHANDLER_H_

#include <QObject>
#include <bb/cascades/pickers/FilePicker>
class TiObject;
//#include <bb/cascades/pickers/FilePickerError>

class PhotoGalleryEventHandler: public QObject
{
	Q_OBJECT;
public:
	PhotoGalleryEventHandler(TiObject*);
	virtual ~PhotoGalleryEventHandler();
	void showPicker();
private:
	bb::cascades::pickers::FilePicker *_picker;
	TiObject *_object;
public slots:
	void onFileSelected(const QStringList&);
	void onCanceled();
//	void onError(bb::cascades::pickers::FilePickerError);
};

#endif /* PHOTOGALLERYEVENTHANDLER_H_ */
