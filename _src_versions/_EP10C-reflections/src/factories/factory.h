#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/animation_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"
#include "../components/component_set.h"
// #include "mesh_factory.h"

class Factory
{
public:
    Factory(
        ComponentSet<PhysicsComponent>& physicsComponents,
        ComponentSet<RenderComponent>& renderComponents,
        ComponentSet<TransformComponent>& transformComponents,
        ComponentSet<AnimationComponent>& animationComponents,
        ComponentSet<CameraComponent>& cameraComponents
    );

    ~Factory();

    void make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers,
                glm::vec3 eulerVelocity);

    // void make_girl_model(glm::vec3 position, glm::vec3 eulers);
    void make_revy_model(glm::vec3 position, glm::vec3 eulers);
    
private:
    unsigned int m_EntitiesMade = 0;
    
    ComponentSet<PhysicsComponent>& m_PhysicsComponents;
    ComponentSet<RenderComponent>& m_RenderComponents;
    ComponentSet<TransformComponent>& m_TransformComponents;
    ComponentSet<AnimationComponent>& m_AnimationComponents;
    ComponentSet<CameraComponent>& m_CameraComponents;
                
};