#include "unit-test-framework/unit_test_framework.h"
#include "test-cases.h"

//extern char * construct_size_one_description;

void run_test(int (*fn)(void), const char * description);

int main(int argc, char const *argv[])
{
  // Describe the suite of tests to be run.
    start_suite("Unit tests");

  // Run some tests. Relying on assertions to find test failures.
  /* *** CONSTRUCT TESTS *** */
    run_test(construct_size_neg_one, construct_size_neg_one_desc);
    run_test(construct_size_zero, construct_size_zero_desc);
    run_test(construct_size_one, construct_size_one_desc);
    run_test(construct_size_ten, construct_size_ten_desc);
    run_test(construct_size_one_kb, construct_size_one_kb_desc);
    run_test(construct_size_one_mb, construct_size_one_mb_desc);

    /* *** SET TESTS *** */

  // End the suite
    end_suite();
    return 0;
}

void run_test(int (*fn)(void), const char * description) {
  test_description(description);
  if(fn())
    test_passed("");
  // not sure how we'd answer this case
  else
    test_failed("");
}