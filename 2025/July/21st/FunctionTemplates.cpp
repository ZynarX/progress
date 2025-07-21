#include <iostream>

template <typename T, typename U, int N>
auto AddAndMultiply(T a, U b) -> decltype((a + b) * N);

int main()
{
    std::cout << AddAndMultiply<int, double, 3>(4, 2.5) << std::endl;
    std::cout << AddAndMultiply<float, double, 7>(2.7f, 3.14159) << std::endl;
}

template <typename T, typename U, int N>
auto AddAndMultiply(T a, U b) -> decltype((a + b) * N)
{
    return (a + b) * N;
}
