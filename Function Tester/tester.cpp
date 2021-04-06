#include <iostream>
#include <string>

using namespace std;

int main() {
	string key = "abcdefgh";
	unsigned long index = 0;
	for (int i = 0; i < key.size(); ++i) {
		index *= 71;
		index += key.at(i);
		cout << index;
		index %= 10;
		cout << " -> " << index << endl;
	}
}