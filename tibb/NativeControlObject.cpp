/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"

#include "NativeLayoutHandler.h"
#include "PersistentV8Value.h"
#include "TiEventContainer.h"
#include "TiConstants.h"
#include "TiObject.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/LayoutUpdateHandler>
#include <bb/device/Display>
#include <QColor>
#include <QRectF>

#define ZINDEX_PROPERTY_NAME            "tizindex"

// 25.4mm in 1"
#define INCHES_TO_MM_MUL                25.4f
// 10mm in 1cm
#define CM_TO_MM_MUL                    10.0f
// 72 points = 1" = 25.4mm
#define PT_TO_MM_MUL                    (INCHES_TO_MM_MUL / 72.0f)
// Default dots per mm
#define DPMM                            19.2f

// Width in pixels
static int g_width = 0;
// Height in pixels
static int g_height = 0;
// Width in mm
static float g_physicalWidth = 0.0f;
// Height in mm
static float g_physicalHeight = 0.0f;

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

// Unit types
struct UnitTypeData
{
    UnitType unitType;
    const char* postfix;
};

const static UnitTypeData g_unitTypes[] =
{
    {UnitTypePixels, "px"},
    {UnitTypePercent, "%"},
    {UnitTypeDIP, "dip"},
    {UnitTypeInches, "in"},
    {UnitTypeMM, "mm"},
    {UnitTypeCM, "cm"},
    {UnitTypePT, "pt"}
};

NativeControlObject::NativeControlObject(TiObject* tiObject) :
    NativeProxyObject(tiObject),
    container_(NULL),
    control_(NULL),
    layout_(NULL),
    layoutHandler_(0),
    bottom_(0),
    left_(0),
    top_(0),
    width_(0),
    height_(0),
    right_(0),
    batchUpdating_(false),
    heightIsUpdated(false),
    widthIsUpdated(false),
    leftIsUpdated(false),
    topIsUpdated(false),
    rightIsUpdated(false),
    bottomIsUpdate(false)
{
    if ((g_width <= 0) || (g_height <= 0))
    {
        bb::device::Display display;
        QSize size = display.pixelSize();
        g_width = size.width();
        g_height = size.height();
        QSizeF phySize = display.physicalSize();
        // Get size of screen if mm
        g_physicalWidth = (float)phySize.width();
        g_physicalHeight = (float)phySize.height();
        // NOTE: the previous functions do not work on the simulator
        if ((g_physicalWidth == 0.0f) || (g_physicalHeight == 0.0f))
        {
            // For now, try to guess what the physical size is.
            g_physicalWidth = (float)g_width / DPMM;
            g_physicalHeight = (float)g_height / DPMM;
        }
    }
}

NativeControlObject::~NativeControlObject()
{
}

NativeControlObject* NativeControlObject::createView(TiObject* tiObject)
{
    return new NativeControlObject(tiObject);
}

int NativeControlObject::getObjectType() const
{
    return N_TYPE_VIEW;
}

NAHANDLE NativeControlObject::getNativeHandle() const
{
    return container_;
}

void NativeControlObject::updateLayout(QRectF rect)
{
    rect_ = rect;
}

int NativeControlObject::initialize()
{
    /* Special case: UI.View only needs the container */
    setControl(NULL);
    return NATIVE_ERROR_OK;
}

void NativeControlObject::setControl(bb::cascades::Control* control)
{
    if (container_ == NULL)
    {
        container_ = bb::cascades::Container::create();
        container_->setLayout(new bb::cascades::AbsoluteLayout());
        layout_ = new bb::cascades::AbsoluteLayoutProperties;
        container_->setLayoutProperties(layout_);
    }
    container_->add(control);
    layoutHandler_ = new NativeLayoutHandler(this);
    bb::cascades::LayoutUpdateHandler::create(container_).onLayoutFrameChanged(layoutHandler_, SLOT(handleLayoutFrameUpdated(QRectF)));
    control_ = control;
}

void NativeControlObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new UIViewEventHandler(eventClick)));

    /* For pure containers connect the container signals, otherwise connect the control signals */
    bb::cascades::Control* connectCtrl = (control_ != NULL) ? control_ : container_;
    QObject::connect(connectCtrl, SIGNAL(touch(bb::cascades::TouchEvent*)),
                     events_[tetCLICK]->handler, SLOT(touch(bb::cascades::TouchEvent*)));
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
        return NativeObject::addChildNativeObject(obj);
    }
    return removeChildImpl(obj);
}

int NativeControlObject::removeChildImpl(NativeObject* obj)
{
    Q_ASSERT(container_ != NULL);
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    container_->remove(control);
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
        updateViewLayout();
    }
    return NATIVE_ERROR_OK;
}

