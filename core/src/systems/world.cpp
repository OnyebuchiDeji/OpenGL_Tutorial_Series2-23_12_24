#include "world.h"

World::World(ComponentRegistry& componentRegistry):
    m_ComponentRegistry(componentRegistry) {}

void World::update(float frametime)
{
    for (size_t i = 0; i < m_ComponentRegistry.velocities.m_Entities.size(); ++i){
        uint32_t id = m_ComponentRegistry.velocities.m_Entities[i];
		VelocityComponent& velocity = m_ComponentRegistry.velocities.m_Components[i];
		TransformComponent& transform = m_ComponentRegistry.transforms.get_component(i);

		transform.eulers += frametime / 1000.0f * velocity.angular;
    }
}