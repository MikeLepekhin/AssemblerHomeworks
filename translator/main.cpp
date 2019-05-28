#include <iostream>
#include <cstring>

#include "common_classes.h"
#include "translator.h"

void showUsage() {
  printf("usage:\n");
  printf("translator [-S|-b] myasm_binary result_file\n");
  printf("modes:\n");
  printf("-S - translate to x86 text\n");
  printf("-b - translate to x86 binary file\n");
}

char getFlag(char* str) {
  if (strlen(str) != 2 || str[0] != '-') {
    return '?';
  }
  return str[1];
}

void writeHeader(char* output_filename) {
  SmartFile header_file("header.asm");

  if (!header_file.getFile()) {
    printf("header file was not found");
    exit(0);
  }

  SmartFile output_file(output_filename, "w");
  FILE* header_ptr = header_file.getFile();
  FILE* output_ptr = output_file.getFile();

  char ch;
  while( ( ch = fgetc(header_ptr) ) != EOF ) {
    fputc(ch, output_ptr);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("the number of arguments is too low!\n");
    showUsage();
    return 0;
  }
  if (argc > 4) {
    printf("the number of arguments is incorrect!\n");
    showUsage();
    return 0;
  }

  bool need_binary = false;

  char* input_filename = argv[1];
  char* output_filename = argv[2];

  if (argc == 4) {
    if (getFlag(argv[1]) == 'b') {
      need_binary = true;
    } else if (getFlag(argv[1]) != 'S') {
      printf("unexpected flag %s\n", argv[1]);
      showUsage();
      return 0;
    }
    input_filename = argv[2];
    output_filename = argv[3];
  }

  SmartFile input_file(input_filename);

  if (!input_file.getFile()) {
    printf("file %s doesn't exist\n", input_filename);
    return 0;
  }
  writeHeader(output_filename);
  SmartFile output_file(output_filename, "a");

  translate(input_file.getFile(), output_file.getFile());

  if (need_binary) {
    std::string nasm_str = "nasm -f elf64 " + std::string(input_filename) + " -o " + std::string(input_filename) + ".o";
    system(nasm_str.c_str());
  }

  printf("good bye!\n");
  return 0;
}