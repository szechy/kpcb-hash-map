#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	free_hash(obj);
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
	free_hash(obj);

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
	free_hash(obj);

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
	free_hash(obj);

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
	free_hash(obj);

	return 1;
}

/* Fill a hash map of size 1, with one key-value pair. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_one()
 {
	hash * obj = construct_hash(1);

	// TODO: Document this as the proper way to add elements to the hash map
	// free_hash() cleans up the hash and any remaining elements
	// Using normally allocated elements ends up being weird with freeing
	// /deleting items
	int * number = (int *) malloc(sizeof(int));
	*number = 5;

	// Check that function reports it was placed
	assert(set(obj, "Test", (void *)number));

	// Check that value actually exists in hash map
	assert(*(int *)retrieveLocation(obj, 0) == 5);

	// Clean up hash
	free_hash(obj);

	return 1;
 }

/* Fill a hash map of size 5, with 5 key-value pairs. No collisions. 
 * Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_five()
 {
	hash * obj = construct_hash(5);
	int *number = malloc(sizeof(int));
	*number = 0;

	// Check that function reports it was placed
	// Keys chosen because they hash to different locations with no collisions
	assert(set(obj, "Test25", (void *)number));   // hashes to 2
	number = malloc(sizeof(int));
	*number = 1;
	assert(set(obj, "Test734", (void *)number));  // hashes to 1
	number = malloc(sizeof(int));
	*number = 2;
	assert(set(obj, "Tes", (void *)number));      // hashes to 4
	number = malloc(sizeof(int));
	*number = 3;
	assert(set(obj, "Test984477extrachar", (void *)number)); // hashes to 3
	number = malloc(sizeof(int));
	*number = 4;
	assert(set(obj, "Test0", (void *)number));     // hashes to 0

	// Check that value actually exists in hash map at proper location
	assert(*(int *)retrieveLocation(obj, 2) == 0);
	assert(*(int *)retrieveLocation(obj, 1) == 1);
	assert(*(int *)retrieveLocation(obj, 4) == 2);
	assert(*(int *)retrieveLocation(obj, 3) == 3);
	assert(*(int *)retrieveLocation(obj, 0) == 4);

	// Clean up hash
	free_hash(obj);

	return 1;
 }

/* Fill a hash map of size 5, with 5 key-value pairs. Two collisions. 
 * Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_five_with_colls()
 {
	hash * obj = construct_hash(5);
	int *number = malloc(sizeof(int));
	*number = 0;

	// Check that function reports it was placed
	// Keys chosen because they hash to similar locations, causing collisions
	assert(set(obj, "Test7", (void *)number));      // hashes to 3
	number = malloc(sizeof(int));
	*number = 1;
	assert(set(obj, "Test2", (void *)number));      // hashes to 0
	number = malloc(sizeof(int));
	*number = 2;
	assert(set(obj, "Test1", (void *)number));      // hashes to 0, colls to 1
	number = malloc(sizeof(int));
	*number = 3;
	assert(set(obj, "Test500", (void *)number));    // hashes to 0, to 1, 2
	number = malloc(sizeof(int));
	*number = 4;
	assert(set(obj, "Test25", (void *)number));     // hashes to 2, to 3, 4

	// Check that value actually exists in hash map
	assert(*(int *)retrieveLocation(obj, 3) == 0);
	assert(*(int *)retrieveLocation(obj, 0) == 1);
	assert(*(int *)retrieveLocation(obj, 1) == 2);
	assert(*(int *)retrieveLocation(obj, 2) == 3);
	assert(*(int *)retrieveLocation(obj, 4) == 4);

	// Clean up hash
	free_hash(obj);

	return 1;
 }

/* Fill a hash map of size 10, with 10 key-value pairs. 
 * Seven sets have at least one collision. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int set_ten_with_colls()
 {
	hash * obj = construct_hash(10);

	// Looking at the sheer number of collisions for the set below is real-life
	// evidence to me that prime-number-sized hash maps are important!
	int * number;
	int i = 9;
	char string[50];
	for(; i >= 0; i--)
	{
		// generate new string
		sprintf(string, "Test%d", i);
		// generate new int
		number = (int *) malloc(sizeof(int));
		*number = i;
		// Check that function reports it was placed        
		assert(set(obj, string, (void *)number));  
	}

	// Check that value actually exists in hash map
	assert(*(int *)retrieveLocation(obj, 8) == 0);
	assert(*(int *)retrieveLocation(obj, 7) == 1);
	assert(*(int *)retrieveLocation(obj, 2) == 2);
	assert(*(int *)retrieveLocation(obj, 0) == 3);
	assert(*(int *)retrieveLocation(obj, 9) == 4);
	assert(*(int *)retrieveLocation(obj, 6) == 5);
	assert(*(int *)retrieveLocation(obj, 1) == 6);
	assert(*(int *)retrieveLocation(obj, 5) == 7);
	assert(*(int *)retrieveLocation(obj, 3) == 8);
	assert(*(int *)retrieveLocation(obj, 4) == 9);  

	// Clean up hash
	free_hash(obj);

	return 1;
 }

/* Fill a hash map of size 1,000,000, with 1,000,000 key-value pairs. 
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
		sprintf(string, "%dTe%dst%d", i, i+300, i+5000);
		// generate new int
		number = (int *) malloc(sizeof(int));
		*number = rand();
		assert(set(obj, string, (void *)number));  
	}

	// Clean up hash
	free_hash(obj);

	return 1;
}

/* Retrieve one value from a hash map - conventional use case.
 * BEHAVIOR: Return 1, with successful retrieval
 */
