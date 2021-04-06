#include <iostream>
#include <string>

#include "Hashmap.cpp"

using namespace std;

int main() {
	Hashmap* map = new Hashmap;
	int size = map->size();
	cout << size << endl;
}