#include <iostream>

struct S {
	int a = 1;
	double d;
	int b;
};

int main() {
	int a;
	double d;
	int b;

	std::cout << &a << ' ' << &d << ' ' << &b << ' ' << '\n';
	std::cout << sizeof(S) << '\n';
	S s;

	std::cout << reinterpret_cast<int&>(s);
}
