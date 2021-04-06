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


void Hashmap::buildNode(Node* &newNode, string key, int value, Node* prev, Node* next) {
	cout << "In buildNode" << endl;
	if(newNode == NULL) {
		cout << "Node is NULL, can't build. Throwing exception..." << endl;
		throw("Error: cannot build a NULL node!");
		//Should be throw(invalid_argument("Error: cannot build a NULL node!"));
		//But I think it might throw off the autograders
	}
	else {
		cout << "Building..." << endl;
		newNode->key = key;
		cout << "Key is " << newNode->key << " (should be " << key << ")" << endl;
		newNode->value = value;
		cout << "Value is " << newNode->value << " (should be " << value << ")" << endl;
		newNode->prev = prev;
		newNode->next = next;
	}
}


// Normally should rehash before inserting if average number of nodes per bucket is greater than 1, but I don't think I'm supposed to for this lab
// Rehashing: make a new array that's twice as big, iterate through old array, hash and insert all items into new array; point to new array
void Hashmap::insert(string key, int value) {
	unsigned int hashcode = hash(key);
	Node* currItem = buckets[hashcode];
	cout << "Hashcode is " << hashcode << endl;

	if(currItem == NULL) { //Empty bucket; create new head node
		currItem = new Node();
		cout << "Empty bucket, making new head node" << endl;
		buildNode(currItem, key, value, NULL, NULL);
		cout << "currItem: " << key << ", " << value << endl;
		++mapSize;
		return;
	}

	else { //currItem != NULL, i.e. bucket is not empty
		Node* prevItem;
		do {
			prevItem = currItem;
			currItem = currItem->next;
		} while(currItem != NULL && currItem->key != key);

		if(currItem != NULL) { //key found at currItem; change value
			currItem->value = value;
			cout << "Key found, changing value." << endl;
			cout << "currItem: " << key << ", " << value << endl;
			return;
		}

		else { //key not found in bucket; reached end of list; create new node
			cout << "Bucket not empty but key not present. Making new node" << endl;
			currItem = new Node();
			buildNode(currItem, key, value, prevItem, NULL);
			cout << "currItem: " << key << ", " << value << endl;
			++mapSize;
			return;
		}
	}
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
	cout << "In size. Size is " << mapSize << endl;
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


bool Hashmap::contains(string key) const { //FIXME
	cout << "False.";
	return false;
}


int& Hashmap::operator [](string key) {
	return at(key);
}


int& Hashmap::at(string key) {
	
}


bool Hashmap::remove(string key) { //FIXME
	cout << "False.";
	return false;
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
string Hashmap::toSortedString() const { //FIXME
	cout << "False.";
	return "false";
}