#include <cstdio>
#include <ctime>
#include <chrono>
#include <iostream>
#include <algorithm>

template<class HashTable>
void simpleTest() {
    std::cout << "SimpleTest\n";

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
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << '\n';

    std::cout << count << " items were found\n";
}


template<class List>
void listTest(size_t item_cnt) {
    std::cout << "ListTest\n";

    List my_list;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
     

    for (size_t i = 0; i < item_cnt; ++i) {
        my_list.insert(i);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << '\n';
}


void stdlistTest(size_t item_cnt) {
    std::cout << "StdListTest\n";

    std::list<int> my_list;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
     

    for (size_t i = 0; i < item_cnt; ++i) {
        my_list.push_back(i);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << '\n';
}

template<class List>
void listFindTest(size_t item_cnt) {
    std::cout << "ListFindTest\n";

    List my_list;
    for (size_t i = 0; i < item_cnt; ++i) {
        my_list.insert(i);
    }
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
     

    size_t res = 0;
    for (size_t i = 0; i < item_cnt; ++i) {
        res += my_list.find(i);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << '\n';
}


void stdlistFindTest(size_t item_cnt) {
    std::cout << "StdListFindTest\n";

    std::list<int> my_list;
    for (size_t i = 0; i < item_cnt; ++i) {
        my_list.push_back(i);
    }
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
     

    size_t res = 0;
    for (size_t i = 0; i < item_cnt; ++i) {
        res += (std::find(my_list.begin(), my_list.end(), i) != my_list.end());
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << '\n';
}
