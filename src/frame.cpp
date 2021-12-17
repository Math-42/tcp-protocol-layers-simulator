#include "frame.hpp"

void printBytes(std::vector<bool> bits) {
    std::cout << std::endl;
    int i = 1;
    int j = 1;
    for (auto bit : bits) {
        std::cout << bit;
        i = i % 8 == 0 ? 1 : i + 1;
        if (i == 1) std::cout << " ";
        j = j % 32 == 0 ? 1 : j + 1;
        if (j == 1) std::cout << std::endl;
    }
    
	std::cout << std::endl << std::endl;
}

void printStream(std::vector<bool> bits) {
    std::cout << std::endl;
    int i = 1;
    for (auto bit : bits) {
        std::cout << bit;
        i = i % 16 == 0 ? 1 : i + 1;
        if (i == 1) std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void printDiff(std::vector<bool> original, std::vector<bool> newVersion) {
    std::cout << std::endl;
    for (int i = 0; i < original.size() ; i++) {
        std::cout << ((original[i] != newVersion[i]) ? "\033[1m\033[31m" : "\033[0m\033[0m") << original[i] <<
            "\033[0m\033[0m";
        ;
        if ((i+1) %16 == 0) std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}