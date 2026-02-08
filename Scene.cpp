#include "Scene.h"

Scene::Scene(std::string scene_name)
{
    set_name(scene_name);
}

void Scene::set_paused(bool paused)
{
    b_paused = paused;
}

bool Scene::get_pause_state()
{
    return b_paused;
}

void Scene::set_name(std::string scene_name)
{
    name = scene_name;
}

std::string Scene::get_name()
{
    return name;
}
