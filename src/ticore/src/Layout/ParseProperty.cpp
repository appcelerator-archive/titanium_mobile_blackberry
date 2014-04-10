/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <stdlib.h>
#include "Layout/Common.h"
#include "Layout/ParseProperty.h"
#include "Ti_Constants.h"
#include <string>


namespace Ti
{
namespace Layout
{

enum ValueType _getValueType(std::string value) {
	QString qVal(QString(value.c_str()));
	if (qVal == Ti::TiConstants::SizeSIZE) {
		return Size;
	}
	else if (qVal == Ti::TiConstants::SizeFILL) {
		return Fill;
	}
	else if (value.find("%") != std::string::npos) {
		return Percent;
    }
    else {
    	return Fixed;
    }
}

double ParseProperty::_computeValue(std::string value, enum ValueType valueType, double ppi) {
	std::string units;
	double parsedValue;

	if (valueType == Percent) {
		return atof(value.c_str()) / 100;
	}
	else if (valueType == Fixed) {
	  if ((value.find("mm") != std::string::npos) || (value.find("cm") != std::string::npos) ||
			  (value.find("em") != std::string::npos) || (value.find("pt") != std::string::npos) ||
			  (value.find("in") != std::string::npos) || (value.find("px") != std::string::npos) ||
			  (value.find("dp") != std::string::npos) || (value.find("dip") != std::string::npos)) {

		  if((value.find("dip") != std::string::npos)) {
			  units = value.substr (value.size() - 3 , 3);
			  parsedValue = atof(value.substr(0, value.size() - 3).c_str());
		  } else {
			  units = value.substr (value.size() - 2 , 2);
			  parsedValue = atof(value.substr(0, value.size() - 2).c_str());
		  }
	  }
	  else {
		  parsedValue = atof(value.c_str());
		  units = "dp";
	  }

	  if (units == "mm") {
		  return parsedValue /= 10;
	  }
	  else if (units == "cm") {
		  return parsedValue * 0.393700787 * ppi;
	  }
	  else if (units == "em" || units == "pt") {
		  return parsedValue /= 12;
	  }
	  else if (units == "pc") {
	  	  return parsedValue /= 6;
	  }
	  else if (units == "in") {
	  	  return parsedValue * ppi;
	  }
	  else if (units == "px") {
	  	  return parsedValue;
	  }
	  else if (units == "dp" || units == "dip") {
	  	  return parsedValue * (ppi / 160); // 160 - http://developer.blackberry.com/cascades/documentation/ui/webview/javascript.html
	  }
	}
	else {
		return 0;
	}
}

void ParseProperty::populateLayoutPoperties(struct InputProperty inputProperty, struct LayoutProperties* layoutProperties, double ppi) {

	switch (inputProperty.name) {
		case MinHeight:
			(*layoutProperties).minHeight.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).minHeight.value = _computeValue(inputProperty.value,
													(*layoutProperties).minHeight.valueType, ppi);
			break;
		case MinWidth:
			(*layoutProperties).minWidth.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).minWidth.value = _computeValue(inputProperty.value,
													(*layoutProperties).minWidth.valueType, ppi);
			break;
		case Width:
			(*layoutProperties).width.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).width.value = _computeValue(inputProperty.value,
													(*layoutProperties).width.valueType, ppi);
			break;
		case Height:
			(*layoutProperties).height.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).height.value = _computeValue(inputProperty.value,
													(*layoutProperties).height.valueType, ppi);
			break;
		case Left:
			(*layoutProperties).left.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).left.value = _computeValue(inputProperty.value,
													(*layoutProperties).left.valueType, ppi);
			break;
		case CenterX:
			(*layoutProperties).centerX.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).centerX.value = _computeValue(inputProperty.value,
													(*layoutProperties).centerX.valueType, ppi);
			break;
		case CenterY:
			(*layoutProperties).centerY.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).centerY.value = _computeValue(inputProperty.value,
													(*layoutProperties).centerY.valueType, ppi);
			break;
		case Right:
			(*layoutProperties).right.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).right.value = _computeValue(inputProperty.value,
													(*layoutProperties).right.valueType, ppi);
			break;
		case Top:
			(*layoutProperties).top.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).top.value = _computeValue(inputProperty.value,
													(*layoutProperties).top.valueType, ppi);
			break;
		case Bottom:
			(*layoutProperties).bottom.valueType = _getValueType(inputProperty.value);
			(*layoutProperties).bottom.value = _computeValue(inputProperty.value,
													(*layoutProperties).bottom.valueType, ppi);
			break;
	}
}

void ParseProperty::layoutPropertiesInitialize(struct LayoutProperties* layoutProperties) {
	(*layoutProperties).top.valueType = None;
	(*layoutProperties).bottom.valueType = None;
	(*layoutProperties).left.valueType = None;
	(*layoutProperties).right.valueType = None;
	(*layoutProperties).width.valueType = None;
	(*layoutProperties).minWidth.valueType = None;
	(*layoutProperties).height.valueType = None;
	(*layoutProperties).minHeight.valueType = None;
	(*layoutProperties).centerX.valueType = None;
	(*layoutProperties).centerY.valueType = None;
}

float ParseProperty::getDimensionValue(std::string value, double ppi) {
	ValueType type = _getValueType(value);
	return (float)_computeValue(value, type, ppi);
}

}
}
