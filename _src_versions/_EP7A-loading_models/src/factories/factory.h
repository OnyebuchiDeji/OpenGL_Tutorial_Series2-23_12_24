#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"

class Factory
{
public:
    Factory(
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
        std::unordered_map<unsigned int, RenderComponent>& renderComponents,
        std::unordered_map<unsigned int, TransformComponent>& transformComponents
    );

    ~Factory();

    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers,
                glm::vec3 eulerVelocity);

private:
    unsigned int m_EntitiesMade = 0;
    std::unordered_map<unsigned int, PhysicsComponent>& m_PhysicsComponents;
    std::unordered_map<unsigned int, RenderComponent>& m_RenderComponents;
    std::unordered_map<unsigned int, TransformComponent>& m_TransformComponents;

    std::vector<unsigned int> m_VAOs;
    std::vector<unsigned int> m_VBOs;
    std::vector<unsigned int> m_Textures;

    RenderComponent make_cube_mesh(glm::vec3 size);
    unsigned int make_texture(const char* filename);
};