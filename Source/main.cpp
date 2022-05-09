#include "SimpleHash.h"

int main(const int argc, const char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: ./SimpleHash data.txt" << std::endl;
        return -1;
    }

    // Create table and print results
    SimpleHash hashTable;
    std::cout << "New table" << std::endl;
    hashTable.Print();
    std::cout << std::endl << "After reading in file" << std::endl;
    hashTable.ReadInDataFile(argv[1]);
    hashTable.Print();
    return 0;
}
