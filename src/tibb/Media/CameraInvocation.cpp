/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "CameraInvocation.h"

#include <bb/system/InvokeRequest>

using namespace bb::system;

namespace titanium {

CameraInvocation::CameraInvocation(TiObject* options)
      : options_(options)
      , visible_(false) {
    options_->addRef();
    connect(invokeManager_,
            SIGNAL(childCardDone(const bb::system::CardDoneMessage&)),
            SLOT(cameraCardDone(const bb::system::CardDoneMessage&)));
}

CameraInvocation::~CameraInvocation() {
    options_->release();
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
    invokeReply_ = invokeManager_->invoke(request);
}

void CameraInvocation::hide() {
}

void CameraInvocation::cameraCardReplyFinished() {
    Q_ASSERT(invokeReply_ && invokeReply_->isFinished());
    if (invokeReply_->error()) {
        // TODO: invoke "error" callback
        fprintf(stderr, "Error invoking camera card! %d\n", invokeReply_->error());
    }

    visible_ = true;

    // We don't need the reply anymore so free up memory.
    invokeReply_->deleteLater();
}

void CameraInvocation::cameraCardDone(const CardDoneMessage& message) {
    visible_ = false;
}

}  // namespace titanium

