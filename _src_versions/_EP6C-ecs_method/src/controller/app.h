#pragma once
#include "../config.h"

#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"

#include "../systems/camera_system.h"
#include "../systems/motion_system.h"
#include "../systems/render_system.h"

#include "../view/shader.h"


class App
{
public:
    App();
    ~App();
    void run();
    unsigned int make_entity();
    unsigned int make_cube_mesh(glm::vec3 size);
    unsigned int make_texture(const char* filename);
    void set_up_opengl();
    void make_systems();

    //  Components
    std::unordered_map<unsigned int, TransformComponent> m_TransformComponents;
    std::unordered_map<unsigned int, PhysicsComponent> m_PhysicsComponents;
    CameraComponent* m_CameraComponent;
    unsigned int m_CameraID;
    std::unordered_map<unsigned int, RenderComponent> m_RenderComponents;
private:
    void set_up_glfw();
    unsigned int m_EntityCount = 0;
    GLFWwindow* m_Window;

    std::vector<unsigned int> m_VAOs;
    std::vector<unsigned int> m_VBOs;
    std::vector<unsigned int> m_Textures;

    unsigned int m_Shader;

    //  Systems
    MotionSystem* m_MotionSystem;
    CameraSystem* m_CameraSystem;
    RenderSystem* m_RenderSystem;
};