int get_one()
{
	hash * obj = construct_hash(10);
	
	// Create and place item
	int * number = malloc(sizeof(int));
	*number = 15;
	assert(set(obj, "TestKey", (void *)number));

	// Retrieve item
	assert(*(int *)get(obj, "TestKey") == *number);

	// Clean up hash
	free_hash(obj);

	return 1;
}

/* Fail to retrieve one value from a hash map, because no keys map there
 * BEHAVIOR: get() returns nullptr, with unsuccessful retrieval
 */
 int get_one_fail()
 {
	hash * obj = construct_hash(10);

	// Create and place item
	int * number = malloc(sizeof(int));
	*number = 27;
	assert(set(obj, "TestKey", (void *) number));

	// Fail to retrieve item
	assert(get(obj, "DifferentKey") == 0);

	// Clean up hash
	free_hash(obj);    

	return 1;
 }

/* Retrieve ten values properly, and five values failing
 * BEHAVIOR: Successfully retrieve ten, and fail to retrieve five
 */
 int get_ten()
 {
	hash * obj = construct_hash(10);

	// Create and place items
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

	// Clean up hash
	free_hash(obj);    

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
	}

	// find valid values
	for(i = 0; i < 1000; i++)
	{
		// generate new string and find valid item
		sprintf(string, "Test%d", i);
		assert(*(int *)get(obj, string) == i);

		// generate random string guaranteed to fail
		sprintf(string, "DifferentTest%d", i);
		// check it fails
		assert(get(obj, string) == 0);
	}

	// Clean up hash
	free_hash(obj);    

	return 1;
}

/* Retrieve 1,000,000 values perfectly
 * Behavior: Successfully retrieve 1,000,000
 * Test currently only at 950,000 because last 50,000 exceptionally
 * time-consuming. TODO: optimize for this test case and full 1,000,000
 */
int get_million()
{
	hash * obj = construct_hash(1000000);

	int i = 949999;
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
	for(i = 0; i < 950000; i++)
	{
		// generate new string and find valid item
		sprintf(string, "Test%d", i);
		int test = *(int *)get(obj, string);
		// print out update status to let user know still processing
		assert(test == i);

		// generate ranodm string guaranteed to fail
		sprintf(string, "Test%ds", i);
		// check it fails
		assert(get(obj, string) == 0);
	}

	// Clean up hash
	free_hash(obj);    
	 
	return 1;
}

/* Set a value placed in the hash map, then delete it
 * Behavior: successfully returns one key's value, then removes it
 */
int delete_one()
{
	hash * obj = construct_hash(1);

	// Create item
	int a = 5;
	char string[50];
	sprintf(string, "TestingThisNumber%d", a);
	assert(set(obj, string, (void *)&a));

	// Remove item
	assert(*(int *)delete(obj, string) == 5);

	// Clean up hash
	free_hash(obj);

	return 1;
}

/* Fill a hash map of size 5, with 5 key-value pairs and no collisions,
 * then delete all five items. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int delete_one_fail()
 {
	hash * obj = construct_hash(5);

	// Create item
	int *a = malloc(sizeof(int));
	*a = 7;

	// Check that function reports it was placed
	assert(set(obj, "Test7", (void *)a));

	// Attempt to remove a different item and fail
	assert(delete(obj, "Test1") == 0);

	// Clean up hash
	free_hash(obj);

	a = 0; 

	return 1;
 }

/* Fill a hash map of size 10, with 10 key-value pairs. 
 * Seven sets have at least one collision. Conventional use case.
 * BEHAVIOR: Return 1, with successful set
 */
 int delete_ten_with_fail()
 {
	hash * obj = construct_hash(10);

	// Create items for hash
	int i = 9;
	int *number;
	char string[50];
	for(; i >= 0; i--)
	{
		// generate new string
		sprintf(string, "Test%d", i);
		number = malloc(sizeof(int));
		*number = i;
		assert(set(obj, string, &i));  
	}

	for(i = 19; i >= 0; i--)
	{
		sprintf(string, "Test%d", i/2); 
		// Half the time, delete the item - other half, it's already been
		// deleted, so check that it fails       
		if(i % 2 == 0)
        {
            assert(delete(obj, string) == 0);            
        }
		else
		{
			assert(*(int *) delete(obj, string) == i);                       
		}
	}

	// Clean up hash
	free_hash(obj);

	return 1;
 }


