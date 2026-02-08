#include "SceneMenuPause.h"
#include <iostream>

SceneMenuPause::SceneMenuPause(std::string scene_name) : Scene(scene_name)
{
    menuPosition.x = 50;
    menuPosition.y = 350;
    btn_w = 400;
    btn_h = 70;

    // Фон меню паузы
    frect_backgrnd.x = 0;
    frect_backgrnd.y = 0;
    frect_backgrnd.w = SCREEN_WIDTH;
    frect_backgrnd.h = SCREEN_HEIGHT;

    // Задаем параметры кнопок
    btn_continue = new Button();
    btn_continue->setCaption("Continue Game");
    btn_continue->setPosition(menuPosition.x, menuPosition.y);
    btn_continue->setSize(btn_w, btn_h);

    btn_options = new Button();
    btn_options->setCaption("Options");
    btn_options->setPosition(menuPosition.x, menuPosition.y + btn_h + 30);
    btn_options->setSize(btn_w, btn_h);

    btn_main_menu = new Button();
    btn_main_menu->setCaption("Main Menu");
    btn_main_menu->setPosition(menuPosition.x, menuPosition.y + 2 * btn_h + 30 * 2);
    btn_main_menu->setSize(btn_w, btn_h);

    btn_exit = new Button();
    btn_exit->setCaption("Exit");
    btn_exit->setPosition(menuPosition.x, menuPosition.y + 3 * btn_h + 30 * 3);
    btn_exit->setSize(btn_w, btn_h);
}

SceneMenuPause::~SceneMenuPause()
{
    delete btn_continue;
    delete btn_options;
    delete btn_main_menu;
    delete btn_exit;
}

SDL_AppResult SceneMenuPause::app_iter(AppState *as)
{
    // Включаем поддержку прозрачности
    SDL_SetRenderDrawBlendMode(as->r, SDL_BLENDMODE_BLEND);
    // Выставляем цвет с прозрачностью
    SDL_SetRenderDrawColor(as->r, 255, 255, 255, 190);
    // Заливаем весь экран
    SDL_RenderFillRect(as->r, &frect_backgrnd);
    // Возвращаем основной цвет рисовки
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, 255);

    btn_continue->draw(as->r);
    btn_options->draw(as->r);
    btn_main_menu->draw(as->r);
    btn_exit->draw(as->r);

    SDL_RenderPresent(as->r);

    return SDL_APP_CONTINUE;
}

gameReaction SceneMenuPause::process_mouse_motion(float x, float y)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneMenuPause::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
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

            if(btn_main_menu->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим в главное меню
                return gameReaction::gr_main_menu;
            }

            if(btn_continue->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Возвращаемся в игру
                return gameReaction::gr_continue;
            }
        }
    }

    return gameReaction::gr_ignore;
}

gameReaction SceneMenuPause::process_keyboard_keydown(SDL_Scancode scancode)
{
    return gameReaction::gr_ignore;
}
