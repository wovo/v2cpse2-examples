#include <iostream>
#include <iomanip>
#include <functional>


// ==========================================================================

void test_empty_lambdas() {

	// lambda's without parameters, returning void
	auto empty_void_lambda_1 = [](){};
	auto empty_void_lambda_2 = []()->void {};
	auto empty_void_lambda_3 = []{};

	// call'm
	empty_void_lambda_1();
	empty_void_lambda_2();
	empty_void_lambda_3();
}


// ==========================================================================

void test_return_types(){

	auto increment_1 = [](int & n) { return ++n; };
	auto increment_2 = [](int & n)->int { return ++n; };
	auto increment_3 = [](int & n)->double { return ++n; };
	auto increment_4 = [](int & n) { return 0.0 + ++n; };

	auto n = 0;
	std::cout << "n = " << std::fixed << std::setprecision(5);
	std::cout << "n = " << n << "\n";
	std::cout << "increment_1 returns " << increment_1(n) << "\n";
	std::cout << "n = " << n << "\n";
	std::cout << "increment_2 returns " << increment_2(n) << "\n";
	std::cout << "n = " << n << "\n";
	std::cout << "increment_3 returns " << increment_3(n) << "\n";
	std::cout << "n = " << n << "\n";
	std::cout << "increment_4 returns " << increment_4(n) << "\n";
	std::cout << "n = " << n << "\n";

	// error because each lambda is a different type,
	// event when they read exactly the same
	// increment_1 = [](int & n) { return ++n; };
}


// ==========================================================================

template< typename T >
void pass_a_lambda(T lambda) {
	lambda();
}

void test_pass_void_lambdas() {

	auto empty_void_lambda = [](){};
	pass_a_lambda( empty_void_lambda );

	pass_a_lambda( []{} );

	// error at the lambda() call in the pass_a_lambda function
	//pass_a_lambda( []( int x ){} );

}


// ==========================================================================

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

void test_store_lambdas(){

	auto empty = [] {};
	auto store1 = store_a_lambda_class< decltype( empty ) >( empty );
	store1.run();

	// this does not work because the two lambda's have a different type
	//auto store2 = store_a_lambda_class< decltype(empty) >( []{} );

	auto store3 = store_a_lambda( empty );
	store3.run();
	auto store4 = store_a_lambda( [] {} );
	store4.run();
}


// ==========================================================================

class function_store {
private:
	std::function< int(int) > function;
public:

	void set(std::function< int(int) > f) {
		function = f;
	}

	int run( int x ){
		return function( x );
	}

	int operator()( int x ) {
		return function( x );
	}

};

void test_function_store() {

	std::function< int(int) > f;

	f = []( int x ){ return x; };
	std::cout << "identy " << f( 5 ) << "\n";

	f = []( int x ){ return 1 + x; };
	std::cout << "next " << f( 5 ) << "\n";

	f = []( int x ){ return 2 * x; };
	std::cout << "double " << f( 5 ) << "\n";

	function_store s;

	s.set([](int x) { return x; });
	std::cout << "identy " << s.run( 5 ) << "\n";

	s.set([](int x) { return 1 + x; });
	std::cout << "next " << s.run( 5 ) << "\n";

	s.set([](int x) { return 2 * x; });
	std::cout << "double " << s( 5 ) << "\n";

}


// ==========================================================================

void test_captures(){

	// std::cout is global, so you can use it without capturing
	auto here = [](){ std::cout << __FILE__ << ":" << __LINE__ << "\n"; };
	here();

    // line is in the enclosing function, so you must capture it, 
	// either by copy or by reference, either individually or collectively
	int line = __LINE__;
	[ & ]() { std::cout << __FILE__ << ":" << line << "\n"; }();
	[ &line ] { std::cout << __FILE__ << ":" << line << "\n"; }();
	[ = ]() { std::cout << __FILE__ << ":" << line << "\n"; }();
	[ line ] { std::cout << __FILE__ << ":" << line << "\n"; }();

	// error: line is not accessible in the lambda
	//[]{ std::cout << __FILE__ << ":" << line; }();

}


// ==========================================================================

class capture_this {
private:
   int n;
public:
   capture_this(): 
	  n( __LINE__) 
   {
      auto lambda = [ this ](){ 
         this->print( this->n ); 
	  };
	  lambda();
   }
   void print( int x ){
      std::cout << x << "\n";
   }
};

void test_this_capture(){
	auto x = capture_this();
}


// ==========================================================================

using void_void = std::function< void(void) >;

void assign_lambda( void_void & f ){
   int n = __LINE__;
   std::cout << __LINE__ << ":" << n << "\n";

   // n is captured by reference by a lambda that will live longer 
   // than n. trouble on the way!
   f = [ &n ](){ 
	   std::cout << __LINE__ << ":" << n << "\n"; 
   };
}

void test_invalid_reference(){
    void_void f;
	assign_lambda( f );

	// this function stores a lambda that uses the local variable n,
	// which is no longer valid. Undefined behaviour!
	f();
}


// ==========================================================================


int main( int argc, char *argv[] ){
	std::cout << "Demos & tests for lambda's\n";

	test_empty_lambdas();
	test_pass_void_lambdas();
	test_store_lambdas();
	test_return_types();
	test_captures();
	test_this_capture();
	test_invalid_reference();

	return 0;
}

