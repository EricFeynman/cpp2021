#include <iostream>

// 4.2. Visibility and accessibility of fields and methods with inheritance.

struct Base{
	int x = 1;
protected:
	void f() {
		std::cout << 1 << '\n';
	}
	Base(int x): x(x) {}
};

struct Derived: Base {
	int x = 2;
	using Base::Base;
	using Base::f;
	void f(int) {
		std::cout << 2 << '\n';
	}
};

int main() {

	Derived d = 5;
	d.f();

}

