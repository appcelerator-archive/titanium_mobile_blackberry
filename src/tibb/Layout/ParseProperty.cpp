/*
 * Common.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#include <stdlib.h>
#include "Common.h"
#include "ParseProperty.h"
#include <string>

enum ValueType _getValueType(std::string value) {
	if (value == "UI.SIZE") {
		return Size;
	}
	else if (value == "UI.FILL") {
		return Fill;
	}
	else if (value.find("%") != std::string::npos) {
		return Percent;
    }
    else {
    	return Fixed;
    }
}

double _computeValue(std::string value, enum ValueType valueType, double dpi) {
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
		  return parsedValue * 0.393700787 * dpi;
	  }
	  else if (units == "em" || units == "pt") {
		  return parsedValue /= 12;
	  }
	  else if (units == "pc") {
	  	  return parsedValue /= 6;
	  }
	  else if (units == "in") {
	  	  return parsedValue * dpi;
	  }
	  else if (units == "px") {
	  	  return parsedValue;
	  }
	  else if (units == "dp" || units == "dip") {
	  	  return parsedValue * (336/96);
	  }
	}
	else {
		return 0;
	}
}

void populateLayoutPoperties(struct InputProperty inputProperty, struct LayoutProperties* layoutProperties, double dpi) {

	if (inputProperty.name == MinHeight) {
		(*layoutProperties).minHeight.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).minHeight.value = _computeValue(inputProperty.value,
												(*layoutProperties).minHeight.valueType, dpi);
	}

	if (inputProperty.name == MinWidth) {
		(*layoutProperties).minWidth.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).minWidth.value = _computeValue(inputProperty.value,
												(*layoutProperties).minWidth.valueType, dpi);
	}

	if (inputProperty.name == Width) {
		(*layoutProperties).width.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).width.value = _computeValue(inputProperty.value,
												(*layoutProperties).width.valueType, dpi);
	}

	if (inputProperty.name == Height) {
		(*layoutProperties).height.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).height.value = _computeValue(inputProperty.value,
												(*layoutProperties).height.valueType, dpi);
	}

	if (inputProperty.name == Left) {
		(*layoutProperties).left.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).left.value = _computeValue(inputProperty.value,
												(*layoutProperties).left.valueType, dpi);
	}

	if (inputProperty.name == CenterX) {
		(*layoutProperties).centerX.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).centerX.value = _computeValue(inputProperty.value,
												(*layoutProperties).centerX.valueType, dpi);
	}

	if (inputProperty.name == CenterY) {
		(*layoutProperties).centerY.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).centerY.value = _computeValue(inputProperty.value,
												(*layoutProperties).centerY.valueType, dpi);
	}

	if (inputProperty.name == Right) {
		(*layoutProperties).right.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).right.value = _computeValue(inputProperty.value,
												(*layoutProperties).right.valueType, dpi);
	}

	if (inputProperty.name == Top) {
		(*layoutProperties).top.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).top.value = _computeValue(inputProperty.value,
												(*layoutProperties).top.valueType, dpi);
	}

	if (inputProperty.name == Bottom) {
		(*layoutProperties).bottom.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).bottom.value = _computeValue(inputProperty.value,
												(*layoutProperties).bottom.valueType, dpi);
	}
}

void layoutPropertiesInitialize(struct LayoutProperties* layoutProperties) {
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



