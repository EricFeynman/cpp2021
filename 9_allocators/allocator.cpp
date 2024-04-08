#include <iostream>

// IX. Allocators and memory management.

// 9.1. Idea and basic usage of allocators.

template <typename T>
struct allocator {
	
	T* allocate(size_t n) {
		return reinterpret_cast<T*>(new char[n * sizeof(T)]);

	}

	void deallocate(T* ptr, size_t) {
		delete[] reinterpret_cast<char*>(ptr);
	}

	template <typename... Args>
	void construct(T* ptr, const Args&&... args) {
		new(ptr) T(std::forward<Args>(args)...);
	}

	void destroy(T* ptr) {
		ptr->~T();
	}
};

template <typename T>
struct PoolAllocator {

};
