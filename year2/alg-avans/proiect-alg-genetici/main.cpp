#include <iostream>

#include "InputReader.h"
#include "Algorithm.h"

int main()
{

    std::srand(std::time(nullptr));
    InputReader reader("input.txt");
    Algorithm algorithm(reader.read(), "evolutie.txt");
    algorithm.run();
    return 0;
}
