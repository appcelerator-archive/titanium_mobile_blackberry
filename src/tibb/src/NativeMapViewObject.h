/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEMAPVIEWOBJECT_H_
#define NATIVEMAPVIEWOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>

namespace bb
{
namespace cascades
{
class ImageView;
namespace maps
{
class MapView;
}
}
}

class MapViewEventHandler;

class NativeMapViewObject : public NativeControlObject
{
public:
    static NativeMapViewObject* createMapView(TiObject* tiObject);
    virtual ~NativeMapViewObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();

    // properties
    virtual int setAnnotations(TiObject* obj);
    virtual int setRegion(TiObject* obj);

    // method
    bb::cascades::maps::MapView *getMapView();
    void updateMarkers();
    QPoint worldToPixel(float latitude, float longitude) const;
    void updateMap();
    int removeAnnotation(NativeObject* annotation);
    int addAnnotation(NativeObject* annotation);

    bool renderOkay;
    QTimer *timer;


protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeMapViewObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeMapViewObject(const NativeMapViewObject&);
    void operator=(const NativeMapViewObject&);

    QVector<NativeObject*> annotations_;
    bb::cascades::maps::MapView* mapview_;
    MapViewEventHandler* eventHandler_;
};

//Event handler for Mapview object
class MapViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit MapViewEventHandler(TiEventContainer* eventContainer, NativeMapViewObject* mapviewObject);
    virtual ~MapViewEventHandler();

public slots:
    void requestRender();
    void setRenderOkay();

private:
    TiEventContainer* eventContainer_;
    NativeMapViewObject* mapviewObject_;
    bb::cascades::maps::MapView *mapview_;
    // Disable copy ctor & assignment operator
    MapViewEventHandler(const MapViewEventHandler& eHandler);
    MapViewEventHandler& operator=(const MapViewEventHandler& eHandler);
    int cnt_;
};


#endif /* NATIVEMAPVIEWOBJECT_H_ */
