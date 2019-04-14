//
// Created by dongsheng cao on 2019/3/5.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <android/log.h>

#include "SDL.h"

typedef struct Sprite {
    SDL_Texture *texture;
    Uint16 w;
    Uint16 h;
} Sprite;

/* Adapted from SDL's testspriteminimal.c */
Sprite LoadSprite(const char *file, SDL_Renderer *renderer) {
    Sprite result;
    result.texture = NULL;
    result.w = 0;
    result.h = 0;

    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

    return result;
}

void draw(SDL_Window *window, SDL_Renderer *renderer, const Sprite sprite) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect destRect = {w / 2 - sprite.w / 2, h / 2 - sprite.h / 2, sprite.w, sprite.h};
    /* Blit the sprite onto the screen */
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);
}

int main(int argc, char *argv[]) {

    int width = 640, height = 480;
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "main start");
    SDL_SetMainReady();
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "main 0000");
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "main xxxxx");
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "Could not initialize SDL - %s",
                            SDL_GetError());
    }

    int quit = 1;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 30;
    rect.h = 30;

    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "main 11111");
    window = SDL_CreateWindow("SDLPlayer", 100, 200, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL_CreateWindow failed");
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL_CreateRenderer failed");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width,
                                height);
    if (!texture) {
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL_CreateTexture failed");
    }
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "main 222222");
    do {
//        SDL_WaitEvent(&event);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = 0;
                break;
            default:
                __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL event.type %d", event.type);
                break;
        }
        rect.x = rand() % 600;
        rect.y = rand() % 450;

        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);

    } while (quit);

    if (window) {
        SDL_DestroyWindow(window);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    SDL_Quit();
    return 0;
}