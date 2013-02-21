

#ifndef CUNIT_H_
#define CUNIT_H_

#include <string>

#define ut_assert(message, test) do { if (!(test)) return message; } while (0)
#define ut_run_test(test) do { std::string message = test(); tests_run++; \
                                if (!message.empty()) return message; } while (0)

extern int tests_run;

std::string run_all_property_parser_tests();
std::string run_all_composite_layout_tests();
std::string run_all_horizontal_layout_tests();
std::string run_all_vertical_layout_tests();

#endif /* CUNIT_H_ */
