/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "CameraInvocation.h"

#include <bb/system/CardDoneMessage>
#include <bb/system/InvokeRequest>

#include "TiBlobObject.h"
#include "TiObject.h"
#include "TiRootObject.h"
#include "TitaniumRuntime.h"
#include "V8Utils.h"

using namespace bb::system;

namespace titanium {

CameraInvocation::CameraInvocation(TiObject* options)
      : options_(options)
      , visible_(false) {
    if (options_) {
        options_->addRef();
    }
    connect(&invokeManager_,
            SIGNAL(childCardDone(const bb::system::CardDoneMessage&)),
            SLOT(cameraCardDone(const bb::system::CardDoneMessage&)));
}

CameraInvocation::~CameraInvocation() {
    if (options_) {
        options_->release();
    }
}

void CameraInvocation::show() {
    if (invokeReply_ && !invokeReply_->isFinished()) {
        // Don't send another invoke request if one is already pending.
        return;
    }

    InvokeRequest request;
    request.setTarget("sys.camera.card");
    request.setAction("bb.action.CAPTURE");
    request.setData("photo");  // TODO: use CameraOptionsType.mediaTypes
    invokeReply_ = invokeManager_.invoke(request);
    if (!invokeReply_) {
        fprintf(stderr, "Failed to send camera card invoke\n");
        return;
    }

    connect(invokeReply_, SIGNAL(finished()), SLOT(cameraCardReplyFinished));
}

void CameraInvocation::hide() {
    if (!visible_) return;
    invokeManager_.closeChildCard();
}

void CameraInvocation::cameraCardReplyFinished() {
    Q_ASSERT(invokeReply_ && invokeReply_->isFinished());
    if (invokeReply_->error()) {
        // TODO: invoke "error" callback
        fprintf(stderr, "Error invoking camera card! %d\n", invokeReply_->error());
    }

    // Since there doesn't appear to be a way to query if
    // a card is visible directly, we'll consider a successful
    // reply as confirmation the card is now displayed on screen.
    visible_ = true;

    // We don't need the reply anymore so free up memory.
    invokeReply_->deleteLater();
}

void CameraInvocation::cameraCardDone(const CardDoneMessage& message) {
    // The camera card is now off screen so clear the visible flag.
    visible_ = false;

    QString reason = message.reason();
    Local<Object> options = options_->getValue()->ToObject();
    if (reason == "done") {
        // User closed the card without taking a picture or video.
        CallV8ObjectProperty(options, "cancel", 0, 0);
    } else if (reason == "close") {
        Local<Object> data = Object::New();
        QString errorMessage = message.data();
        if (!errorMessage.isEmpty()) {
            data->Set(String::NewSymbol("error"),
                      String::New(errorMessage.toUtf8().constData()));
        }
        Handle<Value> argv[1] = { data };
        CallV8ObjectProperty(options, "error", 1, argv);
    } else if (reason == "save") {
        TitaniumRuntime* runtime = TitaniumRuntime::instance();
        TiBlobObject* blob = TiBlobObject::createBlob(runtime->objectFactory());
        Handle<Object> blobProxy = runtime->rootObject()->createProxyObject();
        blob->setValue(blobProxy);
        TiObject::setTiObjectToJsObject(blobProxy, blob);

        QString mediaFile = message.data();
        blob->setData(mediaFile);

        Local<Object> data = Object::New();
        data->Set(String::NewSymbol("media"), blobProxy);
        Handle<Value> argv[1] = { data };
        CallV8ObjectProperty(options, "success", 1, argv);
    }
}

}  // namespace titanium

