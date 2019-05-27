//
// Created by mike on 27.05.19.
//

#ifndef TRANSLATOR_COMMON_CLASSES_H
#define TRANSLATOR_COMMON_CLASSES_H

#include <iostream>
#include <vector>

template<class T>
struct Command {
  size_t cmd_id;
  std::string cmd_name;
  size_t arg_cnt;
  std::vector<std::pair<T, int>> args;
};

bool isJump(const std::string& cmd_name) {
  return cmd_name == "jump" || cmd_name == "call" || cmd_name == "je" || cmd_name == "jne" ||
    cmd_name == "jl" || cmd_name == "jle";
}

bool isJump(size_t cmd_id) {
  return cmd_id == 12 || cmd_id == 13 || cmd_id == 14 || cmd_id == 15 ||
    cmd_id == 16 || cmd_id == 17;
}

class SmartFile {
 private:
  FILE* file_{nullptr};

  void release() {
    if (file_ != nullptr) {
      fclose(file_);
    }
    file_ = nullptr;
  }

 public:
  SmartFile() {}

  SmartFile(const char* filename, const char* mode = "r") {
    file_ = fopen(filename, mode);
  }

  SmartFile(FILE* file) {
    file_ = file;
  }

  FILE* getFile() const {
    return file_;
  }

  void setFile(const char* filename, const char* mode = "r") {
    release();
    file_ = fopen(filename, mode);
  }

  ~SmartFile() {
    release();
  }
};

#endif //TRANSLATOR_COMMON_CLASSES_H
