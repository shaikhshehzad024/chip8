#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
class Platform {
    public:
    Platform(char const *title, int width, int height, int textureWidth, int textureHeight);
      ~Platform();
      void Update();
      bool ProcessInput(uint8_t *keys);
    private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
    };