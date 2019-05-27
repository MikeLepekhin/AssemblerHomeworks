//
// Created by mike on 27.05.19.
//

#ifndef TRANSLATOR_COMMON_CLASSES_H
#define TRANSLATOR_COMMON_CLASSES_H

template<class T>
struct Command {
  size_t cmd_id;
  std::string cmd_name;
  size_t arg_cnt;
  std::vector<std::pair<T, int>> args;
};

bool isJump(const std::string& cmd_name) {
  return cmd_name == "jmp" || cmd_name == "call" || cmd_name == "je" || cmd_name == "jne" ||
    cmd_name == "jl" || cmd_name == "jle";
}

#endif //TRANSLATOR_COMMON_CLASSES_H
