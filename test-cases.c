#include "hash.h"
#include "stdio.h"
// I'd really like to write my own version of assert that could somehow provide
// more diagnostic info, maybe another time
#include <assert.h>

/* CONSTRUCT TESTS */

/* Make a hash map of size -1. This is an edge case. 
 * BEHAVIOR: Return nullptr
 */
int construct_size_neg_one()
{
	hash * obj = construct_hash(-1);
	// null check
	assert(obj == 0);
	return 1;
}

/* Make a hash map of size 0. This is an edge case.
 * BEHAVIOR: returns pointer to hash with no space
 */
int construct_size_zero()
{
    hash * obj = construct_hash(0);

    // null check
    assert(obj != 0);

    // Check reported size
    assert(obj->size == 0);

    // Clean up hash
    delete_hash(obj);
    return 1;
}

/* Make a hash map of size 1. This is an edge case.
 * BEHAVIOR: Return pointer to hash struct with size 1
 */
int construct_size_one()
{
    hash * obj = construct_hash(1);

    // null check
    assert(obj != 0);

    // Check reported size
    assert(obj->size == 1);

    // Clean up hash
    delete_hash(obj);

    return 1;
}

/* Make a hash map of size 1. This is a small conventional use case.
 * BEHAVIOR: Return pointer to hash struct with size 1
 */
int construct_size_ten()
{
    hash * obj = construct_hash(10);

    // null check
    assert(obj != 0);

    // Check reported size
    assert(obj->size == 10);

    // Clean up hash
    delete_hash(obj);

    return 1;
}

/* Make a hash map of 1,000 objects. This is a conventional use case.
 * BEHAVIOR: Return pointer to hash struct with size 1KB
 */
int construct_size_one_kb()
{
    hash * obj = construct_hash(1000);

    // null check
    assert(obj != 0);

    // Check reported size
    assert(obj->size == 1000);

    // Clean up hash
    delete_hash(obj);

    return 1;
}

/* Make a hash map of 1,000,000 objects - a strain case.
 * BEHAVIOR: Return pointer to hash struct with size 1MB
 */

int construct_size_one_mb()
{
    hash * obj = construct_hash(1000000);

    // null check
    assert(obj != 0);

    // Check reported size
    assert(obj->size == 1000000);

    // Clean up hash
    delete_hash(obj);

    return 1;
}