#include "main.h"
#include <cstdint>
#include <iostream>

vm::vm() {
  pc = 0x200;
  sp = 0; // stack pointer starts at 0 (no entries)
  // clear memory
  for (int i = 0; i < 4096; i++) {
    memory[i] = 0;
  }
  std::cout << "memory cleared successfully\n";
  // clear registers and stack
  for (int i = 0; i < 16; i++) {
    v[i] = 0;
    stack[i] = 0;
  }
  std::cout << "stack cleared successfully\n";
}



void vm::print_stack() {
  std::cout << "{ ";
  for (uint16_t i : stack) {
    std::cout << i << ", ";
  }
  std::cout << "end }\n";
}

int main() {
  vm vm_inst;
  uint8_t program[] = {0x22, 0x00, 0x22, 0x02, 0x00, 0xee, 0x00, 0xee};
  vm_inst.vm_interpret(program, sizeof(program));
}
