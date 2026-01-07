#include "camera_system.h"

CameraSystem::CameraSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
            ComponentSet<CameraComponent>& cameras):
    m_Shaders(shaders), m_Cameras(cameras)
{
    this->m_Window = window;
}

bool CameraSystem::update(float dt)
{
    CameraComponent& camera = m_Cameras.m_Components[0];
    uint32_t cameraID = m_Cameras.m_Entities[0];

    glm::vec3& pos = camera.position;
    glm::vec3& eulers = camera.eulers;
    float theta = glm::radians(eulers.z);
    float phi = glm::radians(eulers.y);

    glm::vec3& right = camera.right;
    glm::vec3& up = camera.up;
    glm::vec3& forward = camera.forward;

    forward = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    right = glm::normalize(glm::cross(forward, m_GlobalUp));
    up = glm::normalize(glm::cross(right, forward));

    //  Keys
    glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS){
        dPos.x += 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS){
        dPos.y -= 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS){
        dPos.x -= 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS){
        dPos.y += 1.0f;
    }
    if (glm::length(dPos) > 0.1f)
    {
        dPos = glm::normalize(dPos);
        //  Changing camera motion speed
        pos += 10.0f * dt * dPos.x * forward;
        pos += 10.0f * dt * dPos.y * right;
    }

    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        return true;
    }

    //  Mouse
    glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
    double mouse_x, mouse_y;
    glfwGetCursorPos(m_Window, &mouse_x, &mouse_y);
    glfwSetCursorPos(m_Window, 320.0, 240.0);
    glfwPollEvents();
    
    //  Changing rotation speed
    dEulers.z = -0.5f * static_cast<float>(mouse_x - 320.0);
    dEulers.y = -0.5f * static_cast<float>(mouse_y - 240.0);

    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + dEulers.y));

    eulers.z += dEulers.z;
    if (eulers.z > 360) {
        eulers.z -= 360;
    }
    else if (eulers.z < 0) {
        eulers.z += 360;
    }

    return false;
}