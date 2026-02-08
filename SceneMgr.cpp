#include "SceneMgr.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneMenuPause.h"

SceneMgr::SceneMgr()
{
    // Основное меню
    add_scene(new SceneMenu("menu_main"));
}

SceneMgr::~SceneMgr()
{
    // Удаляем сцены
    delete_all_scenes();
}

SDL_AppResult SceneMgr::app_iter(AppState *as)
{
    return active->app_iter(as);
}

void SceneMgr::add_scene(Scene *scene, bool set_active)
{
    v_scenes.push_back(scene);
    if(set_active)
    {
        active = scene;
        active->set_paused(false);
    }
}

void SceneMgr::delete_all_scenes()
{
    // Удаляем сцены
    for(auto it : v_scenes)
    {
        delete it;
    }
    v_scenes.clear();
}

void SceneMgr::reinit()
{
    delete_all_scenes();

    // Основное меню
    add_scene(new SceneMenu("menu_main"));
}

void SceneMgr::start_new_game()
{
    add_scene(new SceneGame("game")); // Игра
    add_scene(new SceneMenuPause("menu_pause"), false); // Меню паузы
}

gameReaction SceneMgr::process_mouse_motion(float x, float y)
{
    return active->process_mouse_motion(x, y);
}

gameReaction SceneMgr::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    gameReaction gr = active->process_mouse_button_event(m_btn_event);
    if(gr == gameReaction::gr_start_new)
    {
        start_new_game();
        gr = gameReaction::gr_ignore;
    }
    else if(gr == gameReaction::gr_continue)
    {
        if (active->get_name() == "menu_pause")
        {
            // Пауза, возвращаемся в игру
            for (auto sc : v_scenes)
            {
                if (sc->get_name() == "game")
                {
                    active = sc;
                    active->set_paused(false);
                    break;
                }
            }
        }

        gr = gameReaction::gr_ignore;
    }
    else if(gr == gameReaction::gr_main_menu)
    {
        // Сбрасываем все и запускаем главное меню
        reinit();
        gr = gameReaction::gr_ignore;
    }

    return gr;
}

gameReaction SceneMgr::process_keyboard_keydown(SDL_Scancode scancode)
{
    gameReaction gr = gameReaction::gr_ignore;

    if(scancode == SDL_SCANCODE_ESCAPE)
    {
        if(active->get_name() == "game")
        {
            // Ставим игру на паузу
            active->set_paused(true);
            // Передаем управление в меню паузы
            for (auto sc : v_scenes)
            {
                if (sc->get_name() == "menu_pause")
                {
                    active = sc;
                    active->set_paused(false);
                    break;
                }
            }
        }
        else if(active->get_name() == "menu_pause")
        {
            // Пауза, возвращаемся в игру
            for (auto sc : v_scenes)
            {
                if (sc->get_name() == "game")
                {
                    active = sc;
                    active->set_paused(false);
                    break;
                }
            }
        }
        else // Выходим из игры
            gr = gameReaction::gr_exit;
    }
    else
        gr = active->process_keyboard_keydown(scancode);

    return gr;
}
