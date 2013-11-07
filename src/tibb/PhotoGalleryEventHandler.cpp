/*
 * PhotoGalleryEventHandler.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: penrique
 */

#include "PhotoGalleryEventHandler.h"
#include "TiBlobObject.h"
#include "TiObject.h"
#include "TiRootObject.h"
#include "TitaniumRuntime.h"
#include "V8Utils.h"
#include <bb/cascades/pickers/FilePicker>

using namespace titanium;
using namespace v8;

PhotoGalleryEventHandler::PhotoGalleryEventHandler(TiObject* obj) : _object(obj)
{
	_object->addRef();
	_picker = new bb::cascades::pickers::FilePicker();
	_picker->setType(bb::cascades::pickers::FileType::Picture);
	_picker->setTitle("Select Picture");
	_picker->setMode(bb::cascades::pickers::FilePickerMode::Picker);
	// Connect the fileSelected() signal with the slot.
	QObject::connect(_picker,  SIGNAL(fileSelected(const QStringList&)), this, SLOT(onFileSelected(const QStringList&)));
	// Connect the canceled() signal with the slot.
	QObject::connect(_picker, SIGNAL(canceled()), this,  SLOT(onCanceled()));
}

PhotoGalleryEventHandler::~PhotoGalleryEventHandler() {
	_object->release();
}

void PhotoGalleryEventHandler::showPicker() {
	_picker->open();
}

void PhotoGalleryEventHandler::onFileSelected(const QStringList& files)
{

    Local<Object> options = _object->getValue()->ToObject();


    TitaniumRuntime* runtime = TitaniumRuntime::instance();
    TiBlobObject* blob = TiBlobObject::createBlob(runtime->objectFactory());
    Handle<Object> blobProxy = runtime->rootObject()->createProxyObject();
	blob->setValue(blobProxy);
	TiObject::setTiObjectToJsObject(blobProxy, blob);

	QString mediaFile = files.at(0);
	blob->setData(mediaFile);

	Local<Object> data = Object::New();
	data->Set(String::NewSymbol("media"), blobProxy);
	Handle<Value> argv[1] = { data };
	CallV8ObjectProperty(options, "success", 1, argv);

}

void PhotoGalleryEventHandler::onCanceled()
{
    Local<Object> options = _object->getValue()->ToObject();
    CallV8ObjectProperty(options, "cancel", 0, 0);
}

/* Available in 10.2
void PhotoGalleryEventHandler::onError (bb::cascades::pickers::FilePickerError::Type error)
{
    Local<Object> data = Object::New();
//    QString errorMessage = message.data();
//    if (!errorMessage.isEmpty()) {
//        data->Set(String::NewSymbol("error"),
//                  String::New(errorMessage.toUtf8().constData()));
//    }
    Handle<Value> argv[1] = { data };
    CallV8ObjectProperty(options, "error", 1, argv);
}
*/
