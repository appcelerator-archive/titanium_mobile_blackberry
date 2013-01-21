
#include <stdio.h>
#include "CUnit.h"
#include "../ParseProperty.h"

std::string _test_layout_initialization() {
	struct LayoutProperties layoutProperties;
    layoutPropertiesInitialize(&layoutProperties);
	ut_assert("error, layout not initialized", layoutProperties.top.valueType == undefined);
	return "";
}

std::string _test_populate_layout() {
	// Need to calculate width and height. If empty it is either calculated by looking other properties or set to
	// default most often fill
	struct LayoutProperties layoutProperties;
	struct InputProperty inputProperty;
	inputProperty.name = top;
    inputProperty.value = "99px";
    populateLayoutPoperties(inputProperty, &layoutProperties, /*dpi*/ 96);
    ut_assert("error, layout not populated", layoutProperties.top.value == 99);
    return "";
}

std::string run_all_property_parser_tests() {
	ut_run_test(_test_layout_initialization);
	ut_run_test(_test_populate_layout);
	return "";
}

