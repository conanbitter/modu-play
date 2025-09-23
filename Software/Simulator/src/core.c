#include "moduplay.h"
#include "mpcore.h"
#include <SDL3/SDL.h>

#define SCREEN_LINES (8)
#define INIT_SCALE (8)

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* screen = NULL;

static SDL_FRect screen_rect = { 0, 0, SCREEN_WIDTH * INIT_SCALE, SCREEN_HEIGHT * INIT_SCALE };

static Uint32 color_black = 0;
static Uint32 color_white = 0;

void mp_display() {
    Uint32* pixels;
    int pitch;
    if (SDL_LockTexture(screen, NULL, &pixels, &pitch)) {
        pitch /= sizeof(Uint32);

        for (int l = 0; l < SCREEN_LINES; l++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                uint8_t column = canvas[l * SCREEN_WIDTH + x];
                for (int p = 0;p < 8;p++) {
                    bool color = column & (1 << p);
                    int y = l * 8 + p;
                    pixels[y * pitch + x] = color ? color_white : color_black;
                }
            }
        }
        SDL_UnlockTexture(screen);
    } else {
        SDL_Log("Screen update error: %s", SDL_GetError());
    }
}

static void set_scale(int scale) {
    SDL_SetWindowSize(window, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    screen_rect.x = 0;
    screen_rect.y = 0;
    screen_rect.w = SCREEN_WIDTH * scale;
    screen_rect.h = SCREEN_HEIGHT * scale;
}

static void adjust_frame(int width, int height) {
    int screen_scale = width / SCREEN_WIDTH;
    int scaley = height / SCREEN_HEIGHT;
    if (screen_scale > scaley) screen_scale = scaley;
    screen_rect.w = SCREEN_WIDTH * screen_scale;
    screen_rect.h = SCREEN_HEIGHT * screen_scale;
    screen_rect.x = (width - screen_rect.w) / 2;
    screen_rect.y = (height - screen_rect.h) / 2;
}

void mp_begin() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL init error: %s", SDL_GetError());
        exit(1);
    }

    if (!SDL_CreateWindowAndRenderer(
        "ModuPlay simulator",
        SCREEN_WIDTH * INIT_SCALE,
        SCREEN_HEIGHT * INIT_SCALE,
        SDL_WINDOW_RESIZABLE,
        &window,
        &renderer
    )) {
        SDL_Log("Window/renderer creation error: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetWindowMinimumSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 23, 56, 17, 255);

    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureScaleMode(screen, SDL_SCALEMODE_PIXELART);
    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(screen->format);
    color_black = SDL_MapRGBA(format, NULL, 0, 20, 40, 255);
    color_white = SDL_MapRGBA(format, NULL, 229, 242, 255, 255);
}

bool _mpc_process_events() {
    SDL_Event event;
    bool keep_running = true;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            keep_running = false;
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            adjust_frame(event.window.data1, event.window.data2);
            break;
        case SDL_EVENT_KEY_DOWN:
            if (!event.key.repeat) {
                switch (event.key.key)
                {
                case SDLK_ESCAPE:
                    keep_running = false;
                    break;
                case SDLK_1:
                    set_scale(1);
                    break;
                case SDLK_2:
                    set_scale(2);
                    break;
                case SDLK_3:
                    set_scale(3);
                    break;
                case SDLK_4:
                    set_scale(4);
                    break;
                case SDLK_5:
                    set_scale(5);
                    break;
                case SDLK_6:
                    set_scale(6);
                    break;
                case SDLK_7:
                    set_scale(7);
                    break;
                case SDLK_8:
                    set_scale(8);
                    break;
                case SDLK_9:
                    set_scale(9);
                    break;
                case SDLK_0:
                    set_scale(10);
                    break;
                }
                // TODO
            }
            break;
        case SDL_EVENT_KEY_UP:
            // TODO
            break;
        }
    }
    return keep_running;
}

void _mpc_present() {
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, screen, NULL, &screen_rect);
    SDL_RenderPresent(renderer);
}

void _mpc_finish() {
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}