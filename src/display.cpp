#include <SDL2/SDL.h>
#include "main.h"

const int DISPLAY_WIDTH = 64;
const int DISPLAY_HEIGHT = 32;
const int PIXEL_SIZE = 10;

void vm::renderDisplay(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
            int index = y * DISPLAY_WIDTH + x;
            if (displayBuffer[index]) {
                SDL_Rect pixelRect = {x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};
                SDL_RenderFillRect(renderer, &pixelRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}