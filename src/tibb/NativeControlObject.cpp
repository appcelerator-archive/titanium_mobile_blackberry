/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"

#include <stdlib.h>
#include <string.h>
#include <vector>

#include <QRectF>

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/LayoutUpdateHandler>
#include <bb/device/DisplayInfo>

#include "EventHandler.h"
#include "Layout/Composite.h"
#include "NativeLayoutHandler.h"
#include "PersistentV8Value.h"
#include "TiConstants.h"
#include "TiEventContainer.h"
#include "TiObject.h"
#include "V8Utils.h"
#include "TiUIAnimation.h"
#include "NativeAnimationObject.h"
#include "TiUtils.h"

using namespace bb::cascades;
using namespace titanium;

#define ZINDEX_PROPERTY_NAME            "tizindex"


#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeControlObject*, TiObject*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetProperties
{
public:
    SetGetProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetProperties()
    {
        if (setters_ != NULL)
        {
            delete[] setters_;
            setters_ = NULL;
        }
        if (getters_ != NULL)
        {
            delete[] getters_;
            getters_ = NULL;
        }
    }
    NATIVE_PROPSETGET_CALLBACK GetSetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    // Disabled default and copy constructors
    SetGetProperties();
    SetGetProperties(const SetGetProperties& prop);
    // Disabled assignment operator
    const SetGetProperties& operator = (const SetGetProperties& prop);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

class TouchEventHandler : public titanium::EventHandler {
    Q_OBJECT

public:
    TouchEventHandler(TiEventContainer* container)
        : titanium::EventHandler(container) { }

public slots:
    void onTouch(float x, float y) {
        TiEventContainer* container = getEventContainer();
        container->setDataProperty("x", x);
        container->setDataProperty("y", y);
        container->fireEvent();
    }
};

class FocusChangeEventHandler : public titanium::EventHandler {
    Q_OBJECT

public:
    FocusChangeEventHandler(TiEventContainer* container)
        : titanium::EventHandler(container) { }

public slots:
    void focusChanged() {
        getEventContainer()->fireEvent();
    }
};

#include "NativeControlObject.moc"

static void onPostLayout(struct Node* node) {
    NativeControlObject* native = static_cast<NativeControlObject*>(node->data);
    Control* control = static_cast<Control*>(native->getNativeHandle());
    if (!control) {
      // Cannot update layout until control has been created for the view.
      return;
    }

    if (node->properties.width.valueType == Defer || node->properties.height.valueType == Defer) {
    	return;
    }

    float width = node->element._measuredWidth,
          height = node->element._measuredHeight;

    // Do not allow a control with Ti.UI.SIZE to go to 0 or the OS will not callback deferred sizes as the controls are hidden.
	if ((node->properties.width.valueType == Size && width == 0) || (node->properties.height.valueType == Size && height == 0)) {
		return;
	}

    native->resize(width, height);

    bb::cascades::AbsoluteLayoutProperties* layoutProperties = static_cast<bb::cascades::AbsoluteLayoutProperties*>(control->layoutProperties());

    if (layoutProperties != NULL) {
    	layoutProperties->setPositionX(node->element._measuredLeft);
    	layoutProperties->setPositionY(node->element._measuredTop);
    }
}

NativeControlObject::NativeControlObject(TiObject* tiObject, NATIVE_TYPE objType) :
    NativeProxyObject(tiObject),
    container_(NULL),
    control_(NULL),
    layout_(NULL),
    layoutHandler_(0),
    batchUpdating_(false)
{
    nodeInitialize(&layoutNode_);
    layoutNode_.onLayout = onPostLayout;
    layoutNode_.data = this;

    if (objType == N_TYPE_VIEW || objType == N_TYPE_WEBVIEW || objType == N_TYPE_LIST_VIEW || objType == N_TYPE_SCROLL_VIEW || objType == N_TYPE_SCROLLABLE_VIEW) {
		layoutNode_.properties.defaultWidthType = Fill;
		layoutNode_.properties.defaultHeightType  = Fill;
    }
    else if (objType == N_TYPE_LABEL || objType == N_TYPE_BUTTON || objType == N_TYPE_TOGGLEBUTTON ||
        objType == N_TYPE_SLIDER || objType == N_TYPE_PROGRESSBAR || objType == N_TYPE_TEXT_FIELD ||
        objType == N_TYPE_ACTIVITYINDICATOR || objType == N_TYPE_WINDOW || objType == N_TYPE_MAPVIEW ||
        objType == N_TYPE_TEXT_AREA) {
        layoutNode_.properties.width.valueType = Defer;
        layoutNode_.properties.height.valueType = Defer;
    }

    objType_ = objType;

    TiUtils *tiUtils = TiUtils::getInstance();
    ppi_ = tiUtils->getPPI();

    bb::device::DisplayInfo display;
    displayWidth_ = display.pixelSize().width();
    displayHeight_ = display.pixelSize().height();
}

NativeControlObject::~NativeControlObject()
{
}

NativeControlObject* NativeControlObject::createView(TiObject* tiObject)
{
    return new NativeControlObject(tiObject, N_TYPE_VIEW);
}

NATIVE_TYPE NativeControlObject::getObjectType() const
{
    return objType_;
}

NAHANDLE NativeControlObject::getNativeHandle() const
{
    return container_;
}

void NativeControlObject::updateLayout(QRectF rect)
{
    bool requestLayout = false;
    rect_ = rect;

    if (rect.width() != 0 && layoutNode_.properties.width.valueType == Defer) {
        layoutNode_.properties.width.value = rect.width();
        layoutNode_.properties.width.valueType = Fixed;
        requestLayout = true;
    }

    if (rect.height() != 0 && layoutNode_.properties.height.valueType == Defer) {
        layoutNode_.properties.height.value = rect.height();
        layoutNode_.properties.height.valueType = Fixed;
        requestLayout = true;
    }

    if (requestLayout) {
        struct Node* root = nodeRequestLayout(&layoutNode_);
        if (root) {
        	root->element._measuredWidth = displayWidth_;
        	root->element._measuredHeight = displayHeight_;
            nodeLayout(root);
        }
    }
}

int NativeControlObject::initialize()
{
    /* Special case: UI.View only needs the container */
    setControl(NULL);
    return NATIVE_ERROR_OK;
}

void NativeControlObject::setContainer(bb::cascades::Container* container)
{
    container_ = container;
    container_->setImplicitLayoutAnimationsEnabled(false);
    container_->setLayout(new AbsoluteLayout());
    container_->setLayoutProperties(new AbsoluteLayoutProperties());

    // Listen for frame size updates on the container.
    layoutHandler_ = new NativeLayoutHandler(this);
    LayoutUpdateHandler::create(container_)
        .onLayoutFrameChanged(layoutHandler_,
	                      SLOT(handleLayoutFrameUpdated(QRectF)));
}

void NativeControlObject::setControl(bb::cascades::Control* control)
{
    if (container_ == NULL) {
        setContainer(new Container());
    }
    container_->add(control);
    control_ = control;
}

void NativeControlObject::addTouchEvent(const char* name, const QObject* source, const char* signal, TiEventContainer* container) {
    TouchEventHandler* handler = new TouchEventHandler(container);
    QObject::connect(source, signal, handler, SLOT(onTouch(float,float)));
    events_.insert(name, EventPairSmartPtr(container, handler));
}

void NativeControlObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);

    bb::cascades::Control* control = (control_ != NULL) ? control_ : container_;
    UIViewEventHandler* handler = new UIViewEventHandler(control);

    addTouchEvent("touchstart", handler, SIGNAL(touchStart(float,float)), containerFactory->createEventContainer());
    addTouchEvent("touchmove", handler, SIGNAL(touchMove(float,float)), containerFactory->createEventContainer());
    addTouchEvent("touchend", handler, SIGNAL(touchEnd(float,float)), containerFactory->createEventContainer());
    addTouchEvent("touchcancel", handler, SIGNAL(touchCancel(float,float)), containerFactory->createEventContainer());
    addTouchEvent("click", handler, SIGNAL(click(float,float)), containerFactory->createEventContainer());

    TiEventContainer* container = containerFactory->createEventContainer();
    FocusChangeEventHandler* focusHandler = new FocusChangeEventHandler(container);
    QObject::connect(handler, SIGNAL(focus()), focusHandler, SLOT(focusChanged()));
    events_.insert("focus", EventPairSmartPtr(container, focusHandler));

    container = containerFactory->createEventContainer();
    FocusChangeEventHandler* blurHandler = new FocusChangeEventHandler(container);
    QObject::connect(handler, SIGNAL(blur()), blurHandler, SLOT(focusChanged()));
    events_.insert("blur", EventPairSmartPtr(container, blurHandler));

}