void NativeControlObject::updateViewLayout()
{
    if (widthIsUpdated)
    {
        updateWidth();
        widthIsUpdated = false;
    }
    if (heightIsUpdated)
    {
        updateHeight();
        heightIsUpdated = false;
    }
    if (leftIsUpdated)
    {
        updateLeft();
        leftIsUpdated = false;
    }
    if (topIsUpdated)
    {
        updateTop();
        topIsUpdated = false;
    }
    if (rightIsUpdated)
    {
        updateRight();
        rightIsUpdated = false;
    }
    if (bottomIsUpdate)
    {
        updateBottom();
        bottomIsUpdate = false;
    }
    //TODO: need to verify if other UI.View properties needs to be updated as well
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

PROP_SETGET(setFont)
int NativeControlObject::setFont(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setHeight)
int NativeControlObject::setHeight(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (height_ != NULL)
    {
        height_->release();
    }
    height_ = obj;
    if (!batchUpdating_)
    {
        return updateHeight();
    }
    else
    {
        heightIsUpdated = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateHeight()
{
    if (height_ == NULL)
    {
        //height wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float height = 0;
    // TODO:we need the parent height to calculate percentage values and
    // to use that value as max instead of g_height
    float max = g_height; // TODO: Remove this
    int error = getMeasurementInfo(height_, max,
                                   (float)g_height / g_physicalHeight, &height);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setMaxHeight(height);
    container_->setMinHeight(height);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setHintText)
int NativeControlObject::setHintText(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setImage)
int NativeControlObject::setImage(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLabel)
int NativeControlObject::setLabel(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLeft)
int NativeControlObject::setLeft(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (left_ != NULL)
    {
        left_->release();
    }
    left_ = obj;
    if (!batchUpdating_)
    {
        return updateLeft();
    }
    else
    {
        leftIsUpdated = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateLeft()
{
    if (left_ == NULL)
    {
        //left wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float left = 0;
    int error = NativeControlObject::getFloat(left_, &left);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    layout_->setPositionX(left);
    container_->setLayoutProperties(layout_);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setBottom)
int NativeControlObject::setBottom(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (bottom_ != NULL)
    {
        bottom_->release();
    }
    bottom_ = obj;
    if (!batchUpdating_)
    {
        return updateBottom();
    }
    else
    {
        bottomIsUpdate = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateBottom()
{
    if (bottom_ == NULL)
    {
        //bottom wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float bottom = 0;
    int error = NativeControlObject::getFloat(bottom_, &bottom);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    container_->setBottomMargin(bottom);
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
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (right_ != NULL)
    {
        right_->release();
    }
    right_ = obj;
    if (batchUpdating_)
    {
        return updateRight();
    }
    else
    {
        rightIsUpdated = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateRight()
{
    if (right_ == NULL)
    {
        //right wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float right = 0;
    int error = NativeControlObject::getFloat(right_, &right);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    container_->setRightMargin(right);
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

PROP_SETGET(setSelectedIndex)
int NativeControlObject::setSelectedIndex(TiObject*)
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

PROP_SETGET(setTop)
int NativeControlObject::setTop(TiObject* obj)
{
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (top_ != NULL)
    {
        top_->release();
    }
    top_ = obj;
    if (!batchUpdating_)
    {
        return updateTop();
    }
    else
    {
        topIsUpdated = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateTop()
{
    if (top_ == NULL)
    {
        //top wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float top = 0;
    int error = NativeControlObject::getFloat(top_, &top);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    layout_->setPositionY(top);
    container_->setLayoutProperties(layout_);
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
    Q_ASSERT(container_ != NULL);
    Q_ASSERT(obj != NULL);
    obj->addRef();
    if (width_ != NULL)
    {
        width_->release();
    }
    width_ = obj;
    if (!batchUpdating_)
    {
        return updateWidth();
    }
    else
    {
        widthIsUpdated = true;
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::updateWidth()
{
    if (width_ == NULL)
    {
        //width wasn't set, just leave as it is
        return NATIVE_ERROR_OK;
    }
    float width = 0;
    // TODO:we need the parent width to calculate percentage values and
    // to use that value as max instead of g_height
    float max = g_width; // TODO: Remove this
    int error = getMeasurementInfo(width_, max,
                                   (float)g_width / g_physicalWidth, &width);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setMaxWidth(width);
    container_->setMinWidth(width);
    return NATIVE_ERROR_OK;
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
    bb::cascades::Container* parent = (bb::cascades::Container*)container_->parent();
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

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

const static NATIVE_PROPSETGET_SETTING g_propSetGet[] =
{
    {N_PROP_ANCHOR_POINT, PROP_SETGET_FUNCTION(setAnchorPoint), NULL},
    {N_PROP_BACKGROUND_COLOR, PROP_SETGET_FUNCTION(setBackgroundColor), NULL},
    {N_PROP_BACKGROUND_DISABLED_COLOR, PROP_SETGET_FUNCTION(setBackgroundDisableColor), NULL},
    {N_PROP_BOTTOM, PROP_SETGET_FUNCTION(setBottom), NULL},
    {N_PROP_BUTTONNAMES, PROP_SETGET_FUNCTION(setButtonNames), NULL},
    {N_PROP_CANCEL, PROP_SETGET_FUNCTION(setCancel), NULL},
    {N_PROP_COLOR, PROP_SETGET_FUNCTION(setColor), NULL},
    {N_PROP_DATA, PROP_SETGET_FUNCTION(setData), NULL},
    {N_PROP_ENABLED, PROP_SETGET_FUNCTION(setEnabled), NULL},
    {N_PROP_FONT, PROP_SETGET_FUNCTION(setFont), NULL},
    {N_PROP_HEIGHT, PROP_SETGET_FUNCTION(setHeight), NULL},
    {N_PROP_HINT_TEXT, PROP_SETGET_FUNCTION(setHintText), NULL},
    {N_PROP_ICON, PROP_SETGET_FUNCTION(setIcon), NULL},
    {N_PROP_IMAGE, PROP_SETGET_FUNCTION(setImage), NULL},
    {N_PROP_LABEL, PROP_SETGET_FUNCTION(setLabel), NULL},
    {N_PROP_LEFT, PROP_SETGET_FUNCTION(setLeft), NULL},
    {N_PROP_MAX, PROP_SETGET_FUNCTION(setMax), NULL},
    {N_PROP_MAXDATE, PROP_SETGET_FUNCTION(setMaxDate), NULL},
    {N_PROP_MESSAGE, PROP_SETGET_FUNCTION(setMessage), NULL},
    {N_PROP_MIN, PROP_SETGET_FUNCTION(setMin), NULL},
    {N_PROP_MINDATE, PROP_SETGET_FUNCTION(setMinDate), NULL},
    {N_PROP_OPACITY, PROP_SETGET_FUNCTION(setOpacity), NULL},
    {N_PROP_OPTIONS, PROP_SETGET_FUNCTION(setOptions), NULL},
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
    {N_PROP_ZINDEX, PROP_SETGET_FUNCTION(setZIndex), PROP_SETGET_FUNCTION(getZIndex)}
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
    QString qcolorString;
    int error = getString(obj, qcolorString);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
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

int NativeControlObject::getString(TiObject* obj, QString& str)
{
    Handle<Value> value = obj->getValue();
    if (value.IsEmpty())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (!value->IsString())
    {
        value = obj->getValue()->ToString();
    }
    Handle<String> v8string = Handle<String>::Cast(value);
    String::Utf8Value v8UtfString(v8string);
    const char* cStr = *v8UtfString;
    str = cStr;
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

int NativeControlObject::getPoint(TiObject* obj, float* x, float* y)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || (!v8value->IsObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> v8obj = Handle<Object>::Cast(v8value);
    Handle<Value> v8x = v8obj->Get(String::New("x"));
    if ((v8x.IsEmpty()) || (!v8x->IsNumber()) || (!v8x->IsNumberObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8y = v8obj->Get(String::New("y"));
    if ((v8y.IsEmpty()) || (!v8y->IsNumber()) || (!v8y->IsNumberObject()))
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

int NativeControlObject::getMeasurementInfo(TiObject* obj, float maxPixels, float dotsPerMillimeter,
        float* calculatedValue)
{
    Q_ASSERT(calculatedValue != NULL);
    UnitType unitType = UnitTypeDefault;
    if ((!obj->getValue()->IsString()) && (!obj->getValue()->IsStringObject()))
    {
        float value;
        int error = getFloat(obj, &value);
        if (error != NATIVE_ERROR_OK)
        {
            return error;
        }
        if (value < 0.0f)
        {
            value = 0.0f;
        }
        else if (value > maxPixels)
        {
            value = maxPixels;
        }
        *calculatedValue = value;
        return NATIVE_ERROR_OK;
    }
    v8::String::Utf8Value myString(obj->getValue()->ToString());
    QString measurement = (const char*)(*myString);
    float numberPart = (float)atof(*myString);
    for (int i = 0; i < GET_ARRAY_SIZE(g_unitTypes); i++)
    {
        if (measurement.endsWith(QString(g_unitTypes[i].postfix)))
        {
            unitType = g_unitTypes[i].unitType;
            break;
        }
    }
    if (unitType == UnitTypeDefault)
    {
        // Default to 'pixels'
        unitType = UnitTypePixels;
    }
    switch (unitType)
    {
    case UnitTypePixels:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        else if (numberPart > maxPixels)
        {
            numberPart = maxPixels;
        }
        *calculatedValue = numberPart;
        break;
    case UnitTypePercent:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        else if (numberPart > 100.0f)
        {
            numberPart = 100.0f;
        }
        if (maxPixels <= 0.0f)
        {
            *calculatedValue = 0;
        }
        else
        {
            *calculatedValue = maxPixels * numberPart / 100;
        }
        break;
    case UnitTypeDIP:
        // TODO: complete (NOTE: DPI is required)
        break;
    case UnitTypeInches:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        *calculatedValue = dotsPerMillimeter * numberPart * INCHES_TO_MM_MUL;
        break;
    case UnitTypeMM:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        *calculatedValue = dotsPerMillimeter * numberPart;
        break;
    case UnitTypeCM:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        *calculatedValue = dotsPerMillimeter * numberPart * CM_TO_MM_MUL;
        break;
    case UnitTypePT:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        *calculatedValue = dotsPerMillimeter * numberPart * PT_TO_MM_MUL;
        break;
    default:
        return NATIVE_ERROR_NOTSUPPORTED;
    }
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
