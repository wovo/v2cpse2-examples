#include <iostream>
#include <functional>

int main() {

	std::function< int(int) > f;

	f = [](int x) { return x; };
	std::cout << "identy " << f(5) << "\n";

	f = [](int x) { return 1 + x; };
	std::cout << "next " << f(5) << "\n";

	f = [](int x) { return 2 * x; };
	std::cout << "double " << f(5) << "\n";

   return 0;
}