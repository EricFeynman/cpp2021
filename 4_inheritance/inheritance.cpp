#include <iostream>

// IV. Inheritance 

// 4.1. Private, public and protected inheritance

struct Base {
	int x = 1;
public:
	void f() {
		std::cout << 1 << '\n';
	}
};

struct Derived: private Base {
	int y = 2;
	friend int main();

	void g() {
		f();
		std::cout << 2 << '\n';
	}
};

struct Subderived: public Derived {
	int z = 3;

	void h() {
		f();
	}
};

int main() {

	Subderived d;
	d.f();
	std::cout << sizeof(d) << '\n';
}
