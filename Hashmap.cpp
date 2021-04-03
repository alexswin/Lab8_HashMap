#include "Hashmap.h"

/* 
	Constructor:
		Fill buckets with BUCKETS null nodes
		mapSize = 0
*/
Hashmap::Hashmap() {
	for(int i = 0; i < BUCKETS; ++i) {
		buckets[i] = NULL;
	}
	mapSize = 0;
}


/*
	* Return a hash code (bucket index) for a given key
	*  Must return a value >= 0 and < BUCKETS
	*  This can be done by generating a hash code and returning "hashcode % BUCKETS"
	*  Try to make your hash function so that the distribution is uniform over all buckets
*/
unsigned int Hashmap::hash(string key) const {
	unsigned int index = 0;
	for (int i = 0; i < key.size(); ++i) {
		index *= 71;
		index += key.at(i);
		index %= BUCKETS;
	}
	return index;
}


~Hashmap();
void insert(string key, int value);
bool contains(string key) const;
int get(string key) const;
int& operator [](string key);
bool remove(string key);
void clear();
string toString() const;
int size() const;

/*
* Get string representation of all keys and related values
*  Sort by values in descending order
*   For nodes that have the same value, sort alphabetically by key in ascending order.
*   You should use the NodeCompare struct to sort nodes.
*  Because a hashmap cannot sort items, you will have to use a different data structure
*   to do the sorting. Use a priority queue to do a heapsort.
*  Each key/value pair in the map should be on its own line with no leading or trailing spaces:
*
*  key => value
*
* For example:
*  bob => 13
*  alice => 9
*  eve => 3
*  steve => 3
*  nancy => 1
*  tom => 1
*/
string toSortedString() const;