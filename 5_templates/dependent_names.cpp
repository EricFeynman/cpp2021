#include <iostream>

// 5.6. Dependent names in templates.

template <typename T>
struct S {
	static const int x = 1;
};

template <>
struct S<int> {
	using x = int;
};

int a = 0;

template <typename T>
void f(T y) {
	typename S<T>::x* a;
}

template <typename T>
struct SS {
	template <typename K>
	struct A {};
};

template <>
struct SS<int> {
	static const int A;
};

template <typename T, typename K>
void g() {
	typename SS<T>::template A<K> a;
}

int main() {
	g<char, int>();

}
