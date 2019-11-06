#include <iostream>
#include <functional>

int main() {

	// std::cout is global, so you can use it without capturing
	auto here = []() { std::cout << __FILE__ << ":" << __LINE__ << "\n"; };
	here();

	// line is in the enclosing function, so you must capture it, 
	// either by copy or by reference, either individually or collectively
	int line = __LINE__;
	[&]() { std::cout << __FILE__ << ":" << line << "\n"; }();
	[&line] { std::cout << __FILE__ << ":" << line << "\n"; }();
	[=]() { std::cout << __FILE__ << ":" << line << "\n"; }();
	[line] { std::cout << __FILE__ << ":" << line << "\n"; }();

	// error: line is not accessible in the lambda
	// [] { std::cout << __FILE__ << ":" << line; }();

   return 0;
}