#ifndef SCENEMENU_H_INCLUDED
#define SCENEMENU_H_INCLUDED

#include "Scene.h"
#include "Button.h"

class SceneMenu : public Scene
{
private:
    SDL_Point menuPosition, btn_size;
    int btn_w, btn_h;
    Button *btn_new_game, *btn_options,
        *btn_about, *btn_exit;
public:
    SceneMenu();
    ~SceneMenu();
    SDL_AppResult app_iter(AppState *as);
    gameReaction process_mouse_motion(float x, float y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Scancode scancode);
};

#endif // SCENEMENU_H_INCLUDED
