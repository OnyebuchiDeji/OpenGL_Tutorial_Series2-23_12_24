#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->m_Position = position;
    this->m_Eulers = {0.0f, 0.0f, 0.0f};
}

glm::mat4 Camera::get_view_transform()
{
    float theta = glm::radians(m_Eulers.z);
    float phi = glm::radians(m_Eulers.y);

    m_Forward = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    m_Right = glm::normalize(glm::cross(m_Forward, m_GlobalUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

    return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::move(glm::vec3 dPos)
{
    m_Position += 0.1f * dPos.x * m_Forward;
    m_Position += 0.1f * dPos.y * m_Right;
    m_Position += 0.1f * dPos.z * m_Up;
}

void Camera::spin(glm::vec3 dEulers)
{
    m_Eulers.y = fminf(89.0f, fmaxf(-89.0f, m_Eulers.y + dEulers.y));
    m_Eulers.z += dEulers.z;
    if (m_Eulers.z > 360){
        m_Eulers.z -= 360;
    }
    else if (m_Eulers.z < 0){
        m_Eulers.z += 360;
    }
}