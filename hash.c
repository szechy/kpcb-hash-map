#include "hash.h"
#include <stdio.h>


// hash_cell is the struct for each cell in a map.
// This struct is not stored in the header to prevent outside access
// The key for indexing, and the desired data.
// Status is the enum below, and can either be empty, full, or was_used.

typedef enum {EMPTY, FULL, WAS_USED} cell_status;

typedef struct
{
	char * key;
	void * datum;
	cell_status status;
} hash_cell;

// Return an instance of the class with pre-allocated space for the given 
// number of objects. If size is negative, returns a nullptr.
hash * construct_hash(int size)
{
	// Create hash structure
	hash * new_hash = malloc(sizeof(hash));

	// Check if space is negative - if so, nullptr.
	if(size < 0)
		return 0;

	else if(size == 0)
	{
		new_hash->size = 0;
		new_hash->map = 0;
		return new_hash;
	}

	new_hash->size = size;

	hash_cell * map = malloc(sizeof(hash_cell) * size);
	new_hash->map = (void *)map;

	//iterate through the whole map and set initial values
	for(int i = 0; i < size; ++i)
	{
		((hash_cell *)new_hash->map)[i].key = 0;
		((hash_cell *)new_hash->map)[i].datum = 0;
		((hash_cell *)new_hash->map)[i].status = EMPTY;
	}

	return new_hash;
}

// Necessary for manual memory management
void delete_hash(hash * hash_map)
{
	// free up the map, in reverse order
	// TODO: Not sure how to deal with clean-up of objects in map yet
	// Re, above: just kidding. Memory system keeps track of allocations.
	// If there's an allocation at that address, memory system knows the size.
	for(int i = hash_map->size - 1; i >= 0; --i)
	{
		free(((hash_cell *)hash_map->map)[i].key);
		free(((hash_cell *)hash_map->map)[i].datum);
		// this code below pointless because free(hash_map->map) handles arrays
		//free(&(((hash_cell *)hash_map->map)[i]));
	}

	free(hash_map->map);
	hash_map->map = 0;

	// free up the hash_map struct itself

	free(hash_map);
	hash_map = 0;
}

// Couldn't use 'bool', due to no such type existing in C
// currently debating use of uint8_t, or int, or creating a 'bool' type
// need to do more research on what is appropriate for C libraries
// DESCRIPTION:
// Stores the given key/value pair in the hash map. Returns a boolean value 
// indicating success / failure of the operation.
int set(hash * hash_map, const char * key, void * element)
{
	return 0;
}

// Return the value associated with the given key, or null if no value is set.
// Also want to look into C operator overloading (like C++) for this, to match
// typical hash/dictionary syntax. One of these will end up as a wrapper for 
// the other.
void * get(hash * hash_map, const char * key)
{
	return 0;
}

// Delete the value associated with the given key, returning the value on 
// success or null if the key has no value.
void * delete(hash * hash_map, const char * key)
{
	return 0;
}

// Return a float value representing the load factor 
// (\`(items in hash map)/(size of hash map)\`) of the data structure. Since
// the size of the dat structure is fixed, this should never be greater than 1.
float load(hash * hash_map)
{
	return 0;
}