#include <iostream>
#include <string>
#include <list>

#include "opt_hash_table.h"
#include "opt_list.h"
#include "test.h"

int main() {
    simpleTest<OptHashTable>();   
    listTest<OptList<size_t>>(10);   
    stdlistTest(10);   
    listTest<OptList<size_t>>(10000);   
    stdlistTest(10000);   
    listTest<OptList<size_t>>(100000000);   
    stdlistTest(100000000);   
    return 0;
}
