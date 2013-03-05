/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEANNOTATIONOBJECT_H_
#define NATIVEANNOTATIONOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include "TiLogger.h"
#include "NativeMapViewObject.h"

namespace bb
{
namespace cascades
{
class ImageButton;
class ImageView;
class Container;
class Label;
}
}

class AnnotationObjectEventHandler;

class NativeAnnotationObject : public NativeControlObject
{
public:
    static NativeAnnotationObject* createAnnotationObject(TiObject* tiObject);
    virtual ~NativeAnnotationObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();

    // properties
    virtual int setPincolor(TiObject* obj);
    virtual int setLatitude(TiObject* obj);
	virtual int setLongitude(TiObject* obj);
	virtual int setTitle(TiObject* obj);
	virtual int setSubtitle(TiObject* obj);
	virtual int setLeftView(TiObject* obj);
	virtual int setRightView(TiObject* obj);

	bb::cascades::ImageButton* pin;
    bb::cascades::Container* bubble;
    bool showBubble;

    NativeMapViewObject* mapViewObj;

    float latitude;
    float longitude;

    static const int pinOffsetX = 20;
    static const int pinOffsetY = 58;
    static const int bubbleOffsetX = 105;
    static const int bubbleOffsetY = 225;

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeAnnotationObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeAnnotationObject(const NativeAnnotationObject&);
    void operator=(const NativeAnnotationObject&);

    QString pinImageSource_;
    bb::cascades::Label* label_;
    bb::cascades::ImageButton* leftView_;
    bb::cascades::ImageButton* rightView_;

    AnnotationObjectEventHandler* eventHandler_;
};

//Event handler for MAPview object
class AnnotationObjectEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit AnnotationObjectEventHandler(TiEventContainer* eventContainer, NativeAnnotationObject* annotationObject);
    virtual ~AnnotationObjectEventHandler();

public slots:
    void clicked();
    void leftViewClicked();
    void rightViewClicked();

private:
    TiEventContainer* eventContainer_;
    NativeAnnotationObject* annotationObject_;
    //bb::cascades::ImageButton *pin_;
    // Disable copy ctor & assignment operator
    AnnotationObjectEventHandler(const AnnotationObjectEventHandler& eHandler);
    AnnotationObjectEventHandler& operator=(const AnnotationObjectEventHandler& eHandler);
};


#endif /* NATIVEANNOTATIONOBJECT_H_ */
