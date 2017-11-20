#include <iostream>
#include <functional>

class capture_this {
private:
	int n;

public:
	capture_this() :
		n( __LINE__ )
	{
		auto lambda = [this]() {
			this->print( this->n );
		};
		lambda();
	}

	void print( int x ) {
		std::cout << x << "\n";
	}
};


int main() {

   capture_this object;

   return 0;
}