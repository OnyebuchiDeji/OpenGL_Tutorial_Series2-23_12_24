#include "factory.h"
#include "../_vendor/stb_image.h"

Factory::Factory(
    ComponentSet<CameraComponent>& cameraComponents):
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

    CameraComponent camera;
    camera.position = position;
    camera.eulers = eulers;
    m_CameraComponents.insert(id, camera);
}