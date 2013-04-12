
#include <stdio.h>
#include "tests/CUnit.h"

 int tests_run = 0;

int main(int argc, char** argv)
{
	 std::string result = run_all_property_parser_tests();
	 if (!result.empty()) {
		 printf("%s\n", result.c_str());
	 }
	 else {
		 printf("ALL PARSER TESTS PASSED\n");
	 }
	 printf("Tests run: %d\n", tests_run);

	 result = run_all_composite_layout_tests();
	 if (!result.empty()) {
		 printf("%s\n", result.c_str());
	 }
	 else {
		 printf("ALL COMPOSITE LAYOUT TESTS PASSED\n");
	 }

	 printf("Tests run: %d\n", tests_run);

	 result = run_all_horizontal_layout_tests();
	 if (!result.empty()) {
		 printf("%s\n", result.c_str());
	 }
	 else {
		 printf("ALL HORIZONTAL LAYOUT TESTS PASSED\n");
	 }
	 printf("Tests run: %d\n", tests_run);

	 /*
	 result = run_all_vertical_layout_tests();
	 if (!result.empty()) {
		 printf("%s\n", result.c_str());
	 }
	 else {
		 printf("ALL VERTICAL LAYOUT TESTS PASSED\n");
	 }

	 printf("Tests run: %d\n", tests_run);
	 */

    return 0;
}

