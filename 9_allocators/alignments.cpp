#include <iostream>
#include <cstddef>

// 9.5. Alignments.

// 9.6. Bit fields.

struct /*alignas(std::max_align_t)*/  Pool {
	char arr[100'000];

};

struct S {
	uint8_t c: 2;
	uint8_t cc: 3;
	int8_t i: 2;
};
 
int main() {

	std::cout << sizeof(S) << ' ' << alignof(S) << '\n';
	std::cout << alignof(Pool) << ' ' << alignof(std::max_align_t) << '\n';

}