int NativeControlObject::addChildNativeObject(NativeObject* obj)
{
    if (getObjectType() != N_TYPE_VIEW)
    {
        /* add not supported for children types */
        return NativeObject::addChildNativeObject(obj);
    }
    return addChildImpl(obj);
}

int NativeControlObject::addChildImpl(NativeObject* obj)
{
    Q_ASSERT(container_ != NULL);
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    nodeAddChild(&layoutNode_, &((NativeControlObject*) obj)->layoutNode_);
    struct Node* root = nodeRequestLayout(&layoutNode_);
    if (root) {
    	root->element._measuredWidth = displayWidth_;
    	root->element._measuredHeight = displayHeight_;
        nodeLayout(root);
    }
    TiObject* tmpObj = new TiObject;
    obj->getPropertyValue(N_PROP_ZINDEX, tmpObj);
    Handle<Value> zindex = tmpObj->getValue();
    float zindexValue = 0.0;
    if (zindex->IsNumber())
    {
        zindexValue = (float)(zindex->ToNumber()->Value());
    }
    tmpObj->release();
    int error = setZOrder(container_, control, zindexValue, zindex->IsNumber());
    return error;
}

int NativeControlObject::removeChildNativeObject(NativeObject* obj)
{
    if (getObjectType() != N_TYPE_VIEW)
    {
        /* remove not supported for children types */
        return NativeObject::removeChildNativeObject(obj);
    }
    return removeChildImpl(obj);
}

int NativeControlObject::removeChildImpl(NativeObject* obj)
{
    Q_ASSERT(container_ != NULL);
    nodeRemoveChild(&layoutNode_, &((NativeControlObject*) obj)->layoutNode_);
    struct Node* root = nodeRequestLayout(&layoutNode_);
    if (root) {
    	root->element._measuredWidth = displayWidth_;
    	root->element._measuredHeight = displayHeight_;
        nodeLayout(root);
    }
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    container_->remove(control);
    control->setParent(NULL);
    return NATIVE_ERROR_OK;
}

