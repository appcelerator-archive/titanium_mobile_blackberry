/*
 * ParseProperty.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef PARSEPROPERTY_H_
#define PARSEPROPERTY_H_

#include <string>

enum ValueName {top = 0, bottom, left, right, width, minWidth, height, minHeight, centerX, centerY};
enum ValueType {fill = 1, size = 2, percent = 3, undefined = 4, fixed = 0};

struct InputProperty {
	enum ValueName name;
	std::string value;
};

struct layoutProp {
	// fill = UI.FILL, size = UI.SIZE, percent = values containing %, fixed = everything else
	enum ValueType valueType;
	float value;
};

struct LayoutProperties {
	struct layoutProp top;
	struct layoutProp bottom;
	struct layoutProp left;
	struct layoutProp right;
	struct layoutProp width;
	struct layoutProp minWidth;
	struct layoutProp height;
	struct layoutProp minHeight;
	struct layoutProp centerX;
	struct layoutProp centerY;
};

void layoutPropertiesInitialize(struct LayoutProperties*);
void populateLayoutPoperties(struct InputProperty, struct LayoutProperties);

#endif /* PARSEPROPERTY */
