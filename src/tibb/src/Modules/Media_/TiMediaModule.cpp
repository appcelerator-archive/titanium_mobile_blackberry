/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMediaModule.h"
#include "TiMediaAudioPlayerProxy.h"
#include "TiMediaPhotoGallery.h"
#include <bb/cascades/pickers/FileType>

using namespace TiMedia;
TiMediaModule::TiMediaModule(const char* name) :
	Ti::TiModule(name)
{
	addFunction("createAudioPlayer", TiMediaAudioPlayerProxy::CreateProxy);
	addFunction("createSound", TiMediaAudioPlayerProxy::CreateProxy);
	addFunction("openPhotoGallery", TiMediaPhotoGallery::CreateProxy);

	addNumber("MEDIA_TYPE_VIDEO", bb::cascades::pickers::FileType::Video);
	addNumber("MEDIA_TYPE_PHOTO", bb::cascades::pickers::FileType::Picture);

}

TiMediaModule::~TiMediaModule()
{

}
