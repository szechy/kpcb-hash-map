#ifndef CONSTRUCT
#define CONSTRUCT

#include "test-struct.h"

static const char * construct_size_one_desc = "Make a hash map of size 1";
int construct_size_one();

static const char * construct_size_one_kb_desc = "Make a hash map of size 1,000";
int construct_size_one_kb();

static const char * construct_size_one_mb_desc = "Make a hash map of size 1,000,000";
int construct_size_one_mb();

#endif