/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeMapViewObject.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/maps/MapView>
#include <bb/cascades/ImageButton>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Container>
#include <TiObject.h>
#include <NativeAnnotationObject.h>
#include <bb/platform/geo/Point.hpp>
#include <QPoint>
#include "stdio.h"
using namespace bb::cascades;
using namespace bb::platform::geo;

NativeMapViewObject::NativeMapViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_MAPVIEW), renderOkay(false)
{
	mapview_ = NULL;
}

NativeMapViewObject::~NativeMapViewObject()
{
}

NativeMapViewObject* NativeMapViewObject::createMapView(TiObject* tiObject)
{
    return new NativeMapViewObject(tiObject);
}

NATIVE_TYPE NativeMapViewObject::getObjectType() const
{
    return N_TYPE_MAPVIEW;
}

int NativeMapViewObject::initialize()
{
    mapview_ = new bb::cascades::maps::MapView();
    mapview_->setAltitude(3000);
    mapview_->setTilt(0);


    setControl(mapview_);

    return NATIVE_ERROR_OK;
}

void NativeMapViewObject::updateMarkers()
{
	if (annotations_.size() > 0 && renderOkay) {
        for (int i = 0; i < annotations_.size(); i++) {
			NativeAnnotationObject* annotation = (NativeAnnotationObject*)annotations_[i];
			container_->remove(annotation->pin);
			container_->remove(annotation->bubble);
			container_->remove(annotation->bubbleContent);

			QPoint pt = worldToPixel(annotation->latitude, annotation->longitude);

			bb::cascades::AbsoluteLayoutProperties* layoutProperties = static_cast<bb::cascades::AbsoluteLayoutProperties*>(annotation->pin->layoutProperties());
			layoutProperties->setPositionX(pt.x() - annotation->pinOffsetX);
			layoutProperties->setPositionY(pt.y() - annotation->pinOffsetY);
			container_->add(annotation->pin);

			if (annotation->showBubble == true) {
				layoutProperties = static_cast<bb::cascades::AbsoluteLayoutProperties*>(annotation->bubble->layoutProperties());
				layoutProperties->setPositionX(pt.x() - annotation->bubbleOffsetX);
				layoutProperties->setPositionY(pt.y() - annotation->bubbleOffsetY);
				container_->add(annotation->bubble);

				layoutProperties = static_cast<bb::cascades::AbsoluteLayoutProperties*>(annotation->bubbleContent->layoutProperties());
				layoutProperties->setPositionX(pt.x() - annotation->bubbleContentOffsetX);
				layoutProperties->setPositionY(pt.y() - annotation->bubbleContentOffsetY);
				container_->add(annotation->bubbleContent);
			}
        }
	}
}

QPoint NativeMapViewObject::worldToPixel(float latitude, float longitude) const
{
	const Point worldCoordinates = Point(latitude, longitude);
    return QPoint(0,0); //mapview_->worldToWindow(worldCoordinates);
}

int NativeMapViewObject::setRegion(TiObject* obj)
{
	float latitude;
	float longitude;
	int error = NativeControlObject::getRegion(obj, &latitude, &longitude);
	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}
	mapview_->setLatitude(latitude);
	mapview_->setLongitude(longitude);


	return NATIVE_ERROR_OK;
}

int NativeMapViewObject::setAnnotations(TiObject* obj)
{
	int error = NativeControlObject::getObjectArray(obj, annotations_);
	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	// Todo do not go through array every time
	if (annotations_.size() > 0) {
		for (int i = 0; i < annotations_.size(); i++) {
			NativeAnnotationObject* annotation = (NativeAnnotationObject*)annotations_[i];
			annotation->mapViewObj = this;
		}
	}

	updateMap();

	return NATIVE_ERROR_OK;
}

int NativeMapViewObject::addAnnotation(NativeObject* annotation)
{
	annotations_.append(annotation);

	updateMap();

	return NATIVE_ERROR_OK;
}

int NativeMapViewObject::removeAnnotation(NativeObject* annotation)
{
	int pos = -1;
	int i = 0;
	for (; i < annotations_.size(); ++i) {
	     if ((NativeAnnotationObject*)annotations_.at(i) == (NativeAnnotationObject*)annotation) {
	         pos = i;
	         container_->remove(((NativeAnnotationObject*)annotations_.at(i))->pin);
	         container_->remove(((NativeAnnotationObject*)annotations_.at(i))->bubble);
	     }
	 }

	if (pos != -1) {
		annotations_.remove(pos);
	}

	updateMap();

	return NATIVE_ERROR_OK;
}

bb::cascades::maps::MapView* NativeMapViewObject::getMapView()
{
	return mapview_;
}

void NativeMapViewObject::updateMap()
{
	// Todo call the render to force an update
	mapview_->setTilt(1);
	mapview_->setTilt(0);
}

void NativeMapViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	eventHandler_ = new MapViewEventHandler(NULL, this);

	TiEventContainer* click = containerFactory->createEventContainer();
	click->setDataProperty("type", tetCLICK);
	events_.insert(tetCLICK, EventPairSmartPtr(click, new MapViewEventHandler(click, this)));

    QObject::connect(mapview_, SIGNAL(requestRender()), eventHandler_,  SLOT(requestRender()));

    timer = new QTimer(eventHandler_);
    QObject::connect(timer, SIGNAL(timeout()), eventHandler_,  SLOT(setRenderOkay()));
    timer->start(500);
}


MapViewEventHandler::MapViewEventHandler(TiEventContainer* eventContainer, NativeMapViewObject* mapviewObject)
{
    eventContainer_ = eventContainer;
    mapviewObject_ = mapviewObject;
    mapview_ = mapviewObject->getMapView();
    cnt_ = 0;
}

MapViewEventHandler::~MapViewEventHandler() {
}

void MapViewEventHandler::requestRender()
{
	mapviewObject_->updateMarkers();
}

void MapViewEventHandler::setRenderOkay() {

	// give the map some time to come up
	if (cnt_ >= 3) {
       mapviewObject_->renderOkay = true;
       mapviewObject_->timer->stop();
    }

    cnt_++;
   	mapviewObject_->updateMap();
}

