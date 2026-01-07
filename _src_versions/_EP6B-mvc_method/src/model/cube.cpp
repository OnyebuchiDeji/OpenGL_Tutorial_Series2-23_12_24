#include "cube.h"
// #include "../_vendor/stb_image.h"

Cube::Cube(glm::vec3 position)
{
    this->m_Position = position;
    this->m_Eulers = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Cube::update(float dt)
{
    m_Eulers.z += 10.0f * dt;
    if (m_Eulers.z > 360){
        m_Eulers.z -= 360;
    }
}

glm::mat4 Cube::get_model_transform()
{
    //  model transform
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(
        model, glm::radians(m_Eulers.z),
        {0.0f, 0.0f, 1.0f});

    return model;
}