int NativeControlObject::setZOrder(bb::cascades::Container* container, bb::cascades::Control* control,
                                   float zindex, bool zindexIsDefined)
{
    Q_ASSERT(container != NULL);
    Q_ASSERT(control != NULL);
    container->remove(control);
    int childControls = container->count();
    int insertPosition = -1;
    for (int i = childControls; i > 0; i--)
    {
        bb::cascades::Control* child = container->at(i - 1);
        QVariant zqval = child->property(ZINDEX_PROPERTY_NAME);
        if (zindexIsDefined)
        {
            if (zqval.isValid())
            {
                bool conversionSucceeded = false;
                float childZValue = zqval.toFloat(&conversionSucceeded);
                if (!conversionSucceeded)
                {
                    return NATIVE_ERROR_INVALID_ARG;
                }
                if (zindex > childZValue)
                {
                    insertPosition = i;
                    break;
                }
            }
            else
            {
                insertPosition = i;
                break;
            }
        }
        else
        {
            if (!zqval.isValid())
            {
                break;
            }
            insertPosition = i;
        }
    }
    if (insertPosition < 0)
    {
        insertPosition = childControls;
    }
    container->insert(insertPosition, control);
    return NATIVE_ERROR_OK;
}

int NativeControlObject::setVisibility(bool visible)
{
    Q_ASSERT(container_ != NULL);
    container_->setVisible(visible);
    return NATIVE_ERROR_OK;
}

int NativeControlObject::startLayout()
{
    batchUpdating_ = true;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::finishLayout()
{
    if (batchUpdating_)
    {
        batchUpdating_ = false;
        //updateViewLayout();
    }
    return NATIVE_ERROR_OK;
}

void NativeControlObject::resize(float width, float height)
{
    Control* control = static_cast<Control*>(getNativeHandle());
    control->setMinWidth(width);
    control->setMaxWidth(width);
    control->setMinHeight(height);
    control->setMaxHeight(height);
}

void NativeControlObject::updateLayoutProperty(ValueName name, TiObject* val) {
    HandleScope handleScope;

    struct InputProperty property;
    property.name = name;
    property.value = *String::Utf8Value(val->getValue());

    populateLayoutPoperties(property, &layoutNode_.properties, ppi_);

    struct Node* root = nodeRequestLayout(&layoutNode_);
    if (root) {
    	root->element._measuredWidth = displayWidth_;
    	root->element._measuredHeight = displayHeight_;
        nodeLayout(root);
    }
}

// PROP_SETTER creates a static version of functions which
// calls the non-static on method on the NativeControlObject
// class.

PROP_SETGET(setAnchorPoint)
int NativeControlObject::setAnchorPoint(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    float x;
    float y;
    int error = NativeControlObject::getPoint(obj, &x, &y);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setPivotX(x);
    container_->setPivotY(y);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setBackgroundImage)
int NativeControlObject::setBackgroundImage(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);

    QString imagePath = V8ValueToQString(obj->getValue());
    imagePath = getResourcePath(imagePath);
    container_->setBackground(bb::cascades::ImagePaint(QUrl(imagePath)));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setBackgroundColor)
