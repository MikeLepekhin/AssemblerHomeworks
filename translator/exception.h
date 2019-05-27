//
// Created by mike on 27.05.19.
//

#ifndef TRANSLATOR_EXCEPTION_H
#define TRANSLATOR_EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

struct TranslatorException : public std::exception {
  std::string message;
  std::string function_name;

  TranslatorException(const std::string& message = "", const std::string& function_name = ""):
    message(message), function_name(function_name) {}
};

struct IncorrectArgumentException : public TranslatorException {
  IncorrectArgumentException(const std::string& message, const std::string& function_name = ""):
    TranslatorException(message, function_name) {}
};

std::ostream& operator<<(std::ostream& os, const TranslatorException& iaexception) {
  os << "!!! Exception: " << iaexception.message;
  if (!iaexception.function_name.empty()) {
    os << "(" << iaexception.function_name << ")";
  }
  os << '\n';
  return os;
}

#endif //TRANSLATOR_EXCEPTION_H
