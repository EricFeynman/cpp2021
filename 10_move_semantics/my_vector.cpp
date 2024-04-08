#include <iostream>
#include <vector>

// 8.3. Internals of std::vector.

// 10.2. Move-constructor and move-assignment operator.
// The Rule of Five.

// 10.6. Perfect forwarding problem.

// 10.7. std::forward implementation

// 10.9. mov_if_noexcept.

template <typename T>
T&& forward(std::remove_reference_t<T>& x) noexcept {
	return static_cast<T&&>(x);
}

// rarely used
template <typename T>
T&& forward(std::remove_reference_t<T>&& x) noexcept {
	return static_cast<T&&>(x);
}

template <typename T, typename Alloc = std::allocator<T>>
class vector {
private:
	T* arr;
	size_t sz;
	size_t cap;
	Alloc alloc;
	
	using AllocTraits = std::allocator_traits<Alloc>;

public: 

	vector(const vector& other);

	vector& operator=(const vector& other);
	
	// TODO: WTF is vector&& ?
	vector(vector&& other) noexcept(noexcept(alloc(std::move(other.alloc))))
		: arr(other.arr), sz(other.sz), cap(other.cap)
		, alloc(std::move(alloc))
	{
		//other.clear(); // wrong
	}

	vector& operator=(vector&& other) {
		clear(); // wrong

		arr = other.arr;
		sz = other.sz;
		cap = other.cap;
		alloc = std::move::move(other.alloc)

		//other.clear(); //wrong
	}

	// [XXXX.] <-
	// [XXXX.......]

	size_t size() const;
	void resize(size_t newsize);

	size_t capacity() const;

	void reserve(size_t newcap) {
		if (newcap <= cap) return;

		//T* newarr = reinterpret_cast<T*>(new uint8_t[newcap * sizeof(T)]); // TODO: avoid reinterpret_cast
		//T* newarr = alloc.allocate(newcap);
		T* newarr = AllocTraits::allocate(alloc, newcap);


		for (size_t i = 0; i < sz; ++i) {
			try {
				//new(newarr+i) T(arr[i]);
				//alloc.construct(newarr+i, arr[i]);
				AllocTraits::construct(alloc, newarr+i, std::move_if_noexcept(arr[i])); // TODO: always move if T is not copyable
			} catch(...) {
				for (size_t j = 0; j < i; ++j) {
					//(newarr+i)->~T();
					//alloc.destroy(newarr+i);
					AllocTraits::destroy(alloc, newarr+i);
				}
				//delete[] reinterpret_cast<uint8_t*>(newarr);
				//alloc.deallocate(newarr, newcap);
				AllocTraits::deallocate(alloc, newarr, newcap);
				throw;
			}
		}

		for (size_t i = 0; i < sz; ++i) {
			//(arr+i)->~T();
			//alloc.destroy(arr+i);
			AllocTraits::destroy(alloc, arr+i);
		}

		//delete[] reinterpret_cast<uint8_t*>(arr);
		//alloc.deallocate(arr, cap);
		AllocTraits::deallocate(alloc, arr, cap);
		cap = newcap;
		arr = newarr;
	}
	
	void push_back(const T& value) { 
		emplace_back(value);
	}

	void push_back(T&& value) {
		emplace_back(std::move(value));
	}
	
	template <typename... Args>
	void emplace_back(const Args&&... args) {
		if (sz >= cap) {
			reserve(cap * 2);
		}
		// put new element on its place 
		//new(arr+sz) T(value); //placement new
		AllocTraits::construct(alloc, arr+sz, std::forward<Args>(args)...);
		// TODO: exception-safety??!!
		//arr[sz] = value; // WRONG!!!
		++sz;
	}

	void pop_back() {
		--sz;
		(arr+sz)->~T();
	}
	
	struct iterator {
	private:
		T* ptr;
	public:
		T& operator*() const {
			return *ptr;
		}	
	};

};

// 8.4. vector<bool>

template <>
class vector<bool> {
private:
	uint8_t* arr;
	size_t sz;
	size_t cap;

	struct BitReference {
		uint8_t* cell;
		uint8_t bit;

		BitReference& operator=(bool b) {
			//sets corresponding bit in cell to b
			return this;
		}
		operator bool() const {
			return *cell & (1 << bit);
		}

		BitReference& operator=(const BitReference&) = default;
	};

public:
	
	BitReference operator[](size_t index) {
		return {arr + index / 8, index % 8};
	}
};

int main() {

	std::vector<bool> v(5, false);
	v[2] = true; // assignment to rvalue!

	std::vector<bool>::iterator it = v.begin();

	std::cout << typeid(*it).name() << '\n';

	std::cout << typeid(v[2]).name() << '\n';

	/*vector<int> v = {1, 2, 3, 4, 5};

	int& x = v[3];
	int* p = &v[3];
	vector<int>::iterator it = v.begin();

	v.push_back(6);

	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);

	std::cout << x; // UB!!!
	std::cout << *it; //UB!!! Iterator invalidation*/
}
