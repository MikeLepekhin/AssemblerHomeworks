#include <cstdio>
#include <ctime>
#include <chrono>
#include <iostream>

template<class HashTable>
void simpleTest() {
    std::cout << "simpleTest\n";

    HashTable hash_table;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
     
    
    for (std::string s: {"1", "2", "3", "4", "5", "10005000"}) {
        hash_table.insert(s);
    }

    size_t count = 0;
    for (std::string s: {"5", "6", "7", "8", "9", "10005000"}) {
        count += hash_table.find(s);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << '\n';

    std::cout << count << " items were found\n";
}
