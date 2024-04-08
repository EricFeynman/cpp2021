#include <iostream>
#include <string>

struct S;

struct S {
	int x = 0;
	char c = 'a';
	std::string str;
 	
	struct SS {
		int a = 1;
		int b = 2;
	};

	int f(double d);

	S get() {
		std::cout << "Get called!\n";
		return *this;
	}
};

int S::f(double d) {
	std::cout << "Ahaha!" << d << '\n';
	return x + d;
}

int main() {

	S s{1, 'x', "abcde"};
	std::cout << s.x << '\n';
	std::cout << s.str.size() << '\n';

	S* p = &s;
	std::cout << p->c;

	std::cout << s.f(3.14) << '\n';

	S::SS ss;
	std::cout << ss.b << '\n';
}

