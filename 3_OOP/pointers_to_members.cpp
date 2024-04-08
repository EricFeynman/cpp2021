#include <iostream>

struct S {
	int x;
	double d;
public:
	void f(char c) {}
};

int main() {

	int S::* p = &S::x;

	void (S::* pf)(char) = &S::f;

	S s{5, 3.0};

	S* ps = &s;

	(ps->*pf)('a');

	std::cout << sizeof(p) << ' ' << ps->*p << '\n';

}
