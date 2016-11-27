#ifndef CONSTRUCT
#define CONSTRUCT

#include "test-struct.h"

/* construct test cases */
static const char * construct_size_neg_one_desc = "Attempt to make a hash map of size -1";
int construct_size_neg_one();
static const char * construct_size_zero_desc = "Make a hash map of size 0";
int construct_size_zero();
static const char * construct_size_one_desc = "Make a hash map of size 1";
int construct_size_one();
static const char * construct_size_ten_desc = "Make a hash map of size 10";
int construct_size_ten();
static const char * construct_size_one_kb_desc = "Make a hash map of size 1,000";
int construct_size_one_kb();
static const char * construct_size_one_mb_desc = "Make a hash map of size 1,000,000";
int construct_size_one_mb();

/* set(key, value) test cases */
static const char * set_one_desc = "Fill hash map of size 1 with one key-value pair";
int set_one();
static const char * set_five_desc = "Fill hash map of size 5 with 5 key-value pairs, no collisions";
int set_five();
static const char * set_five_with_colls_desc = "Fill hash map of size 5 with 5 key-value pairs, and two collisions";
int set_five_with_colls();
static const char * set_ten_with_colls_desc = "Fill hash map of size 10 with 10 key-value pairs, three collisions";
int set_ten_with_colls();
static const char * set_million_desc = "Fill hash map of size 1,000,000 with 950,000 key-value pairs";
int set_million();

/* get(key, value) test cases */
static const char * get_one_desc = "Retrieve one value from hash map";
int get_one();
static const char * get_one_fail_desc = "Fail to retrieve a value from hash map - invalid key";
int get_one_fail();
static const char * get_ten_desc = "Retrieve ten values from hash map";
int get_ten();
static const char * get_thousand_desc = "Retrieve 1000 values from hash map";
int get_thousand();
static const char * get_million_desc = "Retrieve 950,000 values from hash map";
int get_million();

/* delete(key, value) test cases */
static const char * delete_one_desc = "Delete one value from hash map";
int delete_one();
static const char * delete_one_fail_desc = "Fail to delete a value from hash map";
int delete_one_fail();
static const char * delete_ten_with_fail_desc = "Delete ten values from hash map";
int delete_ten_with_fail();
static const char * delete_thousand_desc = "Delete 1000 values from hash map";
int delete_thousand();
static const char * delete_million_desc = "Delete 950,000 values from hash map";
int delete_million();

/* load-factor test cases */
static const char * load_one_empty_desc = "Check load factor of tiny empty hash map";
int load_one_empty();
static const char * load_one_full_desc = "Check load factor of tiny full hash map";
int load_one_full();
static const char * load_ten_desc = "Check load factor of various hash map states of size 10";
int load_ten();
static const char * load_thousand_desc = "Check load factor of various hash map states of size 1,000";
int load_thousand();
static const char * load_million_desc = "Check load factor of various hash map states of size 950,000";
int load_million();

/* whole-cycle test cases - use all four functions */
static const char * whole_cycle_million_desc = "Set multiple times, get, delete, and check load factor of size 950,000";
int whole_cycle_million();


#endif
