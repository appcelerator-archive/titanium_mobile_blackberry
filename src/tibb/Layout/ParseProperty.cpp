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
		return size;
	}
	else if (value == "UI.FILL") {
		return fill;
	}
	else if (value.find("%") != std::string::npos) {
		return percent;
    }
    else {
    	return fixed;
    }
}

double _computeValue(std::string value, enum ValueType valueType) {
	std::string units;
	double parsedValue;
	int dpi = 96;

	if (valueType == percent) {
		return atof(value.c_str()) / 100;
	}
	else if (valueType == fixed) {
	  if ((value.find("mm") != std::string::npos) && (value.find("cm") != std::string::npos) &&
			  (value.find("em") != std::string::npos) && (value.find("pt") != std::string::npos) &&
			  (value.find("in") != std::string::npos) && (value.find("px") != std::string::npos) &&
			  (value.find("dp") != std::string::npos)) {
		  units = value.substr (value.size() - 2 , 2);
		  parsedValue = atof(value.substr(0, value.size() - 2).c_str());
	  }
	  else {
		  return atof(value.c_str());
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
	  else if (units == "dp") {
	  	  return parsedValue * dpi / 96;
	  }
	}
	else {
		return 0;
	}
}

void populateLayoutPoperties(struct InputProperty inputProperty, struct LayoutProperties* layoutProperties) {

	if (inputProperty.name == minHeight) {
		(*layoutProperties).minHeight.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).minHeight.value = _computeValue(inputProperty.value,
												(*layoutProperties).minHeight.valueType);
	}

	if (inputProperty.name == minWidth) {
		(*layoutProperties).minWidth.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).minWidth.value = _computeValue(inputProperty.value,
												(*layoutProperties).minWidth.valueType);
	}

	if (inputProperty.name == width) {
		(*layoutProperties).width.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).width.value = _computeValue(inputProperty.value,
												(*layoutProperties).width.valueType);
	}

	if (inputProperty.name == height) {
		(*layoutProperties).height.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).height.value = _computeValue(inputProperty.value,
												(*layoutProperties).height.valueType);
	}

	if (inputProperty.name == left) {
		(*layoutProperties).left.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).left.value = _computeValue(inputProperty.value,
												(*layoutProperties).left.valueType);
	}

	if (inputProperty.name == centerX) {
		(*layoutProperties).centerX.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).centerX.value = _computeValue(inputProperty.value,
												(*layoutProperties).centerX.valueType);
	}

	if (inputProperty.name == centerY) {
		(*layoutProperties).centerY.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).centerY.value = _computeValue(inputProperty.value,
												(*layoutProperties).centerY.valueType);
	}

	if (inputProperty.name == right) {
		(*layoutProperties).right.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).right.value = _computeValue(inputProperty.value,
												(*layoutProperties).right.valueType);
	}

	if (inputProperty.name == top) {
		(*layoutProperties).top.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).top.value = _computeValue(inputProperty.value,
												(*layoutProperties).top.valueType);
	}

	if (inputProperty.name == bottom) {
		(*layoutProperties).bottom.valueType = _getValueType(inputProperty.value);
		(*layoutProperties).bottom.value = _computeValue(inputProperty.value,
												(*layoutProperties).bottom.valueType);
	}
}

void layoutPropertiesInitialize(struct LayoutProperties* layoutProperties) {
	(*layoutProperties).top.valueType = undefined;
	(*layoutProperties).bottom.valueType = undefined;
	(*layoutProperties).left.valueType = undefined;
	(*layoutProperties).right.valueType = undefined;
	(*layoutProperties).width.valueType = undefined;
	(*layoutProperties).minWidth.valueType = undefined;
	(*layoutProperties).height.valueType = undefined;
	(*layoutProperties).minHeight.valueType = undefined;
	(*layoutProperties).centerX.valueType = undefined;
	(*layoutProperties).centerY.valueType = undefined;
}



