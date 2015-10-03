#ifndef HASH
#define HASH

struct hash_map {
	void * start;
	int size;	
	int num_elements;
};

struct hash_map * create_hash_map(int size);
bool set(struct hash_map *, string key, void * element);
void * get(struct hash_map *, string key);
void * delete(struct hash_map *, string key);
float load(struct hash_map *);

#endif