
#include <stdio.h>
#include "CUnit.h"
#include "../ParseProperty.h"

char* _test_layout_initialization() {
	struct LayoutProperties layoutProperties;
    layoutPropertiesInitialize(&layoutProperties);
	ut_assert("error, layout not initialized", layoutProperties.top.valueType == undefined);
	return 0;
}

char* _test_populate_layout() {
	struct LayoutProperties layoutProperties;
	struct InputProperty inputProperty;
	inputProperty.name = top;
    inputProperty.value = "99px";
    populateLayoutPoperties(inputProperty, &layoutProperties);
    ut_assert("error, layout not populated", layoutProperties.top.value == 99);
    return 0;
}

char* run_all_property_parser_tests() {
	ut_run_test(_test_layout_initialization);
	ut_run_test(_test_populate_layout);
	return 0;
}

