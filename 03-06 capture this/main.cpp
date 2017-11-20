#include <iostream>
#include <functional>

using void_void = std::function< void(void) >;

void assign_lambda(void_void & f) {
	int n = __LINE__;
	std::cout << __LINE__ << ":" << n << "\n";

	// n is captured by reference by a lambda that will live longer 
	// than n. trouble on the way!
	f = [&n]() {
		std::cout << __LINE__ << ":" << n << "\n";
	};
}

int main() {

	void_void f;
	assign_lambda(f);

	// this function stores a lambda that uses the local variable n,
	// which is no longer valid. Undefined behaviour!
	f();

   return 0;
}