/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMediaPhotoGallery.h"
#include <bb/cascades/pickers/FilePickerMode>
#include <TiCore.h>
#include <bb/cascades/pickers/FileType>

namespace TiMedia {

TiMediaPhotoGallery::TiMediaPhotoGallery(const char* name) : Ti::TiProxy(name)
{
	createPropertySetterGetter("success", _setSuccess,  _getSuccess);
	createPropertySetterGetter("cancel", _setCancel,  _getCancel);
	createPropertySetterGetter("error", _setError,  _getError);
	createPropertySetterGetter("mediaTypes", _setMediaTypes,  _getMediaTypes);
	createPropertySetterGetter("allowEditing", _setAllowEditing,  _getAllowEditing);

	_eventHandler = new TiMediaPhotoGalleryEventHandler(this);

	_picker = new bb::cascades::pickers::FilePicker();
	_picker->setType(bb::cascades::pickers::FileType::Picture);
	_picker->setTitle("Select Picture");
	_picker->setMode(bb::cascades::pickers::FilePickerMode::Picker);

	QObject::connect(_picker,  SIGNAL(fileSelected(const QStringList&)), _eventHandler, SLOT(onFileSelected(const QStringList&)));
	QObject::connect(_picker, SIGNAL(canceled()), _eventHandler,  SLOT(onCanceled()));
}

TiMediaPhotoGallery::~TiMediaPhotoGallery()
{
	delete _picker;
}

void TiMediaPhotoGallery::initEnd()
{
	Ti::TiProxy::initEnd();
	clearWeak();
	_picker->open();
}

TI_GETTER_DEFER(TiMediaPhotoGallery, getAllowEditing)
void TiMediaPhotoGallery::setAllowEditing(Ti::TiValue val)
{
	_picker->setImageCropEnabled(val.toBool());
}

TI_GETTER_DEFER(TiMediaPhotoGallery, getMediaTypes)
void TiMediaPhotoGallery::setMediaTypes(Ti::TiValue val)
{
	// todo: finish this:
	return;
	if(val.isList())
	{
		QList<Ti::TiValue> types = val.toList();
		bool hasPhoto = false;
		bool hasVideo = false;
		foreach(Ti::TiValue v, types) {
			if(v.toNumber() == bb::cascades::pickers::FileType::Picture)
			{
				hasPhoto = true;
			}
			if(v.toNumber() == bb::cascades::pickers::FileType::Video) {
				hasVideo = true;
			}
		}
		if(hasPhoto && !hasVideo) {
			_picker->setType(bb::cascades::pickers::FileType::Picture);
		}
		if(!hasPhoto && hasVideo) {
			_picker->setType(bb::cascades::pickers::FileType::Video);
		}
		if(hasPhoto && hasVideo) {
			_picker->setType(bb::cascades::pickers::FileType::Video | bb::cascades::pickers::FileType::Picture);
		}
	}
}

TI_GETTER_DEFER(TiMediaPhotoGallery, getSuccess)
void TiMediaPhotoGallery::setSuccess(Ti::TiValue val)
{
	_eventHandler->setSuccessCallback(new Ti::TiCallback(this, val));
}
TI_GETTER_DEFER(TiMediaPhotoGallery, getCancel)
void TiMediaPhotoGallery::setCancel(Ti::TiValue val)
{
	_eventHandler->setCancelCallback(new Ti::TiCallback(this, val));
}
TI_GETTER_DEFER(TiMediaPhotoGallery, getError)
void TiMediaPhotoGallery::setError(Ti::TiValue val)
{
	_eventHandler->setErrorCallback(new Ti::TiCallback(this, val));
}


TiMediaPhotoGalleryEventHandler::TiMediaPhotoGalleryEventHandler(TiMediaPhotoGallery* proxy)
{
	_proxy = proxy;
	_success = NULL;
	_error = NULL;
	_cancel = NULL;

}
TiMediaPhotoGalleryEventHandler::~TiMediaPhotoGalleryEventHandler()
{
	if(_success != NULL) delete _success;
	if(_cancel != NULL) delete _cancel;
	if(_error != NULL) delete _error;
}
void TiMediaPhotoGalleryEventHandler::setSuccessCallback(Ti::TiCallback* c)
{
	_success = c;
}
void TiMediaPhotoGalleryEventHandler::setCancelCallback(Ti::TiCallback* c)
{
	_cancel = c;
}
void TiMediaPhotoGalleryEventHandler::setErrorCallback(Ti::TiCallback* c)
{
	_error = c;
}

void TiMediaPhotoGalleryEventHandler::onFileSelected(const QStringList& files)
{
	if(_success != NULL) {
		bb::cascades::pickers::FilePicker* picker = static_cast<bb::cascades::pickers::FilePicker*>(sender());
		Ti::TiBlob *blob = Ti::TiBlob::InitWithFile(files.at(0));

		Ti::TiEventParameters cropRect;
		cropRect.addParam("x", 0);
		cropRect.addParam("y", 0);
		cropRect.addParam("width", blob->getWidth().toNumber());
		cropRect.addParam("height", blob->getHeight().toNumber());

		Ti::TiEventParameters params;
		params.addParam("media", blob);
		params.addParam("cropRect", cropRect);
		// todo: get the type
		params.addParam("mediaType", bb::cascades::pickers::FileType::Picture);// picker->type());

		_success->fire(params);
	}
	_proxy->makeWeak();
}
void TiMediaPhotoGalleryEventHandler::onCanceled()
{
	if(_cancel) {
		_cancel->fire(Ti::TiEventParameters());
	}
	_proxy->makeWeak();
}


} /* namespace TiMedia */
