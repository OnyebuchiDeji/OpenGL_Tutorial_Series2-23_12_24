#include "factory.h"

Factory::Factory(ComponentRegistry& componentRegistry, uint32_t& shader):
    m_ComponentRegistry(componentRegistry), m_Shader(shader)
{

}

unsigned int Factory::allocate_id() {
    
	if (m_GarbageBin.size() > 0) {
		uint32_t id = m_GarbageBin[m_GarbageBin.size() - 1];
		m_GarbageBin.pop_back();
		return id;
	}
	else {
		uint32_t id = m_EntitesMade++;
		return id;
	}
}

void Factory::make_object() {

	unsigned int id = allocate_id();

	//Transform
	TransformComponent transform;
	constexpr float radius = 50.0f;
	float x = radius * (2.0f * randutils::random_float() - 1.0f);
	float y = radius * (2.0f * randutils::random_float() - 1.0f);
	float z = radius * (2.0f * randutils::random_float() - 1.0f);
	transform.position = glm::vec3(x, y, z);

	x = 360.0f * randutils::random_float();
	y = 360.0f * randutils::random_float();
	z = 360.0f * randutils::random_float();
	transform.eulers = glm::vec3(x, y, z);

	x = 1.8f * randutils::random_float() + 0.2f;
	transform.scale = x;

	m_ComponentRegistry.transforms.insert(id, transform);

	//Velocity
	VelocityComponent velocity;
	constexpr float maxSpeed = 10.0f;
	x = maxSpeed * (2.0f * randutils::random_float() - 1.0f);
	y = maxSpeed * (2.0f * randutils::random_float() - 1.0f);
	z = maxSpeed * (2.0f * randutils::random_float() - 1.0f);
	velocity.angular = glm::vec3(x, y, z);

	m_ComponentRegistry.velocities.insert(id, velocity);

	//Model
	RenderComponent model;
	model.objectType = static_cast<ObjectType>(randutils::random_int_in_range(objectTypeCount));
	m_ComponentRegistry.renderables.insert(id, model);
}