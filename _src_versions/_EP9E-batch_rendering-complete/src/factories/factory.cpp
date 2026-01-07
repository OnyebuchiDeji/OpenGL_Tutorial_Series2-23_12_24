#include "factory.h"
#include "../_vendor/stb_image.h"

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, RenderComponent>& renderComponents,
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, AnimationComponent>& animationComponents):
    m_PhysicsComponents(physicsComponents),
    m_RenderComponents(renderComponents),
    m_TransformComponents(transformComponents),
    m_AnimationComponents(animationComponents)
{
}

Factory::~Factory()
{
}

unsigned int Factory::make_camera(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    m_TransformComponents[m_EntitiesMade] = transform;
    return m_EntitiesMade++;
}

void Factory::make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    m_PhysicsComponents[m_EntitiesMade] = physics;

    RenderComponent render;
    render.objectType = ObjectType::eBox;
    render.animationType = AnimationType::eNone;
    m_RenderComponents[m_EntitiesMade++] = render;
}

void Factory::make_cube2(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    m_PhysicsComponents[m_EntitiesMade] = physics;

    RenderComponent render;
    render.objectType = ObjectType::eBox2;
    render.animationType = AnimationType::eNone;
    m_RenderComponents[m_EntitiesMade++] = render;
}

/* void Factory::make_girl_model(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

   RenderComponent render;
   render.objectType = ObjectType::eGirl;
   render.animationType = AnimationType::eNone;
   m_RenderComponents[m_EntitiesMade++] = render;
} */

void Factory::make_revy_model(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    AnimationComponent animation;
    animation.frame = 0;
    animation.speed = 0.4f;
    animation.frameCount = 19;
    m_AnimationComponents[m_EntitiesMade] = animation;

    RenderComponent render;
    render.objectType = ObjectType::eRevy;
    render.animationType = AnimationType::eRun;
    m_RenderComponents[m_EntitiesMade++] = render;
}