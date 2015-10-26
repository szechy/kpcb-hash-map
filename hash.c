#include "hash.h"
// cfarmhash borrowed from Fredrik's fantastic repository (which is originally
// from Google's fantastic work on FarmHash):
// https://github.com/fredrikwidlund/cfarmhash
#include "cfarmhash.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// hash_cell is the struct for each cell in a map.
// This struct is not stored in the header to prevent outside access
// The key for indexing, and the desired data.
// Status is the enum below, and can either be empty, full, or was_used.

typedef enum {EMPTY, FULL, WAS_USED} cell_status;

typedef struct
{
	unsigned long hashed_key;
	void * datum;
	cell_status status;
} hash_cell;

// Private hash function from cstring to unsigned long.
// See function implementation for more detail.
uint32_t SuperFastHash (const char * data, int len);
unsigned long ElfHash(const char *s);


// Private function to simplify retrieving a hash in the map
// Returns the datum's index, or -1.
// Used get() and delete(), which then implements its own action
int get_index(hash * hash_map, const char * key, int looking_for_empty);

// Return an instance of the class with pre-allocated space for the given 
// number of objects. If size is negative, returns a nullptr.
hash * construct_hash(int size)
{
	// Check if space is negative - if so, nullptr.
	if(size < 0)
	{
		return 0;
	}
	
	// Create hash structure
	hash * new_hash = malloc(sizeof(hash));

	if(size == 0)
	{
		new_hash->map = 0;
		new_hash->in_use = 0;		
		new_hash->size = 0;
		return new_hash;
	}

	new_hash->in_use = 0;
	new_hash->size = size;

	hash_cell * map = malloc(sizeof(hash_cell) * size);
	new_hash->map = (void *)map;

	// iterate through the whole map and set initial values
	int i = 0;
	for(; i < size; ++i)
	{
		((hash_cell *)new_hash->map)[i].hashed_key = 0;
		((hash_cell *)new_hash->map)[i].datum = 0;
		((hash_cell *)new_hash->map)[i].status = EMPTY;
	}

	return new_hash;
}

