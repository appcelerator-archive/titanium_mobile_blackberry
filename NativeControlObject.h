/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTROLOBJECT_H_
#define NATIVECONTROLOBJECT_H_

#include "NativeObject.h"
#include <bb/cascades/Container>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>

/*
 * NativeControlObject
 *
 * Base class for all UI controls
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

class TiObject;
class QString;

class NativeControlObject : public NativeObject
{
public:
    virtual NAHANDLE getNativeHandle() const;
    virtual int setPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int getPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int setVisibility(bool visible);
    virtual int setAnchorPoint(TiObject* obj);
    virtual int setBackgroundColor(TiObject* obj);
    virtual int setBackgroundDisableColor(TiObject* obj);
    virtual int setColor(TiObject* obj);
    virtual int setData(TiObject* obj);
    virtual int setEnabled(TiObject* obj);
    virtual int setFont(TiObject* obj);
    virtual int setHeight(TiObject* obj);
    virtual int setHintText(TiObject* obj);
    virtual int setImage(TiObject* obj);
    virtual int setLabel(TiObject* obj);
    virtual int setLeft(TiObject* obj);
    virtual int setMax(TiObject* obj);
    virtual int setMaxDate(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setMinDate(TiObject* obj);
    virtual int setOpacity(TiObject* obj);
    virtual int setOptions(TiObject* obj);
    virtual int setRight(TiObject* obj);
    virtual int setSelectedIndex(TiObject* obj);
    virtual int setText(TiObject* obj);
    virtual int setTextAlign(TiObject* obj);
    virtual int setTitle(TiObject* obj);
    virtual int setType(TiObject* obj);
    virtual int setTop(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setVisible(TiObject* obj);
    virtual int getVisible(TiObject* obj);
    virtual int setWidth(TiObject* obj);
    static int getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a);
    static int getBoolean(TiObject* obj, bool* value);
    static int getString(TiObject* obj, QString& str);
    static int getFloat(TiObject* obj, float* value);
    static int getInteger(TiObject* obj, int* value);
    static int getStringArray(TiObject* obj, QVector<QString>& value);
    static int getMapObject(TiObject* obj, QMap<QString, QString>& props);
    static int getPoint(TiObject* obj, float* x, float* y);
    //obtain java script dictionary object and keep it in the multimap
    static int getDictionaryData(TiObject* obj, QVector<QPair<QString, QString> >& dictionary);

protected:
    NativeControlObject();
    virtual ~NativeControlObject();
    virtual void setControl(bb::cascades::Control* control);
    int getNextEventId();

private:
    static int getMeasurementInfo(TiObject* obj, float maxPixels, float dpMM,
                                  float* calculatedValue);

    bb::cascades::Container* container_;
    bb::cascades::Control* control_;
    bb::cascades::AbsoluteLayoutProperties* layout_;
    bb::cascades::Color backgroundColor_;
    bb::cascades::Color disabledBackgroundColor_;
    float left_;
    float top_;
    int nextEventId_;
};

#endif /* NATIVECONTROLOBJECT_H_ */
