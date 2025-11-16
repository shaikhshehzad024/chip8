#pragma once
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cstddef>
#include <sys/types.h>


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
  void OP_00e0();
  void OP_00ee();
  void OP_1nnn(); // jump
  void OP_2nnn(); // call
  void OP_3xkk(); // skip next instruction if Vx == kk
  void OP_4xkk(); // skip next instruction if Vx != kk
  void OP_5xy0(); //skip next instruction if vx = vy;
  void OP_6xkk(); // set Vx = kk
  void OP_7xkk(); // set Vx += kk
  void OP_8xy0(); // set Vx = Vy
  void OP_8xy1(); // set Vx = Vx OR Vy
  void OP_8xy2(); // set Vx = Vx AND Vy
  void OP_8xy3(); // set Vx = Vx XOR Vy
  void OP_8xy4(); // set Vx += Vy, set VF = carry
  void OP_8xy5(); // set Vx -= Vy, set VF = NOT borrow
  void OP_8xy6();          // set Vx >>= 1, set VF = LSB before shift
  void OP_8xy7(); // set Vx = Vy - Vx, set VF = NOT borrow
  void OP_8xyE();          // set Vx <<= 1, set VF = MSB before shift
  void OP_9xy0(); // skip next instruction if Vx != Vy
  void OP_Annn();       // set I = nnn
  void OP_Bnnn();       // jump to address nnn + V0
  void OP_Cxkk(); // set Vx = random byte AND kk
  void OP_Dxyn(); // draw sprite
  void OP_Ex9E();       // skip next instruction if key with the value of Vx is pressed
  void OP_ExA1();       // skip next instruction if key with the value of Vx is not pressed
  void OP_Fx07();       // set Vx = delay timer value
  void OP_Fx0A();       // wait for a key press, store the value of the key in Vx
  void OP_Fx15();       // set delay timer = Vx
  void OP_Fx18();       // set sound timer = Vx
  void OP_Fx1E();     // set I += Vx
  void OP_Fx29();       // set I = location of sprite for digit Vx
  void OP_Fx33();       // store BCD representation of Vx in memory locations I, I+1, and I+2
  void OP_Fx55();       // store registers V0 through Vx in memory starting  at location I
  void OP_Fx65();       // read registers V0 through Vx from memory starting at location I

  void print_stack();
  void print_registers();
  uint8_t memory[4096];
  uint32_t displayBuffer[64*32];

  uint8_t key[16] = {0};


public:
  vm();
  void setKey(int index, bool pressed);
  void load_program(const uint8_t *program, size_t size);
  void Cycle();
  void installFontset();
  void renderDisplay(SDL_Renderer* renderer);
  void LoadROM(char const* filename);

  public:
  void Table0();
  void Table8();
  void TableE();
  void TableF();
  void OP_NULL();

  typedef void (vm::*Chip8Func)();
  Chip8Func table[0xF + 1];
  Chip8Func table0[0xE + 1];
  Chip8Func table8[0xE + 1];
  Chip8Func tableE[0xE + 1];
  Chip8Func tableF[0x65 + 1];

  public:
  uint16_t instruction;
  uint8_t vx, vy;
  uint8_t kk;
  uint8_t n;
  uint16_t nnn;
  
};
