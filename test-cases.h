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

#endif