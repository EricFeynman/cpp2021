#include <iostream>

// 5.5. Basic template metaprogramming.

template <int N>
struct Fibonacci {	
	static const int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<1> {
	static const int value = 1;
};

template <>
struct Fibonacci<0> {
	static const int value = 0;
};

template <int N, int K>
struct IsPrimeHelper {
	static const bool value = N % K != 0 && IsPrimeHelper<N, K-1>::value;
};

template <int N>
struct IsPrimeHelper<N, 1> {
	static const bool value = true;
};

template <int N>
struct IsPrime {
	static const bool value = IsPrimeHelper<N, N-1>::value;
};

int main() {
	std::cout << IsPrime<31>::value;
}
