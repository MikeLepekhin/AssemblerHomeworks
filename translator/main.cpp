#include <iostream>
#include <cstdio>

#include "translator.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "usage:\n";
    std::cout << "translator [-S] myasm_binary result_file\n";
    return 0;
  }
  return 0;
}