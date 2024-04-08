#include <iostream>

// 6.8.

struct Base {
	virtual void f(int x) {
		std::cout << x << '\n';
	}
};

struct Derived: Base {
	void f(int x) override {
		std::cout << -x << '\n';
	}
};

int main() {

	void (Base::* p)(int) = &Base::f;

	Derived d;
	Base& b = d;
	(b.*p)(1);

}
