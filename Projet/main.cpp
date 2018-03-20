#include <iostream>
#include "src/CNF.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    Generator::GenereFile (20, 50);

    CNF::readFromFile("InfoClauses.txt");

    return 0;
}