#include <iostream>

template< typename T >
class store_a_lambda_class {
private:
	T lambda;

public:

	store_a_lambda_class(T lambda) :
		lambda(lambda)
	{}

	void run() {
		lambda();
	}
};

template< typename T >
store_a_lambda_class< T > store_a_lambda(T lambda) {
	return store_a_lambda_class< T >(lambda);
}



int main() {

	// this is OK, but it is ugly
	auto empty = [] {};
	auto store1 = store_a_lambda_class< decltype(empty) >(empty);
	store1.run();

	// this does not work because the two lambda's have a different type
	// auto store2 = store_a_lambda_class< decltype(empty) >([] {});

	auto empty_void_lambda_1 = []() {};
	auto store3 = store_a_lambda( empty_void_lambda_1 );
	store3.run();

	auto store4 = store_a_lambda([] {});
	store4.run();


   return 0;
}