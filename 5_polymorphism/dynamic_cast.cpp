#include <iostream>

// RTTI
// Run-Time Type Information 

struct Base {
	virtual ~Base() = default;
};

struct Derived: Base {};

int main() {
	
	Derived d;
	Base bb;
	Base& b = bb;

	std::cout << typeid(b).name() << '\n';
}
