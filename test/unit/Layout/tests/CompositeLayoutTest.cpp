

#include <stdio.h>
#include <math.h>
#include "CUnit.h"
#include "../ParseProperty.h"
#include "../Element.h"
#include "../Common.h"
#include "../Composite.h"

std::string _test_measure_composite_node_fill_properties() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	struct Element* element = createElement(composite);
	layoutProperties.width.valueType = fill;
	layoutProperties.width.value = NAN;
	layoutProperties.height.valueType = fill;
	layoutProperties.height.value = NAN;
	measureNodeForCompositeLayout(layoutProperties, element);
	// width height rule
	ut_assert("error, layout width coefficient x1", (*element)._layoutCoefficients.width.x1 == 1);
	ut_assert("error, layout width coefficient x2", (*element)._layoutCoefficients.width.x2 == 0);
	ut_assert("error, layout height coefficient x1", (*element)._layoutCoefficients.height.x1 == 1);
	ut_assert("error, layout height coefficient x2", (*element)._layoutCoefficients.height.x2 == 0);
	// min-width min-height rule
	ut_assert("error, layout min width coefficient x1", isNaN((*element)._layoutCoefficients.minWidth.x1));
	ut_assert("error, layout min width coefficient x2", isNaN((*element)._layoutCoefficients.minWidth.x2));
	ut_assert("error, layout min width coefficient x3", isNaN((*element)._layoutCoefficients.minWidth.x3));
	ut_assert("error, layout min height coefficient x1", isNaN((*element)._layoutCoefficients.minHeight.x1));
	ut_assert("error, layout min height coefficient x2", isNaN((*element)._layoutCoefficients.minHeight.x2));
	ut_assert("error, layout min height coefficient x3", isNaN((*element)._layoutCoefficients.minHeight.x3));
	// top left rule
	ut_assert("error, layout width coefficient x1", (*element)._layoutCoefficients.top.x1 == 0.5);
	ut_assert("error, layout width coefficient x2", (*element)._layoutCoefficients.top.x2 == -0.5);
	ut_assert("error, layout height coefficient x1", (*element)._layoutCoefficients.left.x1 == 0.5);
	ut_assert("error, layout height coefficient x2", (*element)._layoutCoefficients.left.x2 == -0.5);
	return "";
}

std::string _test_measure_composite_node() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	struct Element* element = createElement(composite);
	layoutProperties.width = {fixed, 100};
	layoutProperties.height = {fixed, 100};
	measureNodeForCompositeLayout(layoutProperties, element);
	// width height rule
	ut_assert("error, layout width coefficient x1", (*element)._layoutCoefficients.width.x1 == 0);
	ut_assert("error, layout width coefficient x2", (*element)._layoutCoefficients.width.x2 == 100);
	ut_assert("error, layout height coefficient x1", (*element)._layoutCoefficients.height.x1 == 0);
	ut_assert("error, layout height coefficient x2", (*element)._layoutCoefficients.height.x2 == 100);
	// min-width min-height rule
	ut_assert("error, layout min width coefficient x1", isNaN((*element)._layoutCoefficients.minWidth.x1));
	ut_assert("error, layout min width coefficient x2", isNaN((*element)._layoutCoefficients.minWidth.x2));
	ut_assert("error, layout min width coefficient x3", isNaN((*element)._layoutCoefficients.minWidth.x3));
	ut_assert("error, layout min height coefficient x1", isNaN((*element)._layoutCoefficients.minHeight.x1));
	ut_assert("error, layout min height coefficient x2", isNaN((*element)._layoutCoefficients.minHeight.x2));
	ut_assert("error, layout min height coefficient x3", isNaN((*element)._layoutCoefficients.minHeight.x3));
	// top left rule
	ut_assert("error, layout width coefficient x1", (*element)._layoutCoefficients.top.x1 == 0.5);
	ut_assert("error, layout width coefficient x2", (*element)._layoutCoefficients.top.x2 == -0.5);
	ut_assert("error, layout height coefficient x1", (*element)._layoutCoefficients.left.x1 == 0.5);
	ut_assert("error, layout height coefficient x2", (*element)._layoutCoefficients.left.x2 == -0.5);
	return "";
}

std::string _test_composite_layout() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	struct Element* e1 = createElement(composite); // Device - top level window
	layoutProperties.width.valueType = fill;
	layoutProperties.width.value = NAN;
	layoutProperties.height.valueType = fill;
	layoutProperties.height.value = NAN;
	struct Element* e2 = createElement(composite);
	measureNodeForCompositeLayout(layoutProperties, e2);
	layoutProperties.width = {fixed, 100};
	layoutProperties.height = {fixed, 100};
	struct Element* e3 = createElement(composite);
	measureNodeForCompositeLayout(layoutProperties, e3);
	addChildElement(e1, e2);
	addChildElement(e2, e3);
	doCompositeLayout((*e1)._children, 449, 662, false, false);
	ut_assert("error, absolute position top e2", (*e3)._measuredTop == 281);
	ut_assert("error, absolute position left e2", (*e3)._measuredLeft == 174.5);
	ut_assert("error, absolute width e2", (*e3)._measuredWidth == 100);
	ut_assert("error, absolute height e2", (*e3)._measuredHeight == 100);
	ut_assert("error, absolute position top e3", (*e2)._measuredTop == 0);
	ut_assert("error, absolute position left e3", (*e2)._measuredLeft == 0);
	ut_assert("error, absolute position width e3", (*e2)._measuredWidth == 449);
	ut_assert("error, absolute position height e3", (*e2)._measuredHeight == 662);
	return "";
}

std::string run_all_composite_layout_tests() {
	ut_run_test(_test_measure_composite_node_fill_properties);
	ut_run_test(_test_measure_composite_node);
	ut_run_test(_test_composite_layout);
	return "";
}
