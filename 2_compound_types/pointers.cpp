#include <iostream>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main() {
	/*int a = 0;
	int* p = &a;
	std::cout << p << '\n';
	int** pp = &p;
	std::cout << pp << '\n';

	std::cout << *pp << ' ' << *p << ' ' << **pp << '\n'; 
	*/

	int a = 1;
	int*p = &a;
	
	void* ppp = p;

	{	
		int b = 2;
		int* pp = &b;

		std::cout << p << ' ' << pp << ' ' << pp - p << '\n';
	}
	//swap(&a, &b);
	//std::cout << a << ' ' << b << '\n';
}	
