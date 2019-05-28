#define TWO_ARG_COMMAND(name) \
  "pop rbx\n"\
  "pop rax\n"\
   name" rax, rbx\n"\
  "push rax"\

#define CONDITIONAL_JUMP(name) \
  "pop rbx\n"\
  "pop rax\n"\
  "cmp rax, rbx\n"\
   name" <arg0>"\

COMMAND(1, "push", 1, 7,\
  "push <arg0>"\
)
COMMAND(2, "pop", 1, 6, \
  "pop <arg0>"\
)

COMMAND(3, "add", 0, 0,\
  TWO_ARG_COMMAND("add")\
)

COMMAND(4, "sub", 0, 0,\
  TWO_ARG_COMMAND("sub")\
)
COMMAND(5, "mul", 0, 0,\
  "pop rbx\n"\
  "pop rax\n"\
  "mul rbx\n"\
  "push rax"\
)
COMMAND(6, "div", 0, 0,\
  "xor rdx, rdx\n"
  "pop rbx\n"\
  "pop rax\n"\
  "div rbx\n"\
  "push rax"\
)
COMMAND(7, "sqrt", 0, 0,\
  "TODO"\
)
COMMAND(8, "dup", 0, 0,\
  "pop rax\n"\
  "push rax\n"\
  "push rax"\
)
COMMAND(9, "in", 1, 6,\
  "call my_in\n"\
  "mov <arg0>, [input]"\
)
COMMAND(10, "out", 1, 7,\
  "mov rax, <arg0>\n"\
  "call my_out"\
)
COMMAND(11, "end", 0, 0,\
  "jmp exit_program"\
)
COMMAND(12, "jump", 1, 1,\
  "jmp <arg0>"\
)
COMMAND(13, "call", 1, 1,\
  "call <arg0>"\
)
COMMAND(14, "je", 1, 1,\
  CONDITIONAL_JUMP("je")\
)
COMMAND(15, "jne", 1, 1,\
  CONDITIONAL_JUMP("jne")\
)
COMMAND(16, "jl", 1, 1,\
  CONDITIONAL_JUMP("jl")\
)
COMMAND(17, "jle", 1, 1,\
  CONDITIONAL_JUMP("jle")\
)
COMMAND(18, "ret", 0, 0,\
  "ret"\
)
COMMAND(27, "not", 0, 0,\
  "pop rax"\
  "not rax"\
  "push rax"\
)
COMMAND(28, "and", 0, 0,\
  TWO_ARG_COMMAND("and")\
)
COMMAND(29, "or", 0, 0,\
  TWO_ARG_COMMAND("or")\
)
COMMAND(30, "xor", 0, 0,\
  TWO_ARG_COMMAND("xor")\
)