/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMEDIAPHOTOGALLERY_H_
#define TIMEDIAPHOTOGALLERY_H_

#include <TiCore.h>
#include <QObject>
#include <bb/cascades/pickers/FilePicker>

namespace TiMedia {

class TiMediaPhotoGalleryEventHandler;
class TiMediaPhotoGallery : public Ti::TiProxy {
public:
	CREATE_PROXY(TiMediaPhotoGallery)
	TiMediaPhotoGallery(const char*);
	virtual ~TiMediaPhotoGallery();
	virtual void initEnd();

	TI_CREATE_SETTER_GETTER(TiMediaPhotoGallery, setSuccess, getSuccess)
	TI_CREATE_SETTER_GETTER(TiMediaPhotoGallery, setCancel, getCancel)
	TI_CREATE_SETTER_GETTER(TiMediaPhotoGallery, setError, getError)
	TI_CREATE_SETTER_GETTER(TiMediaPhotoGallery, setMediaTypes, getMediaTypes);
	TI_CREATE_SETTER_GETTER(TiMediaPhotoGallery, setAllowEditing, getAllowEditing);

private:
	TiMediaPhotoGalleryEventHandler* _eventHandler;
	bb::cascades::pickers::FilePicker* _picker;
};

class TiMediaPhotoGalleryEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiMediaPhotoGalleryEventHandler(TiMediaPhotoGallery*);
	virtual ~TiMediaPhotoGalleryEventHandler();
	void setSuccessCallback(Ti::TiCallback*);
	void setCancelCallback(Ti::TiCallback*);
	void setErrorCallback(Ti::TiCallback*);
private:
	Ti::TiCallback* _success;
	Ti::TiCallback* _error;
	Ti::TiCallback* _cancel;
	TiMediaPhotoGallery* _proxy;
public slots:
	void onFileSelected(const QStringList&);
	void onCanceled();
};

} /* namespace TiMedia */
#endif /* TIMEDIAPHOTOGALLERY_H_ */
