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

unsigned int Factory::allocate_id()
{
    if (m_GarbageBin.size() > 0){
        uint32_t id = m_GarbageBin[m_GarbageBin.size() - 1];
        m_GarbageBin.pop_back();
        return id;
    }
    return m_EntitiesMade++;
}

Factory::~Factory()
{
}

void Factory::make_camera(glm::vec3 position, glm::vec3 eulers)
{
    unsigned int id = allocate_id();

    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    m_TransformComponents.insert(id, transform);

    CameraComponent camera;
    m_CameraComponents.insert(id, camera);
}

void Factory::destroy_camera(unsigned int id)
{
    m_TransformComponents.remove(id);
    m_CameraComponents.remove(id);
    m_GarbageBin.push_back(id);
}

void Factory::make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    unsigned int id = allocate_id();
    
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents.insert(id, transform);

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    m_PhysicsComponents.insert(id, physics);

    RenderComponent render;
    render.objectType = ObjectType::eBox;
    render.animationType = AnimationType::eNone;
    m_RenderComponents.insert(id, render);
}

void Factory::make_revy_model(glm::vec3 position, glm::vec3 eulers)
{
    unsigned int id = allocate_id();

    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents.insert(id, transform);

    AnimationComponent animation;
    animation.frame = 0;
    animation.speed = 0.4f;
    animation.frameCount = 19;
    m_AnimationComponents.insert(id, animation);

    RenderComponent render;
    render.objectType = ObjectType::eRevy;
    render.animationType = AnimationType::eRun;
    m_RenderComponents.insert(id, render);
}