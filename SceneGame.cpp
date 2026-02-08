#include "MainConstants.h"
#include "SceneGame.h"
#include <iostream>
#include <SDL3/SDL.h>

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

SDL_AppResult SceneGame::app_iter(AppState *as)
{
    if (!b_paused)
    {
        SDL_SetRenderDrawColor(as->r, 255, 255, 255, 255);
        SDL_RenderClear(as->r);
        SDL_SetRenderDrawColor(as->r, 255, 0, 0, 255);

        // Очищаем экран от текущих объектов
        render_clean(as->r);

        // Рисуем объекты

        // Отображаем результат на экране
        SDL_RenderPresent(as->r);
    }

    return SDL_APP_CONTINUE;
}

void SceneGame::render_clean(SDL_Renderer *r)
{
    // Стираем текущие объекты сцены
}

gameReaction SceneGame::process_mouse_motion(float x, float y)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneGame::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneGame::process_keyboard_keydown(SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_ESCAPE)
	{
		return gameReaction::gr_main_menu;
	}

    return gameReaction::gr_ignore;
}
