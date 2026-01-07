#pragma once
#include "../config.h"

#include "../components/camera_component.h"
#include "../components/component_set.h"


#include "../systems/camera_system.h"
#include "../systems/render_system.h"


#include "../view/shader.h"


class App
{
public:
    App();
    ~App();
    void run();
    void set_up_opengl();
    void make_systems();

    //  Components
    ComponentSet<CameraComponent> m_CameraComponents;

private:
    void set_up_glfw();
    void handle_frame_timing();
    
    GLFWwindow* m_Window;
    std::string m_WinName{"HaKhaylemSoft Window: "};
    

    std::vector<unsigned int> m_Shaders;
    unsigned int m_ColorBuffer;
    
    //  Systems
    CameraSystem* m_CameraSystem;
    RenderSystem* m_RenderSystem;


    //  Timing
    double m_LastTime, m_CurrentTime;
    int m_NumFrames;
    float m_FrameTime;
};