

#include <stdio.h>
#include <math.h>
#include "CUnit.h"
#include "../Layout/ParseProperty.h"
#include "../Layout/Element.h"
#include "../Layout/Common.h"
#include "../Layout/Horizontal.h"

std::string _test_measure_horizontal_node_fill_properties() {
	return "";
}

std::string _test_measure_horizontal_node() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	struct Element* element = new Element();
	elementInitialize(element, Horizontal);
	layoutProperties.width = {Fixed, 50};
	layoutProperties.height = {Fixed, 20};
	measureNodeForHorizontalLayout(layoutProperties, element);
	// top left rule
	ut_assert("error, layout top coefficient x1", (*element)._layoutCoefficients.top.x1 == 0.0);
	ut_assert("error, layout top coefficient x2", (*element)._layoutCoefficients.top.x2 == 0.5);
	ut_assert("error, layout top coefficient x3", (*element)._layoutCoefficients.top.x3 == -0.5);
	ut_assert("error, layout top coefficient x4", (*element)._layoutCoefficients.top.x4 == 0.0);
	return "";
}

std::string _test_horizontal_layout() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	struct Element* e1 = new Element();
	elementInitialize(e1, Horizontal); // Device - top level window
	// e2
	layoutProperties.width = {Fixed, 50};
	layoutProperties.height = {Fixed, 20};
	struct Element* e2 = new Element();
	elementInitialize(e2, Composite);
	measureNodeForHorizontalLayout(layoutProperties, e2);
	// e3
	layoutProperties.width = {Fixed, 50};
	layoutProperties.height = {Fixed, 40};
	struct Element* e3 = new Element();
	elementInitialize(e3, Composite);
	measureNodeForHorizontalLayout(layoutProperties, e3);
	addChildElement(e1, e2);
	addChildElement(e1, e3);
	doHorizontalLayout((*e1)._children, 100, 100, false, false);
	ut_assert("error, absolute position top e2", (*e2)._measuredTop == 10);
	ut_assert("error, absolute position left e2", (*e2)._measuredLeft == 0);
	ut_assert("error, absolute position width e2", (*e2)._measuredWidth == 50);
	ut_assert("error, absolute position height e2", (*e2)._measuredHeight == 20);
	ut_assert("error, absolute position top e3", (*e3)._measuredTop == 0);
	ut_assert("error, absolute position left e3", (*e3)._measuredLeft == 50);
	ut_assert("error, absolute width e3", (*e3)._measuredWidth == 50);
	ut_assert("error, absolute height e3", (*e3)._measuredHeight == 40);
	return "";
}

std::string run_all_horizontal_layout_tests() {
	//ut_run_test(_test_measure_horizontal_node_fill_properties);
	ut_run_test(_test_measure_horizontal_node);
	ut_run_test(_test_horizontal_layout);
	return "";
}
