/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_PARSEPROPERTY_H_
#define TI_PARSEPROPERTY_H_

#include <string>
#include "Headers.h"

namespace Ti
{
namespace Layout
{
class ParseProperty
{
public:

	static double _computeValue(std::string value, enum ValueType valueType, double ppi);
	static void layoutPropertiesInitialize(struct LayoutProperties*);
	static void populateLayoutPoperties(struct InputProperty, struct LayoutProperties*, double);
	static float getDimensionValue(std::string value, double ppi);
};
}
}
#endif /* PARSEPROPERTY */
