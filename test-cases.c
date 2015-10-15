#include "hash.h"
#include "stdio.h"
#include "stdlib.h"
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

/* Fill a hash map of size 1, with one key-value pair. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_one()
 {
    hash * obj = construct_hash(1);
    int j = 5;

    // Check that function reports it was placed
    assert(set(obj, "Test", (void *)&j));

    // Check that value actually exists in hash map
    //printf("%d\n", (int *)retrieveLocation(obj, 0));
    assert(*(int *)retrieveLocation(obj, 0) == 5);
    return 1;
 }

/* Fill a hash map of size 5, with 5 key-value pairs. No collisions. 
 * Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_five()
 {
    hash * obj = construct_hash(5);
    int a = 1, b = 2, c = 3, d = 4, e = 5;

    // Check that function reports it was placed
    // Keys chosen because they hash to different locations with no collisions
    assert(set(obj, "Test1", (void *)&a));
    assert(set(obj, "Test2", (void *)&b));
    assert(set(obj, "Test3", (void *)&c));
    assert(set(obj, "Test4", (void *)&d));
    assert(set(obj, "Test5", (void *)&e));

    // Check that value actually exists in hash map at proper location
    assert(*(int *)retrieveLocation(obj, 0) == 1);
    assert(*(int *)retrieveLocation(obj, 1) == 2);
    assert(*(int *)retrieveLocation(obj, 2) == 3);
    assert(*(int *)retrieveLocation(obj, 3) == 4);
    assert(*(int *)retrieveLocation(obj, 4) == 5);
    return 1;
 }

/* Fill a hash map of size 5, with 5 key-value pairs. Two collisions. 
 * Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_five_with_colls()
 {
    hash * obj = construct_hash(5);
    int a = 1, b = 2, c = 3, d = 4, e = 5;

    // Check that function reports it was placed
    // Keys chosen because they hash to different locations with no collisions
    assert(set(obj, "Test7", (void *)&a));   // hashes to 1
    assert(set(obj, "Test2", (void *)&b));  // hashes to 1, collides
    assert(set(obj, "Test12", (void *)&c)); // hashes to 0
    assert(set(obj, "Test500", (void *)&d));  // hashes to 4
    assert(set(obj, "Test25", (void *)&e)); // hashes to 4, collides

    // Check that value actually exists in hash map
    assert(*(int *)retrieveLocation(obj, 1) == 1);
    assert(*(int *)retrieveLocation(obj, 2) == 2);
    assert(*(int *)retrieveLocation(obj, 0) == 3);
    assert(*(int *)retrieveLocation(obj, 4) == 4);
    assert(*(int *)retrieveLocation(obj, 3) == 5);
    return 1;
 }

/* Fill a hash map of size 10, with 10 key-value pairs. 
 * Seven sets have at least one collision. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_ten_with_colls()
 {
    hash * obj = construct_hash(10);
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10;

    // Check that function reports it was placed
    // Keys chosen because they hash to different locations with no collisions
    assert(set(obj, "Test", (void *)&a));   // hashes to 6
    assert(set(obj, "Test2", (void *)&b));  // hashes to 6, coll to 7
    assert(set(obj, "Test12", (void *)&c)); // hashes to 0
    assert(set(obj, "Test5", (void *)&d));  // hashes to 9
    assert(set(obj, "Test25", (void *)&e)); // hashes to 9, to 0, 3
    assert(set(obj, "Test50", (void *)&f)); // hashes to 2
    assert(set(obj, "Test32", (void *)&g)); // hashes to 2, to 3, 6, 1
    assert(set(obj, "Test63", (void *)&h)); // hashes to 1, to 2, 5
    // Looking at the sheer number of collisions for the set below is real-life
    // evidence to me that prime-number-sized hash maps are important!
    assert(set(obj, "Test27", (void *)&i)); // hashes to 1, lots of colls to 4
    assert(set(obj, "Test42", (void *)&j)); // hashes to 8


    // Check that value actually exists in hash map
    //printf("%d\n", (int *)retrieveLocation(obj, 0));
    assert(*(int *)retrieveLocation(obj, 6) == 1);
    assert(*(int *)retrieveLocation(obj, 7) == 2);
    assert(*(int *)retrieveLocation(obj, 0) == 3);
    assert(*(int *)retrieveLocation(obj, 9) == 4);
    assert(*(int *)retrieveLocation(obj, 3) == 5);
    assert(*(int *)retrieveLocation(obj, 2) == 6);
    assert(*(int *)retrieveLocation(obj, 1) == 7);
    assert(*(int *)retrieveLocation(obj, 5) == 8);
    assert(*(int *)retrieveLocation(obj, 4) == 9);
    assert(*(int *)retrieveLocation(obj, 8) == 10);    
    return 1;
 }

/* Fill a hash map of size 1,000,000, with 100,000 key-value pairs. 
 * Likely to be a lot of collisions. Stress test case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_million()
 {
    hash * obj = construct_hash(1000000);

    int i = 100000;
    int * number;
    char string[50];
    for(; i >= 0; i--)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        number = (int *) malloc(sizeof(int));
        *number = rand();
        assert(set(obj, string, (void *)number));
    }

    return 1;
}

/* Retrieve one value from a hash map - conventional use case.
 * BEHAVIOR: Return 1, with successful retrieval
 */
