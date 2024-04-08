#include <iostream>
#include <type_traits>

// 12.2. minimal version of shared_ptr.

// 12.5. custom deleter and allocator problem.

// 12.6. enable_shared_from_this

// 14.2. solution of custom deleter problem.

template <typename T>
struct enable_shared_from_this {

	std::weak_ptr<T> wp;

	std::shared_ptr<T> shared_from_this() const {
		return wp.lock();
	}
};

// CRTP 

class S: public enable_shared_from_this<S> {
public:
	shared_ptr<S> get_this() {
		return shared_from_this;
	}
};

namespace my {

template <typename T>
class shared_ptr {

	template <typename... Args>
	friend shared_ptr<T> make_shared(Args&&... args);

	struct BaseControlBlock {
		size_t shared_count;
		size_t weak_count;

		BaseControlBlock(const T&, size_t, size_t);

		virtual ~BaseControlBlock() = default;
	};

	template <typename Deleter, typename Alloc>
	struct ControlBlockDirect: BaseControlBlock {
		T* ptr;
		Deleter deleter;
		Alloc alloc;

		//ControlBlock(const T& object, size_t sc, size_t wc, const Deleter& deleter)
		//	: BaseControlBlock(object, sc, wc), Deleter(deleter)
		//{}
	};

	template <typename Alloc>
	struct ControlBlockMakeShared: BaseControlBlock {
		T object;
		Alloc alloc;

	};
	
private:
	ControlBlock* cb;
	T* ptr;
	//size_t* count;


private:
	shared_ptr(ControlBlock* pc);

public:
	shared_ptr(T* ptr): ptr(ptr), count(new int(1)) {
		
		if constexpr (std::is_base_of_v<enable_shared_from_this<T>, T>) {
			ptr->wp = *this;
		}

	}

	shared_ptr(const shared_ptr& other) noexcept
		: ptr(other.ptr), count(other.count)
	{
		++*count;
	}

	shared_ptr(shared_ptr&& other) noexcept
		: ptr(other.ptr), count(other.count)
	{
		other.ptr = nullptr;
		other.count = nullptr;
	}

	// TODO: assignment operaotrs

	~shared_ptr() {
		if (!cb) return;
		--cb->shared_count;
		if (cb->weak_count == 0 && cb->shared_count == 0) {
			delete cb;
			return;
		}
		if (cb->shared_count == 0) {
			// TODO: what if we were created by make_shared?
			cb->object.~T();
			//delete count;
			//delete ptr;
		}
	}
};

} // namespace

// 12.3. make_shared and make_unique

template <typename T, typename Alloc, typename... Args>
auto allocate_shared(Alloc& alloc, Args&&... args) {
	// TODO:
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
	return allocate_shared<T>(std::allocate<T>(), std::forward<Args>(args)...);
	//void* p = ::operator new(sizeof(T) + sizeof(size_t)); // TODO: alignment?
	//return shared_ptr<T>(new shared_ptr<T>::ControlBlock{
	//	T(std::forward<Args>(args)...), 1});

}

// since c++14
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

namespace my {

template <typename T>
class weak_ptr {
	// TODO: what if T and counters were created separately&
	ControlBlock* cb;

public:

	bool expired() const () {
		return cb && cb->shared_count == 0;
	}

	~weak_ptr() {
		if (!cb) return;
		--cb->weak_count;
		if (cb->weak_count == 0 && cb->shared_count == 0) {
			delete cb; // WRONG!
			// deallocate, not destroy!
		}
	}
};

} // namespace my

int main() {

	auto sp = make_shared<int>(5);

	auto sp = make_shared<std::string>(5, 'a');

	//int* p = new int(5);

	//shared_ptr<int> sp = p;

	//shared_ptr<int> sp2 = p;

}
