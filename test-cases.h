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
static const char * set_million_desc = "Fill hash map of size 1,000,000 with 100,000 key-value pairs";
int set_million();

/* get(key, value) test cases */

/* delete(key, value) test cases */

/* load-factor test cases */

#endif