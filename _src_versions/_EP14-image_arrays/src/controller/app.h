#pragma once
#include "../config.h"

#include "../components/registry.h"

#include "../factories/factory.h"

#include "../systems/world.h"
#include "../systems/render.h"
#include "../systems/input.h"
#include "../systems/camera.h"
#include <glad/glad.h>

class App {
public:
    App();
    ~App();
    void run();
    void set_up_opengl();
    void make_systems();

    //Components
    ComponentRegistry m_ComponentRegistry;
    uint32_t m_Shader;
    
private:
    void set_up_glfw();
    void handle_frame_timing();
    void make_objects();

    void handle_controls();

    GLFWwindow* m_Window;
    std::string m_WinName{"HaKhaylemSoft Window: "};

    Factory* m_Factory;

    RenderSystem* m_RenderSystem;
    InputSystem* m_InputSystem;
    World* m_World;
    CameraSystem* m_CameraSystem;

    //  Timing
    double m_LastTime, m_CurrentTime, m_LastFrameTime;
    int m_NumFrames;
    float m_FrameTime = 0.0f;
};