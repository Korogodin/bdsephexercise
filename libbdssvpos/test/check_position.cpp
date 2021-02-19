
#include <check.h>

#include <libbdssvpos/kepler.h>
#include <libbdssvpos/bdssvpos.h>

#include <unistd.h>

START_TEST(test_add)
{
    fail_unless(add(1, 2) == 3,
                "1+2 should be 3");
}
END_TEST

START_TEST(test_mult)
{
    fail_unless(mult(2, 3) == 6,
                "2*3 should be 6");
}
END_TEST

Suite* position_suite(void) {
    Suite *s = suite_create("My test suite");

    TCase *tc_simple = tcase_create("Main tests");
    tcase_add_test(tc_simple, test_add);
    tcase_add_test(tc_simple, test_mult);
    suite_add_tcase(s, tc_simple);

    return s;
}
