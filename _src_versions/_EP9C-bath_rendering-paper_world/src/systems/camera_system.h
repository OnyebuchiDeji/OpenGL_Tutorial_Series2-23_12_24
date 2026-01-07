#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/transform_component.h"


class CameraSystem
{
public:
    CameraSystem(unsigned int shader, GLFWwindow* window);
    bool update(
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        unsigned int cameraID, CameraComponent& cameraComponent, float dt
    );
private:
    unsigned int m_ViewLocation;
    glm::vec3 m_GlobalUp = {0.0f, 0.0f, 1.0f};
    GLFWwindow* m_Window;
};