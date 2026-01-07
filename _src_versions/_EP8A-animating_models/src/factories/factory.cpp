#include "factory.h"
#include "../_vendor/stb_image.h"

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, RenderComponent>& renderComponents,
    std::unordered_map<unsigned int, TransformComponent>& transformComponents):
    m_PhysicsComponents(physicsComponents), m_RenderComponents(renderComponents),
    m_TransformComponents(transformComponents)
{
    m_MeshFactory = new MeshFactory();
}

Factory::~Factory()
{
    delete m_MeshFactory;
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

    RenderComponent render = m_MeshFactory->make_cube_mesh(
        ObjectType::eBox, {0.25f, 0.25f, 0.25f});

    render.material = m_MeshFactory->make_texture(
        ObjectType::eBox, "../_resources/img/spider_3d_image1a.jpg");
        
    m_RenderComponents[m_EntitiesMade++] = render;
}

void Factory::make_girl_model(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    /**
     *  Applying a pre-transform matrix
     *  this is to apply a single transformation once on the model on loading
     *  to get the model in the preferred way the coordinate space.
     * 
    */
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform,
        glm::radians(90.0f), {1.0f, 0.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 1.0f, 0.0f});

    RenderComponent render = m_MeshFactory->make_obj_mesh(
        ObjectType::eGirl, "../_resources/models/girl.obj", preTransform);
        
    render.material = m_MeshFactory->make_texture(
        ObjectType::eGirl, "../_resources/img/stargirl.png");

    m_RenderComponents[m_EntitiesMade++] = render;
}