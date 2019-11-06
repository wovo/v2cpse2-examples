#include <iostream>

template < int Num, int Denum >
class unit {
private:
	double value;
	static double constexpr base = static_cast<double>(Num) / Denum;
	unit(double value) : value{ value } {}

public:

	void __set(double x) { value = x / base; }
	double __get() const { return value * base; }

	static unit one() { return unit(1); }

	unit() : value(0) {}

	template< typename T_rhs >
	unit & operator=(const T_rhs & rhs) {
		__set(rhs.__get());
		return *this;
	}

	unit operator*( double rhs ) const {
		return unit{ value * rhs };
	}

	unit operator/( double rhs ) const {
		return unit{ value / rhs };
	}

	double operator/( const unit & rhs ) const {
		return value / rhs.value;
	}

};

using length_in_cm = unit< 1, 1 >;
using length_in_inch = unit< 254, 100 >;

template< typename T >
T & operator<<(T &lhs, const length_in_cm & x) {
	return lhs << x / length_in_cm::one() << " cm";
}

template< typename T >
T & operator<<(T &lhs, const length_in_inch & x) {
	return lhs << x / length_in_inch::one() << " inch";
}

length_in_inch operator "" _inch( long double x ){ 
   return length_in_inch::one() * x;
}

int main(int argc, char *argv[]) {
	//std::cout << "Units\n";

	length_in_cm my_length;
	length_in_inch also_my_length;

	my_length = length_in_cm::one() * 185.0;
	also_my_length = my_length;

	std::cout << my_length << "\n";
	std::cout << also_my_length << "\n";

	auto length = 70.0_inch;
	my_length = length;
	also_my_length = my_length;

	std::cout << length << "\n";
	std::cout << my_length << "\n";
	std::cout << also_my_length << "\n";

	// std::cout << "Terminating application\n";
	return 0;
}
