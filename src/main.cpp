#include "main.h"
#include <SDL2/SDL.h>
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
  uint8_t program[] = {0x22, 0x00, 0x22, 0x02, 0x00, 0xee, 0x00, 0xee};
  vm_inst.vm_interpret(program, sizeof(program));

  bool running = true;
  SDL_Event event;
  while (running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }
    vm_inst.renderDisplay(renderer);
    SDL_Delay(16);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
