/*
 * TiHelper.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Helper.h"

#include <bb/system/SystemDialog>
#include <bb/device/DisplayInfo>
#include <iostream>
#include "Layout/Structs.h"
#include "Layout/ParseProperty.h"
#include <QSettings>

static const QString FONT_FAMILY            = "fontFamily";
static const QString FONT_SIZE              = "fontSize";
static const QString FONT_STYLE             = "fontStyle";
static const QString FONT_STYLE_NORMAL      = "normal";
static const QString FONT_STYLE_ITALIC      = "italic";
static const QString FONT_WEIGHT            = "fontWeight";
static const QString FONT_WEIGHT_NORMAL     = "normal";
static const QString FONT_WEIGHT_BOLD       = "bold";
static float _ppi = -1;

float Ti::TiHelper::PPI()
{
	if(_ppi != -1) return _ppi;
	const float MMPERINCH = 25.4f;

	bb::device::DisplayInfo display;
	QSize pixelSize = display.pixelSize();
	QSizeF physicalSize = display.physicalSize();

	const float physicalWidth = physicalSize.width();
	const float physicalHeight = physicalSize.height();
	const float pixelWidth = pixelSize.width();
	const float pixelHeight = pixelSize.height();

	// Calculate pixels density
	const float diagonalWidth = sqrtf(physicalWidth * physicalWidth + physicalHeight * physicalHeight) / MMPERINCH;
	const float diagonalPixels = sqrtf(pixelWidth * pixelWidth + pixelHeight * pixelHeight);

	_ppi = diagonalPixels / diagonalWidth;
	return _ppi;
}

Handle<Value> Ti::TiHelper::Log(const Arguments &args)
{
    HandleScope scope;
    if(args.Length() > 0)
    {
    	Ti::TiHelper::Log(args[0]);
    }
    return scope.Close(Undefined());

}

void Ti::TiHelper::Log(QString str)
{
    qDebug() << "[INFO] " << str.toLocal8Bit().data();

}

Handle<Value> Ti::TiHelper::Log(Handle<Value> arg)
{
	qDebug() << "[INFO] " << *String::Utf8Value(arg);
    return Undefined();
}

Handle<Value> Ti::TiHelper::Alert(const Arguments &args)
{
    HandleScope scope;
    if(args.Length() > 0)
    {
    	bb::system::SystemDialog* alert = new bb::system::SystemDialog("OK");
    	alert->setTitle(QString("Alert"));
    	alert->setBody(QString(*String::Utf8Value(args[0])));
    	alert->show();
//    	alert->deleteLater();
    }
    return scope.Close(Undefined());

}

char* Ti::TiHelper::QStringToChar(QString str)
{
	return str.toLocal8Bit().data();
}

Handle<Value> Ti::TiHelper::ValueFromQString(QString str)
{
	return String::New(str.toLocal8Bit().constData());
}

QString Ti::TiHelper::QStringFromValue(Handle<Value> val)
{
	String::Utf8Value value(val);
	return QString(*value);
}

float Ti::TiHelper::FloatFromValue(Handle<Value> val)
{
	if(!val->IsNumber())
		return 0;
	Local<Number> num = val->ToNumber();
	return (float)num->Value();
}

void Ti::TiHelper::applyFontToText(Ti::TiValue value, bb::cascades::AbstractTextControl* control)
{
	if(!value.isMap()) return;
	QMap<QString, Ti::TiValue> map = value.toMap();

	if(map.contains(FONT_FAMILY))
	{
		Ti::TiValue fontFamily = map.value(FONT_FAMILY);
		control->textStyle()->setFontFamily(fontFamily.toString());
	}

	if(map.contains(FONT_SIZE))
	{
		Ti::TiValue fontSize= map.value(FONT_SIZE);
		float size = Ti::Layout::ParseProperty::_computeValue(fontSize.toString().toStdString(), Ti::Layout::Fixed, (double)Ti::TiHelper::PPI());
		size /= 3.5;
		if(size > 0)
		{
			control->textStyle()->setFontSize(bb::cascades::FontSize::PointValue);
			control->textStyle()->setFontSizeValue(size);
		}
	}

	if(map.contains(FONT_STYLE))
	{
		Ti::TiValue fontStyle = map.value(FONT_STYLE);
		QString style = fontStyle.toString();
		if(style == FONT_STYLE_NORMAL)
		{
            control->textStyle()->setFontStyle(bb::cascades::FontStyle::Normal);
		}
        else if (style == FONT_STYLE_ITALIC)
        {
        	control->textStyle()->setFontStyle(bb::cascades::FontStyle::Italic);
        }
	}

	if(map.contains(FONT_WEIGHT))
	{
		Ti::TiValue fontWeight = map.value(FONT_WEIGHT);
		QString weight = fontWeight.toString();
		if(weight == FONT_WEIGHT_NORMAL)
		{
            control->textStyle()->setFontWeight(bb::cascades::FontWeight::Normal);
		}
		else if(weight == FONT_WEIGHT_BOLD)
		{
            control->textStyle()->setFontWeight(bb::cascades::FontWeight::Bold);
		}
	}

}

bb::cascades::Color Ti::TiHelper::ColorFromObject(Handle<Value> obj)
{

    QString qcolorString = Ti::TiHelper::QStringFromValue(obj);
    if (!QColor::isValidColor(qcolorString))
    {
        return bb::cascades::Color::Yellow;
    }
    QColor qcolor(qcolorString);
    qreal qr, qg, qb, qa;
    qcolor.getRgbF(&qr, &qg, &qb, &qa);
    float r = qr;
    float g = qg;
    float b = qb;
    float a = qa;

	return bb::cascades::Color::fromRGBA(r, g, b, a);
}

QVariant Ti::TiHelper::getAppSetting(QString key) {
	QMap<QString, QVariant> settings = Ti::TiHelper::getAppSettings();
	return settings[key];
}

QMap<QString, QVariant> Ti::TiHelper::getAppSettings()
{
	static QMap<QString, QVariant> settings;
	if(settings.isEmpty())
	{
		QSettings defaultSettings("app/native/_private_assets_/app_properties.ini", QSettings::IniFormat);
		foreach(QString key, defaultSettings.allKeys())
		{
			settings[key] = defaultSettings.value(key);
		}
	}
	return settings;
}

QString Ti::TiHelper::getAssetPath(QString file)
{
	if(!file.startsWith("/")) {
		file.prepend("/");
	}

	QFileInfo privateAssets(QString("app/native/_private_assets_").append(file));
	if(privateAssets.exists()) {
		return privateAssets.filePath();
	}
	QFileInfo bbFolder(QString("app/native/assets/blackberry").append(file));
	if(bbFolder.exists()) {
		return bbFolder.filePath();
	}
	QFileInfo resourcesFolder(QString("app/native/assets").append(file));
	if(resourcesFolder.exists()) {
		return resourcesFolder.filePath();
	}
	return "";
}

