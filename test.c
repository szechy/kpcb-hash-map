#include "unit-test-framework/unit_test_framework.h"
#include "test-cases.h"
#include <stdio.h>
#include <string.h>
#include "hash.h"

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
    run_test(set_one, set_one_desc);
    run_test(set_five, set_five_desc);
    run_test(set_five_with_colls, set_five_with_colls_desc);
    run_test(set_ten_with_colls, set_ten_with_colls_desc);
    run_test(set_million, set_million_desc);

  /* *** GET TESTS *** */
    run_test(get_one, get_one_desc);
    run_test(get_one_fail, get_one_fail_desc);
    run_test(get_ten, get_ten_desc);
    run_test(get_thousand, get_thousand_desc);
    run_test(get_million, get_million_desc);

  /* *** DELETE TESTS *** */
    run_test(delete_one_fail, delete_one_fail_desc);
    run_test(delete_one, delete_one_desc);
    run_test(delete_ten_with_fail, delete_ten_with_fail_desc);
    run_test(delete_thousand, delete_thousand_desc);
    run_test(delete_million, delete_million_desc);

  /* *** LOAD_FACTOR TESTS *** */
    run_test(load_one_empty, load_one_empty_desc);
    run_test(load_one_full, load_one_full_desc);
    run_test(load_ten, load_ten_desc);
    run_test(load_thousand, load_thousand_desc);
    run_test(load_million, load_million_desc);

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