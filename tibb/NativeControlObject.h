/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTROLOBJECT_H_
#define NATIVECONTROLOBJECT_H_

#include "NativeProxyObject.h"

#include <bb/cascades/Color>
#include <bb/cascades/TouchEvent>
#include <QRect>


class QString;
class TiObject;
class UIViewEventHandler;
class NativeLayoutHandler;

namespace bb
{
namespace cascades
{
class AbsoluteLayoutProperties;
class Container;
class Control;
}
}

/*
 * NativeControlObject
 *
 * Base class for all UI controls that are not dialogs, this class implements
 * the Native functionality of Ti.UI.View
 *
 * This class has dual functionality.
 *
 * 1. It implements the native View functionality inherited by all Ti classes
 * that extend UI.VIew.  This is done by managing an internal Container that
 * contains the actual control of the derived class.
 *
 * 2. It also can be instanciated on it's own when using Ti.UI.createView
 * In this case it's a pure container and the control_ member remains NULL
 * Ti.UI.Window is another such pure container case where the NativePageObject
 * has a Page instance that has the container_ from this class as content and
 * also a NULL control_.
 */

enum UnitType
{
    UnitTypeDefault,
    UnitTypePixels,
    UnitTypePercent,
    UnitTypeDIP,
    UnitTypeInches,
    UnitTypeMM,
    UnitTypeCM,
    UnitTypePT
};

class NativeControlObject : public NativeProxyObject
{
public:
    static NativeControlObject* createView(TiObject* tiObject);
    virtual int getObjectType() const;
    virtual NAHANDLE getNativeHandle() const;
    virtual int initialize();
    virtual int addChildNativeObject(NativeObject* obj);
    virtual int removeChildNativeObject(NativeObject* obj);
    virtual int finishLayout();
    virtual int getPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int getRect(TiObject* obj);
    virtual int getSize(TiObject* obj);
    virtual int getZIndex(TiObject* obj);
    virtual int setAnchorPoint(TiObject* obj);
    virtual int setBackgroundColor(TiObject* obj);
    virtual int setBackgroundDisableColor(TiObject* obj);
    virtual int setBottom(TiObject* obj);
    virtual int setButtonNames(TiObject* obj);
    virtual int setCancel(TiObject* obj);
    virtual int setColor(TiObject* obj);
    virtual int setData(TiObject* obj);
    virtual int setEnabled(TiObject* obj);
    virtual int setFont(TiObject* obj);
    virtual int setHeight(TiObject* obj);
    virtual int setHintText(TiObject* obj);
    virtual int setIcon(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual int setLabel(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setMax(TiObject* obj);
    virtual int setMaxDate(TiObject* obj);
    virtual int setMessage(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setMinDate(TiObject* obj);
    virtual int setOpacity(TiObject* obj);
    virtual int setOptions(TiObject* obj);
    virtual int setPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int setRight(TiObject* obj);
    virtual int setSelectedIndex(TiObject* obj);
    virtual int setText(TiObject* obj);
    virtual int setTextAlign(TiObject* obj);
    virtual int setTitle(TiObject* obj);
    virtual int setType(TiObject* obj);
    virtual int setTop(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setVisibility(bool visible);
    virtual int setVisible(TiObject* obj);
    virtual int setWidth(TiObject* obj);
    virtual int setWindow(TiObject* obj);
    virtual int startLayout();
    virtual int setZIndex(TiObject* obj);

    static int getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a);
    static int getBoolean(TiObject* obj, bool* value);
    static int getString(TiObject* obj, QString& str);
    static int getFloat(TiObject* obj, float* value);
    static int getInteger(TiObject* obj, int* value);
    static int getStringArray(TiObject* obj, QVector<QString>& value);
    static int getMapObject(TiObject* obj, QMap<QString, QString>& props);
    static int getPoint(TiObject* obj, float* x, float* y);
    static int getDataModel(TiObject* obj, QVector<QVariant>& dataModel);
    static int getDateTime(TiObject* obj, QDateTime& dt);
    void updateLayout(QRectF rect);

protected:
    explicit NativeControlObject(TiObject* tiObject);
    virtual ~NativeControlObject();
    virtual void setControl(bb::cascades::Control* control);
    virtual void setupEvents(TiEventContainerFactory* containerFactory);
    int addChildImpl(NativeObject* obj);
    int removeChildImpl(NativeObject* obj);
    static int setZOrder(bb::cascades::Container* container, bb::cascades::Control* control,
                         float zindex, bool zindexIsDefined);
    static QString getResourcePath(const QString& path);

private:
    friend class NativePageObject;
    static int getMeasurementInfo(TiObject* obj, float maxPixels, float dotsPerMillimeter,
                                  float* calculatedValue);
    void updateViewLayout();
    int updateHeight();
    int updateWidth();
    int updateLeft();
    int updateTop();
    int updateRight();
    int updateBottom();

    bb::cascades::Container* container_;
    bb::cascades::Control* control_;
    bb::cascades::AbsoluteLayoutProperties* layout_;
    bb::cascades::Color backgroundColor_;
    bb::cascades::Color disabledBackgroundColor_;
    NativeLayoutHandler* layoutHandler_;

    TiObject* bottom_;
    TiObject* left_;
    TiObject* top_;
    TiObject* width_;
    TiObject* height_;
    TiObject* right_;
    QRectF rect_;

    bool batchUpdating_;
    bool heightIsUpdated_;
    bool widthIsUpdated_;
    bool leftIsUpdated_;
    bool topIsUpdated_;
    bool rightIsUpdated_;
    bool bottomIsUpdated_;
};

// Event handler for Ti.UI.View
class UIViewEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit UIViewEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~UIViewEventHandler() {}

public slots:
    void touch(bb::cascades::TouchEvent* event)
    {
        if (event->touchType() == bb::cascades::TouchType::Up)
        {
            eventContainer_->fireEvent();
        }
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    UIViewEventHandler(const UIViewEventHandler& eHandler);
    UIViewEventHandler& operator=(const UIViewEventHandler& eHandler);
};

#endif /* NATIVECONTROLOBJECT_H_ */
