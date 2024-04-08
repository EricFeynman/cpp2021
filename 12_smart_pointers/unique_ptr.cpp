#include <iostream>
#include <memory>

// XII. Smart pointers.

// 12.1. unique_ptr (since c++11)

// RAII

namespace my {

template <typename T>
struct default_delete {
	void operator()(T* ptr) const {
		delete ptr;
	}
};

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
private:
	T* ptr;
	Deleter del;

public:
	unique_ptr(T* ptr): ptr(ptr) {}

	unique_ptr(const unique_ptr&) = delete;

	unique_ptr(unique_ptr&& other) noexcept: ptr(other.ptr) {
		other.ptr = nullptr;
	}

	// TODO: assignment operators

	~unique_ptr() {
		del(ptr);
	}
};

}

int main() {
	auto p = std::unique_ptr<int>(new int(5));

	std::cout << sizeof(p);
}


