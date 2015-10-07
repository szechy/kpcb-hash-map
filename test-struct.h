#ifndef TEST_STRUCT
#define TEST_STRUCT

typedef struct
{
	int (*test_fn)(void);
	const char * description;
	const char * success_message;
} test;

#endif