int get_one()
{
    hash * obj = construct_hash(10);
    int * number = malloc(sizeof(int));
    *number = 15;
    assert(set(obj, "TestKey", (void *)number));

    assert(*(int *)get(obj, "TestKey") == *number);

    return 1;
}

/* Fail to retrieve one value from a hash map, because no keys map there
 * BEHAVIOR: get() returns nullptr, with unsuccessful retrieval
 */
 int get_one_fail()
 {
    hash * obj = construct_hash(10);

    int * number = malloc(sizeof(int));
    *number = 27;
    assert(set(obj, "TestKey", (void *) number));
    assert(get(obj, "DifferentKey") == 0);

    return 1;
 }

/* Retrieve ten values properly, and five values failing
 * BEHAVIOR: Successfully retrieve ten, and fail to retrieve five
 */
 int get_ten()
 {
    hash * obj = construct_hash(10);

    int i = 9;
    int * number;
    char string[50];
    for(; i >= 0; i--)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        number = (int *) malloc(sizeof(int));
        *number = i;
        assert(set(obj, string, (void *)number));
    }

    // find valid values
    for(i = 0; i < 10; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        assert(*(int *)get(obj, string) == i);
    }

    // fail on finding five
    assert(get(obj, "Test11") == 0);
    assert(get(obj, "Test12") == 0);
    assert(get(obj, "Test21") == 0);
    assert(get(obj, "Test23") == 0);
    assert(get(obj, "Test42") == 0);

    return 1;
 }

/* Retrieve 1,000 values perfectly, and fail on 1,000.
 * Behavior: Successfully retrieve 1,000 - fail on 1,000
 */
int get_thousand()
{
    hash * obj = construct_hash(1000);

    int i = 999;
    int * number;
    char string[50];
    for(; i >= 0; i--)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        number = (int *) malloc(sizeof(int));
        *number = i;
        assert(set(obj, string, (void *)number));
        sprintf(string, "Test%d\n", i);
        printf(string);
    }

       // find valid values
    for(i = 0; i < 1000; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        assert(*(int *)get(obj, string) == i);
        // generate ranodm string guaranteed to fail
        sprintf(string, "DifferentTest%d", i);
        // check it fails
        assert(get(obj, string) == 0);
    }

    return 1;
}

/* Retrieve 1,000 values perfectly, and fail on 1,000.
 * Behavior: Successfully retrieve 1,000, fail on 1,000
 */
int get_million()
{
    hash * obj = construct_hash(1000000);

    int i = 999999;
    int * number;
    char string[50];
    for(; i >= 0; i--)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        number = (int *) malloc(sizeof(int));
        *number = i;
        assert(set(obj, string, (void *)number));
    }

       // find valid values
    for(i = 0; i < 1000000; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        // generate new int
        assert(*(int *)get(obj, string) == i);
        // generate ranodm string guaranteed to fail
        sprintf(string, "Test%d", 4*i);
        // check it fails
        assert(get(obj, string) == 0);
    }
     
    return 1;
}