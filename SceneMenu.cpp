#include "SceneMenu.h"
#include <iostream>

SceneMenu::SceneMenu()
{
    menuPosition.x = 50;
    menuPosition.y = 350;
    btn_w = 400;
    btn_h = 70;

    // Задаем параметры кнопок
    btn_new_game = new Button();
    btn_new_game->setCaption("New Game");
    btn_new_game->setPosition(menuPosition.x, menuPosition.y);
    btn_new_game->setSize(btn_w, btn_h);

    btn_options = new Button();
    btn_options->setCaption("Options");
    btn_options->setPosition(menuPosition.x, menuPosition.y + btn_h + 30);
    btn_options->setSize(btn_w, btn_h);

    btn_about = new Button();
    btn_about->setCaption("Authors");
    btn_about->setPosition(menuPosition.x, menuPosition.y + 2 * btn_h + 30 * 2);
    btn_about->setSize(btn_w, btn_h);

    btn_exit = new Button();
    btn_exit->setCaption("Exit");
    btn_exit->setPosition(menuPosition.x, menuPosition.y + 3 * btn_h + 30 * 3);
    btn_exit->setSize(btn_w, btn_h);
}

SceneMenu::~SceneMenu()
{
    delete btn_new_game;
    delete btn_options;
    delete btn_about;
    delete btn_exit;
}

SDL_AppResult SceneMenu::app_iter(AppState *as)
{
    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);

    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    btn_new_game->draw(as->r);
    btn_options->draw(as->r);
    btn_about->draw(as->r);
    btn_exit->draw(as->r);

    SDL_RenderPresent(as->r);

    return SDL_APP_CONTINUE;
}

gameReaction SceneMenu::process_mouse_motion(float x, float y)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneMenu::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    // Клик левой кнопкой мышки
    if(m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if(m_btn_event.clicks == 1)
        {
            if(btn_exit->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим из игры
                return gameReaction::gr_exit;
            }

            if(btn_new_game->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Начинаем новую игру
                return gameReaction::gr_start_new;
            }
        }
    }

    return gameReaction::gr_ignore;
}

gameReaction SceneMenu::process_keyboard_keydown(SDL_Scancode scancode)
{
    return gameReaction::gr_ignore;
}
