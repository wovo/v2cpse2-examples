#include <stdlib.h>

struct person {
	char name[20];
	int age;
};

int main() {
   
	person *p = static_cast< person *>( malloc(sizeof(person)));
	free( p );

	person *p2 = new person();
	delete p2;

	person *p3 = new person[ 20 ];
	delete[] p3;

	return 0;
}