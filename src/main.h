#pragma once
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cstddef>

typedef enum { SUCCESS, ERROR_INVALID_OPCODE } vm_result;

class vm {
  uint8_t v[0x10];
  uint16_t i; // only the lowest(rightmost) 12 bits are used
  // vf register should not be used by any program, it is a flag

  // both of them are usually decremented at 60hz
  uint8_t delay_timer;
  uint8_t sound_timer;

  // these registers are not accessible from programs
  uint8_t sp;
  uint16_t pc; // program counter


  uint16_t stack[16]; // used to store address that interpreter should return
                      // when finished with a subroutine
  void OP_00ee();
  void OP_1nnn(uint16_t address); // jump
  void OP_2nnn(uint16_t address); // call
  void OP_3xkk(uint8_t r_x, uint8_t byte); // skip next instruction if Vx == kk
  void OP_4xkk(uint8_t r_x, uint8_t byte); // skip next instruction if Vx != kk
  void OP_5xy0(uint8_t r_x, uint8_t r_y); //skip next instruction if vx = vy;
  void OP_6xkk(uint8_t r_x, uint8_t byte); // set Vx = kk
  void OP_7xkk(uint8_t r_x, uint8_t byte); // set Vx += kk
  void OP_8xy0(uint8_t r_x, uint8_t r_y); // set Vx = Vy
  void OP_8xy1(uint8_t r_x, uint8_t r_y); // set Vx = Vx OR Vy
  void OP_8xy2(uint8_t r_x, uint8_t r_y); // set Vx = Vx AND Vy
  void OP_8xy3(uint8_t r_x, uint8_t r_y); // set Vx = Vx XOR Vy
  void OP_8xy4(uint8_t r_x, uint8_t r_y); // set Vx += Vy, set VF = carry
  void OP_8xy5(uint8_t r_x, uint8_t r_y); // set Vx -= Vy, set VF = NOT borrow
  void OP_8xy6(uint8_t r_x);          // set Vx >>= 1, set VF = LSB before shift
  void OP_8xy7(uint8_t r_x, uint8_t r_y); // set Vx = Vy - Vx, set VF = NOT borrow
  void OP_8xyE(uint8_t r_x);          // set Vx <<= 1, set VF = MSB before shift
  void OP_9xy0(uint8_t r_x, uint8_t r_y); // skip next instruction if Vx != Vy
  void OP_Annn(uint16_t address);       // set I = nnn
  void OP_Bnnn(uint16_t address);       // jump to address nnn + V0
  void OP_Cxkk(uint8_t r_x, uint8_t byte); // set Vx = random byte AND kk
  // void OP_Dxyn(uint8_t r_x, uint8_t r_y, uint8_t nibble); // draw sprite
  // void OP_Ex9E(uint8_t r_x);       // skip next instruction if key with the value of Vx is pressed
  // void OP_ExA1(uint8_t r_x);       // skip next instruction if key with the value of Vx is not pressed
  void OP_Fx07(uint8_t r_x);       // set Vx = delay timer value
  // void OP_Fx0A(uint8_t r_x);       // wait for a key press, store the value of the key in Vx
  void OP_Fx15(uint8_t r_x);       // set delay timer = Vx
  void OP_Fx18(uint8_t r_x);       // set sound timer = Vx
  void OP_Fx1E(uint8_t r_x);     // set I += Vx
  // void OP_Fx29(uint8_t r_x);       // set I = location of sprite for digit Vx
  void OP_Fx33(uint8_t r_x);       // store BCD representation of Vx in memory locations I, I+1, and I+2
  void OP_Fx55(uint8_t r_x);       // store registers V0 through Vx in memory starting  at location I
  void OP_Fx65(uint8_t r_x);       // read registers V0 through Vx from memory starting at location I

  void load_program(const uint8_t *program, size_t size);
  void print_stack();
  void print_registers();
  uint8_t memory[4096];
  uint8_t displayBuffer[64*32];

public:
  vm();
  vm_result vm_interpret(const uint8_t *program, size_t size);
  void renderDisplay(SDL_Renderer* renderer);
};