/* Fill a hash map of size 1,000,000, with 1,000,000 key-value pairs. 
 * Likely to be a lot of collisions. Stress test case.
 * BEHAVIOR: Return 1, with successful set
 */
 int delete_thousand()
 {
	hash * obj = construct_hash(10000);

	// Create items for hash
	int i = 9999;
	int *number;
	char string[50];
	for(; i >= 0; i--)
	{
		// generate new string
		sprintf(string, "Test%d", i);
		number = malloc(sizeof(int));
		*number = i;
		assert(set(obj, string, number)); 
	}

	for(i = 19999; i >= 0; i--)
	{
		sprintf(string, "Test%d", i/2);
		// Half the time, delete the item - other half, it's already been
		// deleted, so check that it fails       
		if(i % 2 == 0)
        {
            assert(delete(obj, string) == 0);            
        }
		else
		{
			// Free manually managed items from memory
			int * ptr = delete(obj, string);
			assert(*ptr == i/2);          
			free(ptr); 
		}
	}  

	// Clean up now-empty hash
	free_hash(obj);

	return 1;
}

/* Fill a hash map of size 1,000,000, with 1,000,000 key-value pairs. 
 * Likely to be a lot of collisions. Stress test case.
 * BEHAVIOR: Return 1, with successful set
 */
 int delete_million()
 {
	hash * obj = construct_hash(1000000);

	// Points are not necessary - deleting
	// Pointers, however, should be used if any possibility of data remaining
	// in hash map during free_hash() - otherwise, segfaults during free_hash()
	// as that memory is managed automatically. This is provided merely as an
	// example, maybe should be removed.
	int i = 959999;
	char string[50];
	for(; i >= 0; i--)
	{
		// generate new string
		sprintf(string, "Test%d", i);
		assert(set(obj, string, &i));  

		if(i % 10000 == 0)
		{
			sprintf(string, "PROGRESS: %d", i);
			//printf("%s\n", string);  
		}

	}

	for(i = 959999*2+1; i >= 0; i--)
	{
		sprintf(string, "Test%d", i/2);
		// Half the time, delete the item - other half, it's already been
		// deleted, so check that it fails        
		if(i % 2 == 0)
			assert(delete(obj, string) == 0);
		else
		{
			 assert(*(int *) delete(obj, string) == i);           
		}
		if(i % 10000 == 0)
		{
			sprintf(string, "PROGRESS: %d", i);
			//printf("%s\n", string);  
		}
	}  

	// Clean up hash
	free_hash(obj);

	return 1;
}

/* Check load factor of empty hash map of size 1. Base test case.
 * BEHAVIOR: Return 1, with successful load factor of 0
 */
int load_one_empty()
{
	hash * obj = construct_hash(1);

	assert(load(obj) == 0);

	free_hash(obj);

	return 1;
}

/* Check load factor of full hash map of size 1. Base test case.
 * BEHAVIOR: Return 1, with successful load factor of 0
 */
int load_one_full()
{
	hash * obj = construct_hash(1);

	// Create item
	int * number = malloc(sizeof(int));
	*number = 5;
	assert(set(obj, "Test", number));

	// Check load factor
	assert(load(obj) == 1);

	free_hash(obj);

	return 1;
}

/* Check load factor of various stages of hash map of size 10.
 * Conventional use case.
 * BEHAVIOR: Return 1, with successful load factors with each set.
 */
int load_ten()
{
    hash * obj = construct_hash(10);

    // Create items for hash, and check load factors
    int i = 0;
    int *number;
    char string[50];
    for(; i < 10; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        number = malloc(sizeof(int));
        *number = i;
        assert(load(obj) == (float)i/10);
        assert(set(obj, string, number)); 
    }

    assert(load(obj) == 1);

    free_hash(obj);

    return 1;
}

/* Check load factor of various stages of hash map of size 1,000.
 * Conventional to meidum-sized use case.
 * BEHAVIOR: Return 1, with successful load factors with each set.
 */
int load_thousand()
{
    hash * obj = construct_hash(1000);

    // Create items for hash, and check load factors
    int i = 0;
    int *number;
    char string[50];
    for(; i < 1000; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        number = malloc(sizeof(int));
        *number = i;
        assert(load(obj) == (float)i/1000);
        assert(set(obj, string, number)); 
    }

    assert(load(obj) == 1);

    free_hash(obj);

    return 1;
}

/* Check load factor of various stages of hash map of size 1,000.
 * Conventional to meidum-sized use case.
 * BEHAVIOR: Return 1, with successful load factors with each set.
 */
int load_million()
{
    hash * obj = construct_hash(1000000);

    // Create items for hash, and check load factors
    int i = 0;
    int *number;
    char string[50];
    for(; i < 1000000; i++)
    {
        // generate new string
        sprintf(string, "Test%d", i);
        number = malloc(sizeof(int));
        *number = i;
        assert(load(obj) == (float)i/1000000);
        assert(set(obj, string, number)); 
    }

    assert(load(obj) == 1);

    free_hash(obj);

    return 1;
}