// Necessary for manual memory management
void free_hash(hash * hash_map)
{
	// free up the map, in reverse order
	// Memory system keeps track of allocations, and how many bytes each
	// pointer points to. If there's an allocation at that address, memory 
	// system knows the size.
	int i = hash_map->size - 1;
	for(; i >= 0; --i)
	{
		free(((hash_cell *)hash_map->map)[i].datum);
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
	// TODO: check if hash is already in map, and return failure
	// TODO: attempt to simplify by sharing functions with get_index()

	// if the map is full, don't bother - and report we're full
	if(hash_map->in_use == hash_map->size)
	{
		return 0;
	}

	// Compute hash, modulus the size of the map
	unsigned long hash_original = cfarmhash(key, strlen(key));
	//unsigned long hash_original = SuperFastHash(key, strlen(key));
	
	int loc = get_index(hash_map, key, 1);

	if(loc != -1)
	{
		// are we claiming a new spot or simply overwriting?
		if(((hash_cell *)hash_map->map)[loc].hashed_key == 0)
			hash_map->in_use++;
		((hash_cell *)hash_map->map)[loc].hashed_key = hash_original;
		((hash_cell *)hash_map->map)[loc].datum = element;		
		((hash_cell *)hash_map->map)[loc].status = FULL;
		return 1;
	}
	else
	{
		return 0;
	}
}

// Return the value associated with the given key, or null if no value is set.
// TODO: Want to look into C operator overloading (like C++) for this, to match
// typical hash/dictionary syntax brackets []. One of these will end up as a 
// wrapper for the other.
void * get(hash * hash_map, const char * key)
{
	// Retrieve index of hash, if it exists.
	int index = get_index(hash_map, key, 0);
	// send failure condition if not found
	if(index == -1)
	{
		return 0;
	}
	// Return pointer to datum
	else
	{
		return ((hash_cell *)hash_map->map)[index].datum;		
	}
}

// Delete the value associated with the given key, returning the value on 
// success or null if the key has no value.
void * delete(hash * hash_map, const char * key)
{
	// Retrieve index of hash, if it exists.
	int index = get_index(hash_map, key, 0);
	// Mark out the hash cell, and set to null if it exists
	if(index > -1)
	{
		void * datum = ((hash_cell *)hash_map->map)[index].datum;
		((hash_cell *)hash_map->map)[index].datum = 0;
		((hash_cell *)hash_map->map)[index].hashed_key = 0;
		((hash_cell *)hash_map->map)[index].status = WAS_USED;
		hash_map->in_use--;
		return datum;
	}
	// if index == -1, return null
	else
	{
		return 0;
	}
}

// Return a float value representing the load factor 
// (\`(items in hash map)/(size of hash map)\`) of the data structure. Since
// the size of the dat structure is fixed, this should never be greater than 1.
float load(hash * hash_map)
{
	return ((float)hash_map->in_use)/hash_map->size;
}

// This function retrieves the index that a hash resides at in a map.
// Both get(), delete() need an algorithm for this functionality,
// so it makes sense that both should reference one common location
// If the hash doesn't exist, it returns -1.
// Set looking_for_empty if using set(), so that way all three functions
// reference same collision resolution algorithms
int get_index(hash * hash_map, const char * key, int looking_for_empty)
{
	unsigned long hash_original = cfarmhash(key, strlen(key));

	unsigned long hash_mod = hash_original % hash_map->size;

	hash_cell * map = hash_map->map;

	// go through collision resolution until reach empty cell
	// unless we've explored the whole map...
	// With linear probing we know we will see every spot in fixed-size map,
	// in minimum time, which is great with high load factors.
	// With the original implementation of quadratic probing scheme and 
	// non-prime-number-sizes we could get stuck in loops where only a small
	// percentage of the map was being visited. Also had to have O(n) memory
	// to track when map was fully visited. With linear probing, easy to
	// establish when whole map is visited (great with high load factors) 

	int num_visited = 0, new_location = hash_mod;
	while(num_visited != hash_map->size)
	{
		new_location = (hash_mod + num_visited) % hash_map->size;
		// If looking for an empty spot and this is empty
		// return proper value depending on looking_for_empty
		if(map[new_location].status == EMPTY)
		{
			return looking_for_empty ? new_location : -1;
		}
		// if spot is in-use, use if looking for empty
		else if((map[new_location].status == WAS_USED) & (looking_for_empty))
		{
			return new_location;
		}
		// we want to keep moving for get() and delete()
		else if((map[new_location].status == FULL)
			& (map[new_location].hashed_key == hash_original))
		{
			// Possible error here - what if hashing algorithm hashes
			// two keys to same thing? cfarmhash has not yet caused this
			// to happen, unlike other two hashing algorithms - willing
			// to risk the probability of this not happening with that
			// one algorithm for the unimportant and small scale of this
			// hash map library.
			return new_location;
		}

		// otherwise we haven't found what we're looking for
		num_visited++;
	}
	// Couldn't find the hash's location
	return -1;
}

// This function should not be used by consumers.
// In C++ and other object-oriented languages, it would be marked private
// and the testing classes would be a 'friend' (C++ keyword) of this one
// private function. Not sure how to implement that in C.
void * retrieveLocation(hash * hash_map, int loc)
{
	return ((hash_cell * )(hash_map->map))[loc].datum;
}

// Different hash algorithm then ELFHash. After seeing very similar hashes 
// with similar strings with the ELF-hash algorithm, resulting in poor
// performance with linear probing, I began research into a different hashing 
// algorithm. This algorithm is borrowed from Paul Hseih at
// http://www.azillionmonkeys.com/qed/hash.html, licensed under LGPL. 
// It's more complicated, but has completely different hashes with similar
// inputs, unlike ELFHash. I should probaby look into a different probing
// structure still, though

/*#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

uint32_t SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    // Main loop
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    // Handle end cases 
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    // Force "avalanching" of final 127 bits
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

// Direct copy of Wikipedia's explanation of the ELF hash, which is a variant
// of the PJW hash. This is conventionally used for ELF files in Unix systems.
// This algorithm was chosen for its simplicity, and that it sees common use.
// See https://en.wikipedia.org/wiki/PJW_hash_function
unsigned long ElfHash(const char *s)
{
	unsigned long h = 0, high;
	while(*s)
	{
		h = (h<<4) + *s++;
	}
	if((high = (h & 0xF00000000)))
		h ^= high >> 24;
	h &= ~high;
	return h;
}
*/
