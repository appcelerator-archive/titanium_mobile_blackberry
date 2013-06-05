/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_MEDIA_CAMERAINVOCATION_H
#define TI_MEDIA_CAMERAINVOCATION_H

#include <QObject>
#include <QPointer>

#include <bb/system/InvokeManager>
#include <bb/system/InvokeReply>

namespace titanium {

class TiObject;

// Presents the camera application card so the end user
// may take a picture. Once the picture is captured or
// the user cancels by closing the card the callbacks
// provided by the "options" object will be invoked.
// Only a single instance of this should be used since
// applications may only host a single card at a time.
class CameraInvocation : public QObject {
    Q_OBJECT

public:
    // Create a new camera invocation and provide
    // an "options" object that contains the properties
    // documented in the "CameraOptionsType" abstract type.
    explicit CameraInvocation(TiObject* options = NULL);

    virtual ~CameraInvocation();

    // Sends an invocation to display the camera card
    // so the user may take a picture. Once a picture has
    // been captured or the user cancels, the callbacks
    // in the "options" object will be invoked.
    void show();

    // Requests that the camera card be closed.
    void hide();

    // Returns true if the camera card is currently visible.
    bool isVisible() const {
        return visible_;
    }

private slots:
    void cameraCardReplyFinished();
    void cameraCardDone(const bb::system::CardDoneMessage& message);

private:
    bb::system::InvokeManager invokeManager_;
    QPointer<bb::system::InvokeReply> invokeReply_;
    TiObject* options_;
    bool visible_;
};

}  // namespace titanium

#endif
