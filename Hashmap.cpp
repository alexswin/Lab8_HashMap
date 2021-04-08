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


Hashmap::~Hashmap() {
	clear();
}


void Hashmap::clear() {
	Node* currItem;
	Node* nextItem;
	for (int i = 0; i < BUCKETS; ++i) { //If rehashing and size doubling can happen, change BUCKETS to the current array size, and reset array size at the end
		currItem = buckets[i];
		while (currItem != NULL) {
			nextItem = currItem->next;
			delete currItem;
			currItem = nextItem;
		}
		buckets[i] = NULL;
	}
	mapSize = 0;
}


unsigned int Hashmap::hash(string key) const {
	unsigned int hashcode = 0;
	for (int i = 0; i < key.size(); ++i) {
		hashcode *= 71;
		hashcode += key.at(i);
		hashcode %= BUCKETS;
	}
	return hashcode;
}


// Normally should rehash before inserting if average number of nodes per bucket is greater than 1, but I don't think I'm supposed to for this lab
// Rehashing: make a new array that's twice as big, iterate through old array, hash and insert all items into new array; point to new array
void Hashmap::insert(string key, int value) {
	at(key) = value;
}


int Hashmap::get(string key) const{
	unsigned int hashcode = hash(key);
	Node* currItem = buckets[hashcode];
	while(currItem != NULL && currItem->key != key) {
		currItem = currItem->next;
	}
	if(currItem == NULL) { //Key not found
		throw(invalid_argument("Key not present!"));
	}
	else { //Key found
		return currItem->value;
	}
}


int Hashmap::size() const {
	return mapSize;
}


string Hashmap::toString() const {
	ostringstream output;
	Node* currItem;
	for(int i = 0; i < BUCKETS; ++i) {
		output << "[" << i << "]";
		currItem = buckets[i];
		while(currItem != NULL) {
			output << " " << currItem->key << " => " << currItem->value;
			if (currItem->next != NULL) {
				output << ",";
			}
			currItem = currItem->next;
		}
		output << endl;
	}
	return output.str();
}


bool Hashmap::contains(string key) const {
	try {
		get(key);
		return true;
	}
	catch(invalid_argument) {
		return false;
	}
}


int& Hashmap::operator [](string key) {
	return at(key);
}


int& Hashmap::at(string key) {
	unsigned int hashcode = hash(key);
	Node* currItem = buckets[hashcode];
	while(currItem != NULL) {
		if(currItem->key == key) {
			break;
		}
		else {
			currItem = currItem->next;
		}
	}
	if(currItem == NULL) { //Create a new Node at the beginning of the list
		currItem = new Node();
		currItem->next = buckets[hashcode];
		currItem->prev = NULL;
		currItem->key = key;
		currItem->value = 0;
		if (buckets[hashcode] != NULL) {
			buckets[hashcode]->prev = currItem;
		}
		buckets[hashcode] = currItem;
		++mapSize;
	}
	return currItem->value;
}


bool Hashmap::remove(string key) {
	unsigned int hashcode = hash(key);
	Node* currItem = buckets[hashcode];
	while(currItem != NULL && currItem->key != key) {
		currItem = currItem->next;
	}
	if(currItem == NULL) {
		return false;
	}
	else {
		Node* delMe = currItem;
		currItem = delMe->next;
		// (...) -- delMe -- currItem -- (...)
		if(delMe->prev == NULL) { //delMe is head
			buckets[hashcode] = currItem;
		}
		else { //delMe is not head
			delMe->prev->next = currItem;
		}
		if (currItem != NULL) {
			currItem->prev = delMe->prev;
		}
		delete delMe;
		--mapSize;
		return true;
	}
}


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
string Hashmap::toSortedString() const {
  stringstream ss;
  priority_queue<Node*, vector<Node*>, NodeCompare> nodeHeap;
	Node* currItem;
  for(int i = 0; i < BUCKETS; i++) {
    // Iterate through each bucket. Use nodeHeap.push to push all Node* onto heap.
		currItem = buckets[i];
		while(currItem != NULL) {
			nodeHeap.push(currItem);
			currItem = currItem->next;
		}
  }
  while(!nodeHeap.empty()) {
    Node* top = nodeHeap.top(); // Get top node (next node in sorted order)
    ss << top->key << " => " << top->value << endl; // Add node data to stringstream
    nodeHeap.pop(); // Pop it off
  }
  return ss.str();
}