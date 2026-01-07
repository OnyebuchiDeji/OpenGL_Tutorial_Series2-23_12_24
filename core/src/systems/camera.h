#pragma once
#include "../config.h"
#include "../components/registry.h"


class CameraSystem
{
public:
    CameraSystem(uint32_t shader);
    void update();
    void move(glm::vec3 dPos);
    void spin(glm::vec3 dEulers);

private:
    glm::vec3 m_Position, m_Eulers, m_Forward, m_Right, m_Up;
    glm::uint32_t m_Shader, m_ViewProjLocation;
    glm::mat4 m_Projection;
};