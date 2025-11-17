#include "main.h"
#include <stdio.h>

void vm::print_registers() {
  for (int i = 0; i < 16; i++) {
    printf("V[%X]: %02X, ", i, v[i]);
  }
  printf("\nI: %04X\n", i);
  printf("PC: %04X\n", pc);
  printf("SP: %02X\n", sp);
  printf("Delay Timer: %02X\n", delay_timer);
  printf("Sound Timer: %02X\n", sound_timer);
  print_stack();
}

void vm::print_stack() {
  printf("Stack: ");
  for (uint16_t i : stack) {
    printf("%04X, ", i);
  }
  printf("end }\n");
}