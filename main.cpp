#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include "HashTable.h"

int main() {
    HashTable table(60);
    for(int i = 0; i < 60; ++i) {
        table.insert(std::string("key") + std::to_string(i), i*2);
    }
    std::cout << table << std::endl;
    std::cout << "Load Factor: " << table.getLoadFactor() << std::endl;
    // table.remove("key0");
    // std::cout << "removing" << std::endl;
    // std::cout << table << std::endl;
    // std::cout << "Load Factor: " << table.getLoadFactor() << std::endl;
    for(int i = 0; i < 60; ++i) {
        std::cout << std::string("key") + std::to_string(i) << ": find" << table[std::string("key") + std::to_string(i)] << std::endl;
    }
    return 0;
}