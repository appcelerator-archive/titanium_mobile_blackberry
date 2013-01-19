

#include <stdio.h>
#include "CUnit.h"
#include "../ParseProperty.h"
#include "../Element.h"
#include "../Common.h"
#include "../Composite.h"

char* _test_measure_node() {
	struct LayoutProperties layoutProperties;
	layoutPropertiesInitialize(&layoutProperties);
	layoutProperties.top = {fixed, 0};
	layoutProperties.left = {fixed, 0};
	layoutProperties.width = {fixed, 500};
	layoutProperties.height = {fixed, 670};
	struct Element* element = createElement(composite);
	measureNodeForCompositeLayout(layoutProperties, element);
	ut_assert("error, layout coefficient x1", (*element)._layoutCoefficients.height.x1 == 0);
	ut_assert("error, layout coefficient x2", (*element)._layoutCoefficients.height.x2 == 0);
	ut_assert("error, layout coefficient x3", (*element)._layoutCoefficients.height.x3 == 0);
	return 0;
}

char* _test_composite_layout() {
	struct LayoutProperties layoutProperties;
	struct Element* e1 = createElement(composite); // Device - top level window
    layoutProperties.top = {fixed, 0};
    layoutProperties.left = {fixed, 0};
    layoutProperties.width = {fixed, 500};
    layoutProperties.height = {fixed, 670};
	struct Element* e2 = createElement(composite);
	measureNodeForCompositeLayout(layoutProperties, e2);
	layoutProperties.top = {undefined};
	layoutProperties.left = {undefined};
	layoutProperties.width = {fixed, 500};
	layoutProperties.height = {fixed, 500};
	struct Element* e3 = createElement(composite);
	addChildElement(e1, e2);
	addChildElement(e2, e3);
	doCompositeLayout((*e1)._children, 500, 670, false, false);
	return 0;
}

char* run_all_composite_layout_tests() {
	ut_run_test(_test_measure_node);
	ut_run_test(_test_composite_layout);
	return 0;
}
