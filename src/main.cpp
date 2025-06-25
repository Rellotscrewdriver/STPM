#include <iostream>
#include <fmt/core.h>
#include "dog.h"
using namespace std;

/**
 * An example.
 *
 * @tparam T Template parameter.
 *
 * @param x Input parameter.
 * @param[out] y Output parameter.
 *
 * @return Return value.
 *
 * @tip There are plenty more demos [here](/demo).
 */
template <class T>
int f(int x, int& y);

/**
 * @brief this is a main function
 *
 * @return int
 */
int main() { 
    dog* d = new dog("Milky", 5);
    fmt::print("Hello, {}!\n", "world");
    return 0;
}