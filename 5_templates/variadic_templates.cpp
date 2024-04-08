#include <iostream>

// 5.8. Variadic templates (since c++11)

void print() {}

template <typename T, typename... Args>
void print(T value, Args... args) {
	std::cout << value << ' ';
	print(args...);
}

int main() {

	print(1, 2, "abc", 'x', 5.0);
}
