#include "main.h"
void vm::load_program(const uint8_t *program, size_t size) {
  // copy 'size' bytes of program into memory starting at 0x200
  if (!program || size == 0)
    return;
  for (size_t i = 0; i < size && (0x200 + i) < sizeof(memory); ++i) {
    memory[0x200 + i] = program[i];
  }
}