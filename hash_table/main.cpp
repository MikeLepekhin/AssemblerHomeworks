#include <iostream>
#include <string>

#include "opt_hash_table.h"
#include "opt_list.h"
#include "test.h"

int main() {
    simpleTest<OptHashTable>();   
    listTest<OptBidirectionalList<int>>();   
    return 0;
}
