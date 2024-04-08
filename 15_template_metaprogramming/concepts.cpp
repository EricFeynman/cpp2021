#include <iostream>
#include <vector>
#include <list>
#include <concepts>

// 15.7. Concepts (since c++20)

template <typename T>
concept Polymorphic = std::is_polymorphic_v<T>;

//template <Polymorphic T>
void f(Polymorphic auto);

//template <std::input_iterator InputIter, std::output_iterator OutputIter>
//OutputIter copy(InputIter from, InputIter to, OutputIter where);

template <std::input_iterator Iter>
void f(Iter iter, int n) {
	std::cout << 1;
}

template <std::random_access_iterator Iter>
void f(Iter iter, int n) {
	std::cout << 2;
}

int main() {
	std::vector<int> v(10);
	f(v.begin(), 0);

	std::list<int> l(10);
	f(l.begin(), 0);
}
