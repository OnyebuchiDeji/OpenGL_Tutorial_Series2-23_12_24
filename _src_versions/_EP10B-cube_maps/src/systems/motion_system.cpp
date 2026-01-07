#include "motion_system.h"

MotionSystem::MotionSystem(
        ComponentSet<TransformComponent>& transforms,
        ComponentSet<PhysicsComponent>& velocities):
    m_Transforms(transforms), m_Velocities(velocities)
{
}


void MotionSystem::update(float dt)
{
    for (size_t i = 0; i < m_Velocities.m_Entities.size(); ++ i){
        uint32_t entity = m_Velocities.m_Entities[i];
        PhysicsComponent& physics = m_Velocities.m_Components[i];
        TransformComponent& transform = m_Transforms.get_component(entity);

        transform.position += physics.velocity * dt;
        transform.eulers += physics.eulerVelocity * dt;
        if (transform.eulers.z > 360){
            transform.eulers.z -= 360;
        }
    }
}