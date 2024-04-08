#include <iostream>
#include <vector>

// 5.4. Non-type template parameters.

/*template <typename T, size_t N>
class array {
private:
	T array[N];
public:

};*/

// Template template parameters.

template <typename T, template<typename, typename> class Container>
class Stack {
	Container<T, std::allocator<T>> container;
};

int main() {
	//std::array<int, 10> a;

	Stack<int, std::vector> st;
}
