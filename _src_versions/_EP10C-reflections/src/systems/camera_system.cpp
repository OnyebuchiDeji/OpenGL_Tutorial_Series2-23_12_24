#include "camera_system.h"

CameraSystem::CameraSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
            ComponentSet<TransformComponent>& transforms, ComponentSet<CameraComponent>& cameras):
    m_Shaders(shaders), m_Transforms(transforms), m_Cameras(cameras)
{
    this->m_Window = window;
    unsigned int shader = m_Shaders[0];
    glUseProgram(shader);
    m_ForwardLocation = glGetUniformLocation(shader, "u_Forward");
    m_RightLocation = glGetUniformLocation(shader, "u_Right");
    m_UpLocation = glGetUniformLocation(shader, "u_Up");

    for (size_t i = 1; i < 3; ++i)
    {
        shader = m_Shaders[i];
        glUseProgram(shader);
        m_ViewLocations.push_back(glGetUniformLocation(shader, "u_View"));
        m_PosLocations.push_back(glGetUniformLocation(shader, "u_CameraPos"));
    }
    m_Dy = 1.25f * glm::tan(3.14159f / 8.0f);
    m_Dx = m_Dy * 640.0f / 480.0f;
}

bool CameraSystem::update(float dt)
{
    CameraComponent& camera = m_Cameras.m_Components[0];
    uint32_t cameraID = m_Cameras.m_Entities[0];

    TransformComponent& transform  = m_Transforms.get_component(cameraID);
    glm::vec3& pos = transform.position;
    glm::vec3& eulers = transform.eulers;
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
    glm::mat4 view = glm::lookAt(pos, pos + forward, up);

    glUseProgram(m_Shaders[0]);
    glUniform3fv(m_ForwardLocation, 1, glm::value_ptr(forward));
    glUniform3fv(m_RightLocation, 1, glm::value_ptr(m_Dx * right));
    glUniform3fv(m_UpLocation, 1, glm::value_ptr(m_Dy * up));
     
    glUseProgram(m_Shaders[1]);
    glUniformMatrix4fv(m_ViewLocations[0], 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(m_PosLocations[0], 1, glm::value_ptr(pos));
    
    glUseProgram(m_Shaders[2]);
    glUniformMatrix4fv(m_ViewLocations[1], 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(m_PosLocations[1], 1, glm::value_ptr(pos));

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