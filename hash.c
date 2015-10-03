#include "hash.h"

//int main() {
//	return 0;
//}

// Return an instance of the class with pre-allocated space for the given 
// number of objects.
struct hash * construct_hash(int size) {
	return 0;
}

// Necessary for manual memory management
void delete_hash(struct hash * hash_map) {

}

// Couldn't use 'bool', due to no such type existing in C
// currently debating use of uint8_t, or int, or creating a 'bool' type
// need to do more research on what is appropriate for C libraries
// DESCRIPTION:
// Stores the given key/value pair in the hash map. Returns a boolean value 
// indicating success / failure of the operation.
int set(struct hash * hash_map, const char * key, void * element) {
	return 0;
}

// Return the value associated with the given key, or null if no value is set.
// Also want to look into C operator overloading (like C++) for this, to match
// typical hash/dictionary syntax. One of these will end up as a wrapper for 
// the other.
void * get(struct hash * hash_map, const char * key) {
	return 0;
}

// Delete the value associated with the given key, returning the value on 
// success or null if the key has no value.
void * delete(struct hash * hash_map, const char * key) {
	return 0;
}

// Return a float value representing the load factor 
// (\`(items in hash map)/(size of hash map)\`) of the data structure. Since
// the size of the dat structure is fixed, this should never be greater than 1.
float load(struct hash * hash_map) {
	return 0;
}