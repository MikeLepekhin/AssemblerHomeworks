//
// Created by mike on 27.05.19.
//

#ifndef TRANSLATOR_TRANSLATOR_H
#define TRANSLATOR_TRANSLATOR_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <cassert>

#include "file_buffer.h"
#include "exception.h"
#include "common_classes.h"

void replace(std::string& str, const std::string& from, const std::string& to) {
  size_t start_pos = str.find(from);

  //std::cout << "# REPLACE\n";
  //std::cout << str << ' ' << from << ' ' << to << '\n';
  assert(start_pos != std::string::npos);
  str.replace(start_pos, from.length(), to);
}

std::string getRegisterX86(size_t register_id) {
  assert(register_id > 0 && register_id <= 5 &&
         "incorrect register! only rax, rbx, rcx, rdx and rex are allowed");

  switch (register_id) {
    case 1:
      return "r8";
    case 2:
      return "r11";
    case 3:
      return "r13";
    case 4:
      return "r14";
    case 5:
      return "r15";
  }
  return "r228";
}

void readCommand(size_t cmd_id,
                 size_t arg_cnt, size_t support_mask,
                 std::vector<std::pair<double, int>>& arg_values, FileBuffer& fbuffer) {

  size_t arg_cnt_file = fbuffer.readFromBuffer<size_t>();

  std::cout << "argument cnt in file: " << arg_cnt_file << '\n';

  if (arg_cnt == 0) {
    return;
  }

  for (size_t arg_id = 0; arg_id < arg_cnt; ++arg_id) {
    int cur_type = fbuffer.readFromBuffer<int>();
    double cur_val = fbuffer.readFromBuffer<double>();

    arg_values.push_back({cur_val, cur_type});
    std::cout << cur_val << ' ' << cur_type << '\n';
  }
  std::cout << "real arg number:" << ' ' << arg_cnt << " arguments\n";
}

std::string getRamObject(int encoded) {
  int reg_num = (encoded >> 8);
  int shift = encoded & ((1 << 8) - 1);

  std::string reg = reg_num > 0 ? getRegisterX86(reg_num) : "";
  std::string shift_str = shift > 0 ? std::to_string(shift) : "";

  return std::string("[") + reg + (reg_num > 0 && shift > 0 ? "+" : "") + shift_str + "]";
}

std::string decodeArgument(const std::pair<double, int>& arg) {
  if (arg.second < 1 || arg.second > 3) {
    throw IncorrectArgumentException("Argument type should be a number from 1 to 3");
  }
  switch (arg.second) {
    case 1:
      return std::to_string(static_cast<size_t>(arg.first));
    case 2:
      return getRegisterX86(static_cast<size_t>(arg.first));
    case 3:
      return getRamObject(static_cast<int>(arg.first));
    default:
      throw IncorrectArgumentException("Argument type should be a number from 1 to 3");
  }
}

void decodeCommand(Command<double>& command, size_t cmd_order,
                   const std::set<size_t>& jumps_to, FILE* decode_file) {
  if (jumps_to.find(cmd_order) != jumps_to.end()) {
    fprintf(decode_file, "\nlabel_cmd_");
    fprintf(decode_file, "%zu:\n", cmd_order);
  }


  for (size_t arg_id = 0; arg_id < command.arg_cnt; ++arg_id) {
    if (!isJump(command.cmd_id)) {
      replace(command.cmd_name, "<arg" + std::to_string(arg_id) + ">", decodeArgument(command.args[arg_id]));
    } else {
      replace(command.cmd_name, "<arg" + std::to_string(arg_id) + ">", "label_cmd_" + decodeArgument(command.args[arg_id]));
    }
  }

  fprintf(decode_file, "%s", command.cmd_name.c_str());
  fprintf(decode_file, "\n");
}

void translateCommand(size_t cmd_id, const char* code_x86, size_t arg_cnt, size_t support_mask,
                        FileBuffer& fbuffer, std::vector<Command<double>>& commands,
  std::set<size_t>& jumps_to, FILE* decode_file) {

  std::vector<std::pair<double, int>> args;

  readCommand(cmd_id, arg_cnt, support_mask, args, fbuffer);
  if (isJump(cmd_id)) {
    jumps_to.insert(static_cast<size_t>(args[0].first));
  }
  commands.push_back(Command<double>{cmd_id, code_x86, arg_cnt, args});
  std::cout << "translated\n";
}

void translate(FILE* binary_file = stdin, FILE* decode_file = stdout) {
  FileBuffer fbuffer(binary_file);

  std::set<size_t> jumps_to;
  std::vector<Command<double>> commands;

  while (!fbuffer.done()) {
    size_t cur_cmd_id = fbuffer.readFromBuffer<size_t>();
      //std::cout << "command " + std::string(name) + " with " + std::to_string(arg_cnt) + " arguments in switch\n";\
      translateCommand(cmd_id, code_x86, arg_cnt, arg_mask, fbuffer, commands, jumps_to, decode_file);\

    switch (cur_cmd_id) {
#define COMMAND(cmd_id, name, arg_cnt, arg_mask, code_x86) \
    case cmd_id :\
      translateCommand(cmd_id, code_x86, arg_cnt, arg_mask, fbuffer, commands, jumps_to, decode_file);\
      break;

#include "commands.h"
#undef COMMAND

      default: {
        throw IncorrectArgumentException(std::string("incorrect command id ") + std::to_string(cur_cmd_id));
      }
    }
  }

  for (size_t cmd_order = 0; cmd_order < commands.size(); ++cmd_order) {
    decodeCommand(commands[cmd_order], cmd_order, jumps_to, decode_file);
  }

  std::cout << "function translate is finished\n";
}

#endif //TRANSLATOR_TRANSLATOR_H
