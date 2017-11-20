#include <iostream>

int main() {
	signed char c = 127;
	c = c + 1;
	if (c > 0) {
		std::cout << "larger\n";
	} else {
		std::cout << "not larger\n";
	}
   return 0;
}