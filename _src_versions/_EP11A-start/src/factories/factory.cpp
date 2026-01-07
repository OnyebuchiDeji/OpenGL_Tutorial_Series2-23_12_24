#include "factory.h"
#include "../_vendor/stb_image.h"

Factory::Factory(
    ComponentSet<PhysicsComponent>& physicsComponents,
    ComponentSet<RenderComponent>& renderComponents,
    ComponentSet<TransformComponent>& transformComponents,
    ComponentSet<AnimationComponent>& animationComponents,
    ComponentSet<CameraComponent>& cameraComponents):
    m_PhysicsComponents(physicsComponents),
    m_RenderComponents(renderComponents),
    m_TransformComponents(transformComponents),
    m_AnimationComponents(animationComponents),
    m_CameraComponents(cameraComponents)
{
}

Factory::~Factory()
{
}

void Factory::make_camera(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    m_TransformComponents.insert(m_EntitiesMade, transform);

    CameraComponent camera;
    m_CameraComponents.insert(m_EntitiesMade++, camera);
}

void Factory::make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents.insert(m_EntitiesMade, transform);

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    m_PhysicsComponents.insert(m_EntitiesMade, physics);

    RenderComponent render;
    render.objectType = ObjectType::eBox;
    render.animationType = AnimationType::eNone;
    m_RenderComponents.insert(m_EntitiesMade++, render);
}

void Factory::make_revy_model(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents.insert(m_EntitiesMade, transform);

    AnimationComponent animation;
    animation.frame = 0;
    animation.speed = 0.4f;
    animation.frameCount = 19;
    m_AnimationComponents.insert(m_EntitiesMade, animation);

    RenderComponent render;
    render.objectType = ObjectType::eRevy;
    render.animationType = AnimationType::eRun;
    m_RenderComponents.insert(m_EntitiesMade++, render);
}