#include "main.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "constants.h"

vm::vm() {
  pc = START_ADDRESS;
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
  table[0x0] = &vm::Table0;
  table[0x1] = &vm::OP_1nnn;
  table[0x2] = &vm::OP_2nnn;
  table[0x3] = &vm::OP_3xkk;
  table[0x4] = &vm::OP_4xkk;
  table[0x5] = &vm::OP_5xy0;
  table[0x6] = &vm::OP_6xkk;
  table[0x7] = &vm::OP_7xkk;
  table[0x8] = &vm::Table8;
  table[0x9] = &vm::OP_9xy0;
  table[0xA] = &vm::OP_Annn;
  table[0xB] = &vm::OP_Bnnn;
  table[0xC] = &vm::OP_Cxkk;
  table[0xD] = &vm::OP_Dxyn;
  table[0xE] = &vm::TableE;
  table[0xF] = &vm::TableF;

  for (size_t i = 0; i <= 0xE; i++) {
    table0[i] = &vm::OP_NULL;
    table8[i] = &vm::OP_NULL;
    tableE[i] = &vm::OP_NULL;
  }
  table0[0x0] = &vm::OP_NULL;
  table0[0xE] = &vm::OP_00ee;
  table8[0x0] = &vm::OP_8xy0;
  table8[0x1] = &vm::OP_8xy1;
  table8[0x2] = &vm::OP_8xy2;
  table8[0x3] = &vm::OP_8xy3;
  table8[0x4] = &vm::OP_8xy4;
  table8[0x5] = &vm::OP_8xy5;
  table8[0x6] = &vm::OP_8xy6;
  table8[0x7] = &vm::OP_8xy7;
  table8[0xE] = &vm::OP_8xyE;
  tableE[0x1] = &vm::OP_ExA1;
  tableE[0xE] = &vm::OP_Ex9E;

  for (size_t n = 0; n <= 0x65; n++) {
    tableF[n] = &vm::OP_NULL;
  }
  tableF[0x07] = &vm::OP_Fx07;
  tableF[0x0A] = &vm::OP_Fx0A;
  tableF[0x15] = &vm::OP_Fx15;
  tableF[0x18] = &vm::OP_Fx18;
  tableF[0x1E] = &vm::OP_Fx1E;
  tableF[0x29] = &vm::OP_Fx29;
  tableF[0x33] = &vm::OP_Fx33;
  tableF[0x55] = &vm::OP_Fx55;
  tableF[0x65] = &vm::OP_Fx65;
}

void vm::Table0() {
  ((*this).*(table0[instruction & 0x000f]))();
}
void vm::Table8() {
  ((*this).*(table8[instruction & 0x000f]))();
}
void vm::TableE() {
  ((*this).*(tableE[instruction & 0x000f]))();
}
void vm::TableF() {
  ((*this).*(tableF[instruction & 0x00ff]))();
}
void vm::OP_NULL() {
  std::cerr << "ERROR: Unimplemented opcode: " << std::hex << instruction << std::dec << "\n";
}


// Helper: map SDL_Keycode to CHIP-8 key (0x0..0xF). Returns -1 for unmapped keys.
static int sdlKeyToChip8(SDL_Keycode kc) {
    switch (kc) {
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;
        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;
        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;
        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;
        default: return -1;
    }
}

// Helper: handle SDL key event and forward to VM
static void handleKeyEvent(vm &vm_inst, const SDL_Event &event, bool pressed) {
    if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) return;
    int key = sdlKeyToChip8(event.key.keysym.sym);
    if (key >= 0) vm_inst.setKey(key, pressed);
}

int main() {
  vm vm_inst;
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Window* window = SDL_CreateWindow(
    "Chip8",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 320,
    0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // NOTE: don't call vm_interpret() here before loading something into memory.
  // vm_inst.vm_interpret(); <-- removed

  // load program / ROM before entering the main loop
  // vm_inst.load_program(testProgram, sizeof(testProgram));
  vm_inst.LoadROM("IBM Logo.ch8");
  vm_inst.installFontset();

  bool running = true;
  SDL_Event event;
  while (running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        continue;
      }

      // Use modular handler for key down/up
      if (event.type == SDL_KEYDOWN) handleKeyEvent(vm_inst, event, true);
      if (event.type == SDL_KEYUP)   handleKeyEvent(vm_inst, event, false);
    }
    // vm_inst.vm_interpret();
    vm_inst.Cycle();
    vm_inst.renderDisplay(renderer);
    SDL_Delay(16);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
