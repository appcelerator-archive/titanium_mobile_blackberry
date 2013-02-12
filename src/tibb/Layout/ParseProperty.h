/*
 * ParseProperty.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef PARSEPROPERTY_H_
#define PARSEPROPERTY_H_

#include <string>

enum ValueName {
    Top = 0, Bottom, Left, Right, Width, MinWidth, Height, MinHeight, CenterX, CenterY
};
enum ValueType {Fill = 1, Size = 2, Percent = 3, Defer = 4, Fixed = 0, None = -1};

struct InputProperty {
    ValueName name;
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
void populateLayoutPoperties(struct InputProperty, struct LayoutProperties*, double);

#endif /* PARSEPROPERTY */
