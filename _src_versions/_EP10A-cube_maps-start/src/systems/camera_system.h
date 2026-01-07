#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/transform_component.h"
#include "../components/component_set.h"


class CameraSystem
{
public:
    CameraSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
        ComponentSet<TransformComponent>& transforms,
        ComponentSet<CameraComponent>& cameras);
    bool update(float dt);

private:
    std::vector<unsigned int>& m_Shaders;
    std::vector<unsigned int> m_ViewLocations;
    const glm::vec3 m_GlobalUp = {0.0f, 0.0f, 1.0f};
    GLFWwindow* m_Window;

    ComponentSet<TransformComponent>& m_Transforms;
    ComponentSet<CameraComponent>& m_Cameras;
};