#include <SDL2/SDL.h>
#include <SDL_log.h>
class Chip8{
    public:
    bool init() {
      if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init_Error: %s", SDL_GetError());
        return false;
      }
      window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 640, 320, 0);
      if (!window) {
        SDL_Log("SDL_CreateWindow_Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
      }
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        SDL_Log("SDL_CreateRenderer_Error: %s", SDL_GetError());
        return false;
      }
      return true;
    }

    ~Chip8() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }
    void emulateCycle() {
        // Emulation cycle code goes here
    }
    void render() {
        // Rendering code goes here
    }
    void handleInput() {
        // Input handling code goes here
    }
    private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};