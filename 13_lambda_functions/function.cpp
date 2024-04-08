#include <iostream>
#include <functional>

// 13.4. std::function and its usage.

int foo(int x, int y) {
	return x + y;
}

struct Bar {
	int operator()(int x, double y ) {
		return x - y;
	}
};

struct S {
	int y = 1;
	void goo(int x) const {
		std::cout << x + y << '\n';
	}
};

int main() {
	
	void (S::* p)(int) const = &S::goo;
	S s;
	(s.*p)(5);

	std::function<void(S&, int)> memfn = &S::goo;

	memfn(s, 5);

	return 0;

	std::function<int(int, double)> f = foo;

	std::cout << f(5, 3.0) << '\n';

	f = Bar();

	std::cout << f(5, 3.0) << '\n';

	f = [](int x, double y) { return x * y; };

	std::cout << f(5, 3.0) << '\n';
}
