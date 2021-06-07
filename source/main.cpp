#include "hash.hpp"

#include <iostream>

int main() {
    unsigned int i = 0;
    while (true) {
        std::string sha = hash::SHA256(std::to_string(i));
        if (hash::lessThanDifficulty(sha, 16)) {
            std::cout << i << " with hash: " << sha << " is the first string(number) with less than 16 diff" << '\n';
            break;
        }
        i++;
    }
}