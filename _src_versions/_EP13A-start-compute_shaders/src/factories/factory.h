#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/component_set.h"


class Factory
{
public:
    Factory(
        ComponentSet<CameraComponent>& cameraComponents
    );

    ~Factory();

    void make_camera(glm::vec3 position, glm::vec3 eulers);
    
private:
    unsigned int m_EntitiesMade = 0;
    std::vector<unsigned int> m_GarbageBin;
    
    ComponentSet<CameraComponent>& m_CameraComponents;
    
    unsigned int allocate_id();
                
};