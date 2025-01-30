#include <iostream>
#include <fstream>

const std::string PATH = "./data/raw/01302019.NASDAQ_ITCH50";

import parser;

int main() {
    std::ifstream inputFile(PATH, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file: " << PATH << std::endl;
        return EXIT_FAILURE;
    }
    parse(inputFile, std::cout);

    return EXIT_SUCCESS;
}