#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "MainConstants.h"
#include <SDL3/SDL.h>
#include <string>

class Scene
{
protected:
    bool b_paused = true;

    // Текстовый идентификатор сцены
    std::string name = "";
public:
    Scene(std::string scene_name);
    virtual ~Scene() {};
    void set_paused(bool paused);
    bool get_pause_state();
    void set_name(std::string scene_name);
    std::string get_name();
    virtual SDL_AppResult app_iter(AppState *as) = 0;
    virtual gameReaction process_mouse_motion(float x, float y) = 0;
    virtual gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event) = 0;
    virtual gameReaction process_keyboard_keydown(SDL_Scancode scancode) = 0;
};

#endif // SCENE_H_INCLUDED
