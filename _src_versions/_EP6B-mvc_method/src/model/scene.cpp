#include "scene.h"

Scene::Scene()
    : m_Camera(Camera(glm::vec3(0.0f, 0.0f, 1.0f)))
{
    m_Cubes.push_back(Cube({3.0f, 0.0f, 0.25f}));
}

void Scene::update(float dt)
{
    for (Cube& cube : m_Cubes){
        cube.update(dt);
    }
}

void Scene::move_player(glm::vec3 dPos)
{
    m_Camera.move(dPos);
}

void Scene::spin_player(glm::vec3 dEulers)
{
    m_Camera.spin(dEulers);
}