#include <iostream>

// 5.2. Overloading of template functions.

template <typename T = int>
void f(T, T) {
	std::cout << sizeof(T) << '\n';
}

template <typename T, typename U>
void f(T, U) {
	std::cout << 2 << '\n';
}

/*template <typename T = int>
T f(int) {
	std::cout << 2 << '\n';
	return T();
}*/

int main() { 
	f<int>(0.0, 0.0);
	//f<int>(0);
	//f('a');
}
