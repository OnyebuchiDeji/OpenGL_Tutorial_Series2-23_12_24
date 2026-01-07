#include "config.h"

class Camera
{
public:
    Camera(glm::vec3 position);
    glm::mat4 get_view_transform();
    void move(glm::vec3 dPos);
    void spin(glm::vec3 dEulers);
private:
    glm::vec3 m_Position, m_Eulers;
    glm::vec3 m_GlobalUp = {0.0f, 0.0f, 1.0f};
    glm::vec3 m_Forward, m_Right, m_Up;
};