#include <iostream>

// 5.3. Template specialization.

// Full specialization vs. partial specialization.

template <typename T>
struct S;
/*{
	void f() {
		std::cout << 1 << '\n';
	}
};*/

template <typename T>
struct S<T, int> {
	void f() {
		std::cout << 2 << '\n';
	}
};	

template <typename T, typename U>
void f(T, U) {
	std::cout << 1 << '\n';
}

typename <>
void f(int, int) {
	std::cout << 3 << '\n';
}

template <typename T>
void f(T, T) {
	std::cout << 2 << '\n';
}

int main() {
	f<int, double>(0, 0);
	//S<const double&> s;
	//s.f();
}
