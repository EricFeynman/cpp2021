#include <iostream>
#include <variant>

// 14.5. std::variant (since c++17), its usage and implementation.

// 14.6. std::launder.

template <typename... Types>
union VariadicUnion {
	template <int N>
	char& get() {
		static_assert(N < 0, "N exceeds number of alternatives in variant");
	}

	template <typename T>
	void put(const T&) {
	       static_assert(std::is_same_v<T, void>, "fail");
      	}	       
};

template <typename Head, typename... Tail>
union VariadicUnion<Head, Tail...> {
	Head head;
	VariadicUnion<Tail...> tail;

	VariadicUnion() {}
	~VariadicUnion() {}

	template <int N>
	auto& get() {
		if constexpr (N == 0)
			return head;
		else
			return tail.template get<N-1>();
	}

	template <typename T>
	void put(const T& value) {
		if constexpr (std::is_same_v<T, Head>) {
			new(std::launder(&head)) T(value);
		} else {
			tail.template put<T>(value);
		}
	}

	template <typename T>
	void destroy() {
		// TODO
	}
};

template <size_t N, typename T, typename Head, typename... Tail>
struct index_by_type_impl {
	static constexpr size_t value = std::is_same_v<T, Head>
		? N
		: index_by_type_impl<N+1, T, Tail...>::value;
};

template <size_t N, typename T, typename Last>
struct index_by_type_impl<N, T, Last> {
	static constexpr size_t value = N;
};

template <typename T, typename... Types>
static constexpr size_t index_by_type = index_by_type_impl<0, Types...>::value;

template <typename... Types>
class Variant;

template <typename T, typename... Types>
struct VariantAlternative {

	using Derived = Variant<Types...>;

	static constexpr size_t index = index_by_type<T, Types...>;

	VariantAlternative() {}
	~VariantAlternative() {}

	VariantAlternative(const T& value) {
		auto ptr = static_cast<Derived*>(this);
		ptr->storage.template put<T>(value);
		ptr->index = index;
	}

	void destroy() {
		auto ptr = static_cast<Derived*>(this);
		if (ptr->index == index) {
			ptr->storage.template destroy<T>();
		}
	}
};

template <typename... Types>
class Variant
	: private VariantStorage<Types...>
	, private VariantAlternative<Types, Types...>...
{
private:
	template <size_t N, typename... Ts>
	friend auto& get(Variant<Ts...>& v);

	template <typename T, typename... Ts>
	friend struct VariantAlternative;

private:
	VariadicUnion<Types...> storage;
	size_t index;
public:
	using VariantAlternative<Types, Types...>::VariantAlternative...;

	~Variant() {
		// fold expression (since c++17)
		(VariantAlternative<Types, Types...>::destroy(),  ...);
	}
};

template <size_t N, typename... Types>
auto& get(Variant<Types...>& v) {
	if (v.index == N)
		return v.storage.template get<N>();
	throw std::bad_variant_access();
}

/*template <typename T, typename... Types>
T& get(Variant<Types...>& v) {
	return get< index_by_type<T, Types...> >(v);
}*/

int main() {

	Variant<int, float, std::string> v = 5.0f;

	std::cout << get<1>(v) << '\n';

	//v = 5;

	//std::cout << get<int>(v) << '\n';

	//v = 5.0f;
	
	//std::cout << get<float>(v) << '\n';

	//std::cout << std::holds_alternative<float>(v) << '\n';
}