int NativeControlObject::setBackgroundColor(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    backgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (container_->isEnabled())
    {
        container_->setBackground(backgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setBackgroundDisableColor)
int NativeControlObject::setBackgroundDisableColor(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    disabledBackgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (!container_->isEnabled())
    {
        container_->setBackground(disabledBackgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setColor)
int NativeControlObject::setColor(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setData)
int NativeControlObject::setData(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setDisableBounce)
int NativeControlObject::setDisableBounce(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setEnabled)
int NativeControlObject::setEnabled(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    bool enabled;
    int error = getBoolean(obj, &enabled);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setEnabled(enabled);
    if (enabled)
    {
        container_->setBackground(backgroundColor_);
    }
    else
    {
        container_->setBackground(disabledBackgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setEnableZoomControls)
int NativeControlObject::setEnableZoomControls(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setFont)
int NativeControlObject::setFont(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setHeight)
int NativeControlObject::setHeight(TiObject* obj)
{
	// auto and Ti.UI.SIZE uses defaults that have already been set
	string str = *String::Utf8Value(obj->getValue());

	if ((str == "auto" || str == "UI.SIZE") && layoutNode_.properties.height.valueType == Defer) {
		return NATIVE_ERROR_OK;
	}

	updateLayoutProperty(Height, obj);

	return NATIVE_ERROR_OK;
}

PROP_SETGET(setHideLoadIndicator)
int NativeControlObject::setHideLoadIndicator(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setHintText)
int NativeControlObject::setHintText(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setHtml)
int NativeControlObject::setHtml(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setImage)
int NativeControlObject::setImage(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setKeyboardType)
int NativeControlObject::setKeyboardType(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLabel)
int NativeControlObject::setLabel(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLayout)
int NativeControlObject::setLayout(TiObject* obj)
{
    nodeSetLayoutType(&layoutNode_, *String::Utf8Value(obj->getValue()));
}

PROP_SETGET(setLoading)
int NativeControlObject::setLoading(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLeft)
int NativeControlObject::setLeft(TiObject* obj)
{
    updateLayoutProperty(Left, obj);

    return NATIVE_ERROR_OK;
}

PROP_SETGET(setLeftImage)
int NativeControlObject::setLeftImage(TiObject* obj) {
  return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setBottom)
int NativeControlObject::setBottom(TiObject* obj)
{
    updateLayoutProperty(Bottom, obj);

    return NATIVE_ERROR_OK;
}

PROP_SETGET(setButtonNames)
int NativeControlObject::setButtonNames(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setCancel)
int NativeControlObject::setCancel(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setRight)
int NativeControlObject::setRight(TiObject* obj)
{
    updateLayoutProperty(Right, obj);

    return NATIVE_ERROR_OK;
}

PROP_SETGET(setMax)
int NativeControlObject::setMax(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMinDate)
int NativeControlObject::setMinDate(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMaxDate)
int NativeControlObject::setMaxDate(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMin)
int NativeControlObject::setMin(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOpacity)
int NativeControlObject::setOpacity(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    if ((value < 0.0f) || (value > 1.0f))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    container_->setOpacity(value);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setOptions)
int NativeControlObject::setOptions(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOrientationModes)
int NativeControlObject::setOrientationModes(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPasswordMask)
int NativeControlObject::setPasswordMask(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPluginState)
int NativeControlObject::setPluginState(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setSelectedIndex)
int NativeControlObject::setSelectedIndex(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setScalesPageToFit)
int NativeControlObject::setScalesPageToFit(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setScrollsToTop)
int NativeControlObject::setScrollsToTop(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setShowScrollbars)
int NativeControlObject::setShowScrollbars(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setText)
int NativeControlObject::setText(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTextAlign)
int NativeControlObject::setTextAlign(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTitle)
int NativeControlObject::setTitle(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setUrl)
int NativeControlObject::setUrl(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setUserAgent)
int NativeControlObject::setUserAgent(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTop)
int NativeControlObject::setTop(TiObject* obj)
{
    updateLayoutProperty(Top, obj);

    return NATIVE_ERROR_OK;
}

PROP_SETGET(setValue)
int NativeControlObject::setValue(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setVisible)
int NativeControlObject::setVisible(TiObject* obj)
{
    bool visible;
    int error = getBoolean(obj, &visible);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    return setVisibility(visible);
}

PROP_SETGET(setWillHandleTouches)
int NativeControlObject::setWillHandleTouches(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getRect)
int NativeControlObject::getRect(TiObject* obj)
{
    Handle<Object> value = Object::New();
    value->Set(String::New("height"), Number::New(rect_.height()));
    value->Set(String::New("width"), Number::New(rect_.width()));
    value->Set(String::New("x"), Number::New(rect_.x()));
    value->Set(String::New("y"), Number::New(rect_.y()));
    obj->setValue(value);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getSize)
int NativeControlObject::getSize(TiObject* obj)
{
    Handle<Object> value = Object::New();
    value->Set(String::New("height"), Number::New(rect_.height()));
    value->Set(String::New("width"), Number::New(rect_.width()));
    value->Set(String::New("x"), Number::New(0));
    value->Set(String::New("y"), Number::New(0));
    obj->setValue(value);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setWidth)
int NativeControlObject::setWidth(TiObject* obj)
{
	// auto and Ti.UI.SIZE uses defaults that have already been set
	string str = *String::Utf8Value(obj->getValue());

	if ((str == "auto" || str == "UI.SIZE") && layoutNode_.properties.width.valueType == Defer) {
		return NATIVE_ERROR_OK;
	}

	updateLayoutProperty(Width, obj);

	return NATIVE_ERROR_OK;
}

PROP_SETGET(setContentWidth)
int NativeControlObject::setContentWidth(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setContentHeight)
int NativeControlObject::setContentHeight(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setType)
int NativeControlObject::setType(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setWindow)
int NativeControlObject::setWindow(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setWordWrap)
int NativeControlObject::setWordWrap(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setZIndex)
int NativeControlObject::setZIndex(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    container_->setProperty(ZINDEX_PROPERTY_NAME, QVariant(value));

    // In the case of the NativePageObject, the dynamic_cast will return NULL
    // as a Page is not a Container.  Setting zIndex on a Page doesn't make
    // sense and is not supported by Cascades.  We still return NATIVE_ERROR_OK
    // so the zIndex value is set on the JS object although it is ignored
    bb::cascades::Container* parent = dynamic_cast<bb::cascades::Container*>(container_->parent());
    if (parent != NULL)
    {
        error = setZOrder(parent, container_, value, true);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getZIndex)
int NativeControlObject::getZIndex(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    QVariant value = container_->property(ZINDEX_PROPERTY_NAME);
    if (value.isValid())
    {
        bool conversionSucceeded = false;
        float controlZValue = value.toFloat(&conversionSucceeded);
        if (!conversionSucceeded)
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        obj->setValue(Number::New(controlZValue));
    }
    else
    {
        obj->setValue(Undefined());
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_OK;
}


PROP_SETGET(setIcon)
int NativeControlObject::setIcon(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMessage)
int NativeControlObject::setMessage(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

// MapView properties
PROP_SETGET(setRegion)
int NativeControlObject::setRegion(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMapType)
int NativeControlObject::setMapType(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setAnnotations)
int NativeControlObject::setAnnotations(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setViews)
int NativeControlObject::setViews(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}
//////////////////////

// Annotation properties
PROP_SETGET(setPincolor)
int NativeControlObject::setPincolor(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLatitude)
int NativeControlObject::setLatitude(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLongitude)
int NativeControlObject::setLongitude(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setSubtitle)
int NativeControlObject::setSubtitle(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLeftView)
int NativeControlObject::setLeftView(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setRightView)
int NativeControlObject::setRightView(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}
/////////////////////////

// Media properties
PROP_SETGET(getPlaying)
int NativeControlObject::getPlaying(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getPaused)
int NativeControlObject::getPaused(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getRecording)
int NativeControlObject::getRecording(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getProgress)
int NativeControlObject::getProgress(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setBitRate)
int NativeControlObject::setBitRate(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setRepeatMode)
int NativeControlObject::setRepeatMode(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getVolume)
int NativeControlObject::getVolume(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setVolume)
int NativeControlObject::setVolume(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}
//////////////////////////

void NativeControlObject::focus() {
    if (control_) {
        control_->requestFocus();
    }
}

void NativeControlObject::blur() {
    if (control_) {
        control_->loseFocus();
    }
}

PROP_SETGET(setActive)
int NativeControlObject::setActive(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(isActive)
int NativeControlObject::isActive(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setDescription)
int NativeControlObject::setDescription(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setActiveTab)
int NativeControlObject::setActiveTab(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getActiveTab)
int NativeControlObject::getActiveTab(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setShowTabsOnActionBar)
int NativeControlObject::setShowTabsOnActionBar(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getTabs)
int NativeControlObject::getTabs(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

// ScrollableView
PROP_SETGET(setCurrentPage)
int NativeControlObject::setCurrentPage(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOverScrollMode)
int NativeControlObject::setOverScrollMode(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOverlayEnabled)
int NativeControlObject::setOverlayEnabled(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPagingControlAlpha)
int NativeControlObject::setPagingControlAlpha(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPagingControlColor)
int NativeControlObject::setPagingControlColor(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPagingControlHeight)
int NativeControlObject::setPagingControlHeight(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPagingControlOnTop)
int NativeControlObject::setPagingControlOnTop(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setPagingControlTimeout)
int NativeControlObject::setPagingControlTimeout(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setScrollingEnabled)
int NativeControlObject::setScrollingEnabled(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setShowPagingControl)
int NativeControlObject::setShowPagingControl(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

const static NATIVE_PROPSETGET_SETTING g_propSetGet[] =
{
    {N_PROP_ENABLE_ZOOM_CONTROLS, PROP_SETGET_FUNCTION(setEnableZoomControls), NULL},
    {N_PROP_HIDE_LOAD_INDICATOR, PROP_SETGET_FUNCTION(setHideLoadIndicator), NULL},
    {N_PROP_HTML, PROP_SETGET_FUNCTION(setHtml), NULL},
    {N_PROP_LOADING, PROP_SETGET_FUNCTION(setLoading), NULL},
    {N_PROP_PLUGIN_STATE, PROP_SETGET_FUNCTION(setPluginState), NULL},
    {N_PROP_SCALES_TO_FIT, PROP_SETGET_FUNCTION(setScalesPageToFit), NULL},
    {N_PROP_SCROLLS_TO_TOP, PROP_SETGET_FUNCTION(setScrollsToTop), NULL},
    {N_PROP_SHOW_SCROLL_BARS, PROP_SETGET_FUNCTION(setShowScrollbars), NULL},
    {N_PROP_USER_AGENT, PROP_SETGET_FUNCTION(setUserAgent), NULL},
    {N_PROP_WILL_HANDLE_TOUCHES, PROP_SETGET_FUNCTION(setWillHandleTouches), NULL},
    {N_PROP_ANCHOR_POINT, PROP_SETGET_FUNCTION(setAnchorPoint), NULL},
    {N_PROP_BACKGROUND_IMAGE, PROP_SETGET_FUNCTION(setBackgroundImage), NULL},
    {N_PROP_BACKGROUND_COLOR, PROP_SETGET_FUNCTION(setBackgroundColor), NULL},
    {N_PROP_BACKGROUND_DISABLED_COLOR, PROP_SETGET_FUNCTION(setBackgroundDisableColor), NULL},
    {N_PROP_BOTTOM, PROP_SETGET_FUNCTION(setBottom), NULL},
    {N_PROP_BUTTONNAMES, PROP_SETGET_FUNCTION(setButtonNames), NULL},
    {N_PROP_CANCEL, PROP_SETGET_FUNCTION(setCancel), NULL},
    {N_PROP_CONTENT_HEIGHT, PROP_SETGET_FUNCTION(setContentHeight), NULL},
    {N_PROP_CONTENT_WIDTH, PROP_SETGET_FUNCTION(setContentWidth), NULL},
    {N_PROP_COLOR, PROP_SETGET_FUNCTION(setColor), NULL},
    {N_PROP_DATA, PROP_SETGET_FUNCTION(setData), NULL},
    {N_PROP_ENABLED, PROP_SETGET_FUNCTION(setEnabled), NULL},
    {N_PROP_FONT, PROP_SETGET_FUNCTION(setFont), NULL},
    {N_PROP_HEIGHT, PROP_SETGET_FUNCTION(setHeight), NULL},
    {N_PROP_HINT_TEXT, PROP_SETGET_FUNCTION(setHintText), NULL},
    {N_PROP_ICON, PROP_SETGET_FUNCTION(setIcon), NULL},
    {N_PROP_IMAGE, PROP_SETGET_FUNCTION(setImage), NULL},
    {N_PROP_KEYBOARD_TYPE, PROP_SETGET_FUNCTION(setKeyboardType), NULL},
    {N_PROP_LABEL, PROP_SETGET_FUNCTION(setLabel), NULL},
    {N_PROP_LAYOUT, PROP_SETGET_FUNCTION(setLayout), NULL},
    {N_PROP_LEFT, PROP_SETGET_FUNCTION(setLeft), NULL},
    {N_PROP_LEFT_IMAGE, PROP_SETGET_FUNCTION(setLeftImage), NULL},
    {N_PROP_MAX, PROP_SETGET_FUNCTION(setMax), NULL},
    {N_PROP_MAXDATE, PROP_SETGET_FUNCTION(setMaxDate), NULL},
    {N_PROP_MESSAGE, PROP_SETGET_FUNCTION(setMessage), NULL},
    {N_PROP_MIN, PROP_SETGET_FUNCTION(setMin), NULL},
    {N_PROP_MINDATE, PROP_SETGET_FUNCTION(setMinDate), NULL},
    {N_PROP_OPACITY, PROP_SETGET_FUNCTION(setOpacity), NULL},
    {N_PROP_OPTIONS, PROP_SETGET_FUNCTION(setOptions), NULL},
    {N_PROP_ORIENTATION_MODES, PROP_SETGET_FUNCTION(setOrientationModes), NULL},
    {N_PROP_PASSWORD_MASK, PROP_SETGET_FUNCTION(setPasswordMask), NULL},
    {N_PROP_RECT, NULL, PROP_SETGET_FUNCTION(getRect)},
    {N_PROP_RIGHT, PROP_SETGET_FUNCTION(setRight), NULL},
    {N_PROP_SELECTED_INDEX, PROP_SETGET_FUNCTION(setSelectedIndex), NULL},
    {N_PROP_SIZE, NULL, PROP_SETGET_FUNCTION(getSize)},
    {N_PROP_TEXT, PROP_SETGET_FUNCTION(setText), NULL},
    {N_PROP_TEXT_ALIGN, PROP_SETGET_FUNCTION(setTextAlign), NULL},
    {N_PROP_TITLE, PROP_SETGET_FUNCTION(setTitle), NULL},
    {N_PROP_TOP, PROP_SETGET_FUNCTION(setTop), NULL},
    {N_PROP_TYPE, PROP_SETGET_FUNCTION(setType), NULL},
    {N_PROP_VALUE, PROP_SETGET_FUNCTION(setValue), NULL},
    {N_PROP_VISIBLE, PROP_SETGET_FUNCTION(setVisible), NULL},
    {N_PROP_WIDTH, PROP_SETGET_FUNCTION(setWidth), NULL},
    {N_PROP_WINDOW, PROP_SETGET_FUNCTION(setWindow), NULL},
    {N_PROP_WINDOW, PROP_SETGET_FUNCTION(setUrl), NULL},
    {N_PROP_WORD_WRAP, PROP_SETGET_FUNCTION(setWordWrap), NULL},
    {N_PROP_URL, PROP_SETGET_FUNCTION(setUrl), NULL},
    // MapView properties
    {N_PROP_MAPTYPE, PROP_SETGET_FUNCTION(setMapType), NULL},
    {N_PROP_REGION, PROP_SETGET_FUNCTION(setRegion), NULL},
    {N_PROP_ANNOTATIONS, PROP_SETGET_FUNCTION(setAnnotations), NULL},
    /////////////////////
    // Annotation properties
    {N_PROP_LATITUDE, PROP_SETGET_FUNCTION(setLatitude), NULL},
    {N_PROP_LONGITUDE, PROP_SETGET_FUNCTION(setLongitude), NULL},
    {N_PROP_SUBTITLE, PROP_SETGET_FUNCTION(setSubtitle), NULL},
    {N_PROP_PINCOLOR, PROP_SETGET_FUNCTION(setPincolor), NULL},
    {N_PROP_LEFTVIEW, PROP_SETGET_FUNCTION(setLeftView), NULL},
    {N_PROP_RIGHTVIEW, PROP_SETGET_FUNCTION(setRightView), NULL},
    ////////////////////////
    // Media properties
    {N_PROP_PLAYING,  NULL, PROP_SETGET_FUNCTION(getPlaying)},
    {N_PROP_PAUSED, NULL, PROP_SETGET_FUNCTION(getPaused)},
    {N_PROP_PROGRESS, NULL, PROP_SETGET_FUNCTION(getProgress)},
    {N_PROP_RECORDING, NULL, PROP_SETGET_FUNCTION(getRecording)},
    {N_PROP_BITRATE, PROP_SETGET_FUNCTION(setBitRate), NULL},
    {N_PROP_REPEATMODE, PROP_SETGET_FUNCTION(setRepeatMode), NULL},
    {N_PROP_VOLUME, PROP_SETGET_FUNCTION(setVolume),PROP_SETGET_FUNCTION(getVolume)},
    //////////////////////
    {N_PROP_ZINDEX, PROP_SETGET_FUNCTION(setZIndex), PROP_SETGET_FUNCTION(getZIndex)},

    // Tab properties
    {N_PROP_ACTIVE, PROP_SETGET_FUNCTION(setActive), PROP_SETGET_FUNCTION(isActive)},
    {N_PROP_DESCRIPTION, PROP_SETGET_FUNCTION(setDescription), NULL},

    // TabGroup properties
    {N_PROP_ACTIVE_TAB, PROP_SETGET_FUNCTION(setActiveTab), PROP_SETGET_FUNCTION(getActiveTab)},
    {N_PROP_TABS, NULL, PROP_SETGET_FUNCTION(getTabs)},
    {N_PROP_SHOW_TABS_ON_ACTION_BAR, PROP_SETGET_FUNCTION(setShowTabsOnActionBar), NULL},

    // ScrollableView
    {N_PROP_VIEWS, PROP_SETGET_FUNCTION(setViews), NULL},
    {N_PROP_CURRENT_PAGE, PROP_SETGET_FUNCTION(setCurrentPage), NULL},
    {N_PROP_DISABLE_BOUNCE, PROP_SETGET_FUNCTION(setDisableBounce), NULL},
    {N_PROP_OVER_SCROLL_MODE, PROP_SETGET_FUNCTION(setOverScrollMode), NULL},
    {N_PROP_OVERLAY_ENABLED, PROP_SETGET_FUNCTION(setOverlayEnabled), NULL},
    {N_PROP_PAGING_CONTROL_ALPHA, PROP_SETGET_FUNCTION(setPagingControlAlpha), NULL},
    {N_PROP_PAGING_CONTROL_COLOR, PROP_SETGET_FUNCTION(setPagingControlColor), NULL},
    {N_PROP_PAGING_CONTROL_HEIGHT, PROP_SETGET_FUNCTION(setPagingControlHeight), NULL},
    {N_PROP_PAGING_CONTROL_ON_TOP, PROP_SETGET_FUNCTION(setPagingControlOnTop), NULL},
    {N_PROP_PAGING_CONTROL_TIMEOUT, PROP_SETGET_FUNCTION(setPagingControlTimeout), NULL},
    {N_PROP_SCROLLING_ENABLED, PROP_SETGET_FUNCTION(setScrollingEnabled), NULL},
    {N_PROP_SHOW_PAGING_CONTROL, PROP_SETGET_FUNCTION(setShowPagingControl), NULL},
};

static SetGetProperties g_props(g_propSetGet, GET_ARRAY_SIZE(g_propSetGet));


int NativeControlObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeControlObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeControlObject::getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a)
{
    QString qcolorString = V8ValueToQString(obj->getValue());
    if (!QColor::isValidColor(qcolorString))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    QColor qcolor(qcolorString);
    qreal qr, qg, qb, qa;
    qcolor.getRgbF(&qr, &qg, &qb, &qa);
    *r = qr;
    *g = qg;
    *b = qb;
    *a = qa;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getBoolean(TiObject* obj, bool* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsBoolean()) && (!v8value->IsBooleanObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Boolean> b = v8value->ToBoolean();
    *value = b->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getFloat(TiObject* obj, float* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (float)num->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getInteger(TiObject* obj, int* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject()) && (!v8value->IsInt32())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (int)num->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getStringArray(TiObject* obj, QVector<QString>& value)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsArray())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Array> array = Handle<Array>::Cast(v8value);
    unsigned int uiLength = array->Length();
    for (unsigned int i = 0; i < uiLength; ++i)
    {
        Handle<Value> item = array->Get(Integer::New(i));
        if (item.IsEmpty() || ((!item->IsString()) && (!item->IsStringObject())))
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        String::Utf8Value v8UtfString(Handle<String>::Cast(item));
        const char* cStr = *v8UtfString;
        value.append(cStr);
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getObjectArray(TiObject* obj, QVector<NativeObject*>& value)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsArray())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Array> array = Handle<Array>::Cast(v8value);
    unsigned int uiLength = array->Length();
    for (unsigned int i = 0; i < uiLength; ++i)
    {
        Handle<Value> item = array->Get(Integer::New(i));
        if (item.IsEmpty() || !item->IsObject())
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        Handle<Object> v8obj = Handle<Object>::Cast(item);
        TiObject* tiObj = TiObject::getTiObjectFromJsObject(v8obj);
        value.append(tiObj->getNativeObject());
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getRegion(TiObject* obj, float* latitude, float* longitude)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || (!v8value->IsObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> v8obj = Handle<Object>::Cast(v8value);
    Handle<Value> v8lat = v8obj->Get(String::New("latitude"));
    if ((v8lat.IsEmpty()) || (!v8lat->IsNumber()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8lon = v8obj->Get(String::New("longitude"));
    if ((v8lon.IsEmpty()) || (!v8lon->IsNumber()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (latitude != NULL)
    {
        *latitude = (float)v8lat->ToNumber()->Value();
    }
    if (longitude != NULL)
    {
        *longitude = (float)v8lon->ToNumber()->Value();
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getPoint(TiObject* obj, float* x, float* y)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || (!v8value->IsObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> v8obj = Handle<Object>::Cast(v8value);
    Handle<Value> v8x = v8obj->Get(String::New("x"));
    if ((v8x.IsEmpty()) || (!v8x->IsNumber()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8y = v8obj->Get(String::New("y"));
    if ((v8y.IsEmpty()) || (!v8y->IsNumber()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (x != NULL)
    {
        *x = (float)v8x->ToNumber()->Value();
    }
    if (y != NULL)
    {
        *y = (float)v8y->ToNumber()->Value();
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getMapObject(TiObject* obj, QMap<QString, QString>& props)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsObject())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> object = Handle<Object>::Cast(v8value);
    Handle<Array> keys = object->GetPropertyNames();

    for (unsigned int i = 0; i < keys->Length(); i++)
    {
        v8::Handle<v8::String> key = keys->Get(v8::Integer::New(i))->ToString();
        v8::String::Utf8Value keyStr(key);
        v8::Handle<v8::String> value = object->Get(key)->ToString();
        v8::String::Utf8Value valueStr(value);
        QString strKey = QString::fromUtf8(*keyStr);
        QString strValue = QString::fromUtf8(*valueStr);

        props.insert(strKey, strValue);
    }

    return NATIVE_ERROR_OK;
}

int NativeControlObject::getDataModel(TiObject* obj, QVector<QVariant>& dataModel)
{
    Handle<Value> value = obj->getValue();
    if (value.IsEmpty() || (!value->IsArray()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    Handle<Array> array = Handle<Array>::Cast(value);
    uint32_t length = array->Length();
    dataModel.reserve(length);
    for (uint32_t i = 0; i < length; ++i)
    {
        Handle<Value> row = array->Get(i);
        PersistentV8Value v8Value(row);
        QVariant vRow = QVariant::fromValue(v8Value);
        dataModel.push_back(vRow);
    }

    return NATIVE_ERROR_OK;
}

int NativeControlObject::getDateTime(TiObject* obj, QDateTime& dt)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsDate()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    unsigned int year = 0, month = 0, day = 0;
    Local<Object> object = Object::Cast(*value);

    // Get year from date
    Local<Value> getYear_prop = (object->Get(String::New("getFullYear")));
    if (getYear_prop->IsFunction())
    {
        Local<Function> getYear_func = Function::Cast(*getYear_prop);
        Local<Value> yearValue = getYear_func->Call(object, 0, NULL);
        year = yearValue->NumberValue();
    }

    // Get month from date
    Local<Value> getMonth_prop = (object->Get(String::New("getMonth")));
    if (getMonth_prop->IsFunction())
    {
        Local<Function> getMonth_func = Function::Cast(*getMonth_prop);
        Local<Value> monthValue = getMonth_func->Call(object, 0, NULL);
        month = monthValue->NumberValue();
    }

    // Get day property
    Local<Value> getDay_prop = (object->Get(String::New("getDate")));
    if (getDay_prop->IsFunction())
    {
        Local<Function> getDay_func = Function::Cast(*getDay_prop);
        Local<Value> dayValue = getDay_func->Call(object, 0, NULL);
        day = dayValue->NumberValue();
    }
    dt.setDate(QDate(year, month, day));
    return NATIVE_ERROR_OK;
}

QString NativeControlObject::getResourcePath(const QString& path)
{
    if (path.isEmpty())
    {
        return "";
    }

    QString rPath;
    if (path[0] == '/')
    {
        //absolute path, just append assets from front
        rPath = "assets" + path;
    }
    else
    {
        if (TiObject::jsFilePath.rfind("/") == Ti::AssetsDir.size())
        {
            //js file is in the top dir (assets/) and image path is relative
            rPath = "assets/" + path;
        }
        else
        {
            //relative path of image from current js file
            std::string::size_type slashPos = TiObject::jsFilePath.rfind("/");
            if (slashPos != std::string::npos)
            {
                // remove app/native part from path
                int s = Ti::TopDir.size();
                std::string dir  = TiObject::jsFilePath.substr(s + 1, slashPos - s);
                rPath = QString((dir.c_str()) + path);
            }
        }
    }
    return rPath;
}


NativeAnimationObject * NativeControlObject::createAnimationObject(Local<Object> obj)
{
    NativeObjectFactory* factory = tiObject_->getNativeObjectFactory();
    TiUIAnimation* animation = TiUIAnimation::createAnimation(factory);
    TiObject *itemObject = static_cast<TiObject*>(animation);

    // Create a JavaScript proxy for the new animation object.
    Handle<ObjectTemplate> templ = TiObject::getObjectTemplateFromJsObject(tiObject_->getValue());
    Local<Object> proxy = templ->NewInstance();
    animation->setValue(proxy);
    TiObject::setTiObjectToJsObject(proxy, animation);

    // Apply the properties in the dictionary to the new animation object.
    animation->setParametersFromObject(animation, obj->ToObject());
    return (NativeAnimationObject *)animation->getNativeObject();
}

void NativeControlObject::animate(NativeObject* obj)
{
	NativeAnimationObject *animation = static_cast<NativeAnimationObject*>(obj);
	animation->animate(this, layoutNode_);
}

void NativeControlObject::animate(Local<Object> obj, TiV8Event* event)
{
	NativeAnimationObject *animation = createAnimationObject(obj);
	animation->setCallback(event);
	animation->animate(this, layoutNode_);

}

void NativeControlObject::animate(Local<Object> obj)
{
	NativeAnimationObject *animation = createAnimationObject(obj);
	animation->animate(this, layoutNode_);
}
