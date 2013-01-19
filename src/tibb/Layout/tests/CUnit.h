

#ifndef CUNIT_H_
#define CUNIT_H_

#define ut_assert(message, test) do { if (!(test)) return message; } while (0)
#define ut_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

extern int tests_run;

char* run_all_composite_layout_tests();
char* run_all_property_parser_tests();

#endif /* CUNIT_H_ */
