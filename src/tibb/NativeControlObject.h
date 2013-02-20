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
#include <bb/cascades/VisualNode>
#include <QRect>

#include <Layout/Node.h>


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

class NativeControlObject : public NativeProxyObject
{
public:
    static NativeControlObject* createView(TiObject* tiObject);
    virtual NATIVE_TYPE getObjectType() const;
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
    virtual int setBackgroundImage(TiObject* obj);
    virtual int setBackgroundColor(TiObject* obj);
    virtual int setBackgroundDisableColor(TiObject* obj);
    virtual int setBottom(TiObject* obj);
    virtual int setButtonNames(TiObject* obj);
    virtual int setCancel(TiObject* obj);
    virtual int setColor(TiObject* obj);
    virtual int setData(TiObject* obj);
    virtual int setDisableBounce(TiObject* obj);
    virtual int setEnabled(TiObject* obj);
    virtual int setEnableZoomControls(TiObject* obj);
    virtual int setFont(TiObject* obj);
    virtual int setHeight(TiObject* obj);
    virtual int setHideLoadIndicator(TiObject* obj);
    virtual int setHintText(TiObject* obj);
    virtual int setHtml(TiObject* obj);
    virtual int setIcon(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual int setLabel(TiObject* obj);
    virtual int setLayout(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setLeftImage(TiObject* obj);
    virtual int setLoading(TiObject* obj);
    virtual int setMax(TiObject* obj);
    virtual int setMaxDate(TiObject* obj);
    virtual int setMessage(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setMinDate(TiObject* obj);
    virtual int setOpacity(TiObject* obj);
    virtual int setOptions(TiObject* obj);
    virtual int setPasswordMask(TiObject* obj);
    virtual int setPluginState(TiObject* obj);
    virtual int setPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int setRight(TiObject* obj);
    virtual int setScalesPageToFit(TiObject* obj);
    virtual int setScrollsToTop(TiObject* obj);
    virtual int setShowScrollbars(TiObject* obj);
    virtual int setSelectedIndex(TiObject* obj);
    virtual int setText(TiObject* obj);
    virtual int setTextAlign(TiObject* obj);
    virtual int setTitle(TiObject* obj);
    virtual int setType(TiObject* obj);
    virtual int setTop(TiObject* obj);
    virtual int setUrl(TiObject* obj);
    virtual int setUserAgent(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setVisibility(bool visible);
    virtual int setVisible(TiObject* obj);
    virtual int setWidth(TiObject* obj);
    virtual int setWillHandleTouches(TiObject* obj);
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
    virtual void updateLayout(QRectF rect);

protected:
    explicit NativeControlObject(TiObject* tiObject, NATIVE_TYPE objType = N_TYPE_UNDEFINED);
    virtual ~NativeControlObject();
    virtual void setContainer(bb::cascades::Container* container);
    virtual void setControl(bb::cascades::Control* control);
    virtual void setupEvents(TiEventContainerFactory* containerFactory);
    int addChildImpl(NativeObject* obj);
    int removeChildImpl(NativeObject* obj);
    static int setZOrder(bb::cascades::Container* container, bb::cascades::Control* control,
                         float zindex, bool zindexIsDefined);
    static QString getResourcePath(const QString& path);

    struct Node layoutNode_;

private:
    friend class NativePageObject;
    friend class NativeWindowObject; // TODO(josh): we shouldn't have to abuse friends this way.

    void addTouchEvent(const char* name, const QObject* source, const char* signal, TiEventContainer* container);
    void updateLayoutProperty(ValueName name, TiObject* val);

    bb::cascades::Container* container_;
    bb::cascades::Control* control_;
    bb::cascades::AbsoluteLayoutProperties* layout_;
    bb::cascades::Color backgroundColor_;
    bb::cascades::Color disabledBackgroundColor_;
    NativeLayoutHandler* layoutHandler_;

    QRectF rect_;
    bool batchUpdating_;
    NATIVE_TYPE objType_;
};

// Event handler for Ti.UI.View
class UIViewEventHandler : public QObject {
    Q_OBJECT

public:
    explicit UIViewEventHandler(const bb::cascades::VisualNode* node) {
        QObject::connect(node, SIGNAL(touch(bb::cascades::TouchEvent*)),
                         this, SLOT(dispatchTouch(bb::cascades::TouchEvent*)));
        QObject::connect(node, SIGNAL(destroyed(QObject*)),
                         this, SLOT(onNodeDestroyed()));
    }

signals:
    void click(float x, float y);
    void touchStart(float x, float y);
    void touchMove(float x, float y);
    void touchEnd(float x, float y);
    void touchCancel(float x, float y);

private slots:
    void dispatchTouch(bb::cascades::TouchEvent* event) {
        float x = event->localX(),
              y = event->localY();

        // TODO(josh): Include coordinates of "click".
        // TODO(josh): Click should only happen with no movement (down & up).
        if (event->touchType() == bb::cascades::TouchType::Up) {
            emit click(x, y);
        }

        switch (event->touchType()) {
            case bb::cascades::TouchType::Down:
                emit touchStart(x, y);
                break;
            case bb::cascades::TouchType::Move:
                emit touchMove(x, y);
                break;
            case bb::cascades::TouchType::Up:
                emit touchEnd(x, y);
                break;
            case bb::cascades::TouchType::Cancel:
                emit touchCancel(x, y);
                break;
        }
    }

    void onNodeDestroyed() {
        // Release this event handler once the node is destroyed.
        delete this;
    }
};

#endif /* NATIVECONTROLOBJECT_H_ */
