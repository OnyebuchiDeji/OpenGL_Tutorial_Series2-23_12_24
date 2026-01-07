#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/animation_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"
// #include "mesh_factory.h"

class Factory
{
public:
    Factory(
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
        std::unordered_map<unsigned int, RenderComponent>& renderComponents,
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        std::unordered_map<unsigned int, AnimationComponent>& animationComponents
    );

    ~Factory();

    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers,
                glm::vec3 eulerVelocity);

    void make_cube2(glm::vec3 position, glm::vec3 eulers,
                glm::vec3 eulerVelocity);

    // void make_girl_model(glm::vec3 position, glm::vec3 eulers);
    void make_revy_model(glm::vec3 position, glm::vec3 eulers);
    
private:
    unsigned int m_EntitiesMade = 0;
    
    std::unordered_map<unsigned int, PhysicsComponent>& m_PhysicsComponents;
    std::unordered_map<unsigned int, RenderComponent>& m_RenderComponents;
    std::unordered_map<unsigned int, TransformComponent>& m_TransformComponents;
    std::unordered_map<unsigned int, AnimationComponent>& m_AnimationComponents;
                
};