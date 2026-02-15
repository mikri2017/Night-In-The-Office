#pragma once

#include <SDL3/SDL.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *r;
    int win_h; // Высота окна
    int win_w; // Ширина окна
} AppState;

enum gameReaction {
    gr_ignore,
    gr_start_new,
    gr_continue,
    gr_pause,
    gr_main_menu,
    gr_exit
};
