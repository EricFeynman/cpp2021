#include <iostream>

// 3.2. Access modifiers, incapsulation.

struct S {
private:
	friend void g(int);

	int a;
	void f(int) { std::cout << 1; }
public:
	double d;
	void f(double) { std::cout << 2; }

};

void g(int x) {
	S s;
	s.f(x);
}

int main() {
	S s;

	g(1);

	//s.a;
	

	//s.f(0);
}
