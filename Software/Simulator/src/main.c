#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* screen = NULL;

int scale = 8;

int main(int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL init error: %s", SDL_GetError());
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer(
        "ModuPlay simulator",
        SCREEN_WIDTH * scale,
        SCREEN_HEIGHT * scale,
        SDL_WINDOW_RESIZABLE,
        &window,
        &renderer
    )) {
        SDL_Log("Window/renderer creation error: %s", SDL_GetError());
        return 1;
    }

    SDL_SetWindowMinimumSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 23, 56, 17, 255);

    SDL_Event event;
    bool isRunning = true;

    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                isRunning = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                // TODO
                break;
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat) {
                    // TODO
                }
                break;
            case SDL_EVENT_KEY_UP:
                // TODO
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}