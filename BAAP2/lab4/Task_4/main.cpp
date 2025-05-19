#include <iostream>
#include "Vector.h"


int main() {
    Vector<int> vec;

    for (int var = 0; var < 10; ++var) {
        vec.push_back(var);
        std::cout << vec.capacity() << " ";
    }


    return 0;
}
