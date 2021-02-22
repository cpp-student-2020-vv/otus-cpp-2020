namespace otus_cpp::hw02::math {
/**
 * @brief Static (compile-time) templated math factorial (N!).
 *
 * @tparam N given input number
 */
template <unsigned int N>
struct Factorial {
  int constexpr static value = N * Factorial<N - 1>::value;
};

/**
 * @brief End of recursion specialization for recursive templated static
 * (compile-time) factorial (N!) func.
 *
 * @tparam  implicit zero
 */
template <>
struct Factorial<0> {
  int constexpr static value = 1;
};

/**
 * @brief Wrapper for static (compile-time) factorial (N!) function, converting
 * its syntax to more convinient form (similar to regular functions).
 *
 * @tparam N given input number
 * @return constexpr int computed factorial
 */
template <unsigned int N>
constexpr int factorial() {
  return Factorial<N>::value;
}

/**
 * @brief Dynamic (runtime) version of factorial (N!) function.
 *
 * @param n given input number
 * @return constexpr unsigned long int
 */
constexpr unsigned long int factorial(unsigned int n) {
  return (n > 0) ? n * factorial(n - 1) : 1;
}
}  // namespace otus_cpp::hw02::math