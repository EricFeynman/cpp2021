#include <iostream>

void f(int& r);

int main() {
	int x = 0;
	int* p = &x;
	int& r = x;
	int y = 1;
	double d = 3.14;

	std::cout << &x << ' ' << &p << ' ' << &y << ' ' << &d << '\n';
	// memory layout:
	// [x(4)][y(4)][ p(8) ][ d(8) ]
	// Where is r? Nowhere!
	
	f(x);
}

void f(int& r) {
	int x = 0;
	int* p = &x;
	std::cout << &r << '\n';
	std::cout << &x << ' ' << &p << '\n';
	// ....[x(4)][ p==&x (8) ]

	std::cout << &p-1 << ' ' << *(&p-1) << '\n';
	std::cout << &p-2 << ' ' << *(&p-2) << '\n';
	std::cout << &p-3 << ' ' << *(&p-3) << '\n';
	// [ &x==r(8) ][ ........|....[x(4)]|[ p==&x(8) ]]

	for (int i = 4; i <= 200; ++i)
		std::cout << &p-i << ' ' << *(&p-i) << '\n';
}	
