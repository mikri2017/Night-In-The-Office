#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include <string>
#include "Scene.h"
#include "ui/FontMgr.h"

class SceneGame: public Scene
{
private:
    SDL_FRect fr{ 0, 0, 50, 50 };
public:
    SceneGame(std::string scene_name);
    ~SceneGame();
    SDL_AppResult app_iter(AppState *as);
    void render_clean(SDL_Renderer *r);
    gameReaction process_mouse_motion(float x, float y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Scancode scancode);
};

#endif // GAMESCENE_H_INCLUDED
