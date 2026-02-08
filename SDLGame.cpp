#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "MainConstants.h"
#include "SDLGame.h"

SDLGame::SDLGame()
{
    error_msg = "";

	// Создадим менеджер сцен
	s_mgr = new SceneMgr();
}

SDLGame::~SDLGame()
{
    delete s_mgr;
    TTF_Quit(); // Отключаем библиотеку SDL_ttf
}

std::string SDLGame::get_error_msg()
{
    return error_msg;
}

SDL_AppResult SDLGame::app_event(void* appstate, SDL_Event* event)
{
    gameReaction gr = gameReaction::gr_ignore;

    if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN)
    {
        // Нажатие клавиши
        gr = s_mgr->process_keyboard_keydown(event->key.scancode);
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_MOTION)
    {
        // Движение мышкой
        gr = s_mgr->process_mouse_motion(event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        // Клик мышкой
        gr = s_mgr->process_mouse_button_event(event->button);
    }
    else if(event->type == SDL_EventType::SDL_EVENT_QUIT)
    {
        // Выход из приложения
        return SDL_APP_SUCCESS;
    }

    if(gr == gameReaction::gr_exit)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
    iter_start = SDL_GetPerformanceCounter();

    AppState *as = (AppState *) appstate;

    s_mgr->app_iter(as);

    SDL_GetWindowSize(as->win, &(as->win_w), &(as->win_h));

    iter_end = SDL_GetPerformanceCounter();

    iter_diff_ms = (float)(iter_end - iter_start)
        / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    // Ограничиваем частоту кадров в 60 fps
    iter_delay_ms = (Uint32)floor(16.666f - iter_diff_ms);
    if (iter_delay_ms < 0)
        iter_delay_ms = 0;
    else
        if (iter_delay_ms > 1000)
        {
            // При быстром перемещении окна, может получиться
            // очень большое число на задержку!
            iter_delay_ms = 0;
        }

    // Ждем свободное время
    SDL_Delay(iter_delay_ms);

	return SDL_APP_CONTINUE;
}

void SDLGame::app_quite(void* appstate, SDL_AppResult result) {}
