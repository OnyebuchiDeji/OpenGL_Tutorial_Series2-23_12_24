#pragma once
#include "../config.h"

#include "../components/animation_component.h"
#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"
#include "../components/component_set.h"

#include "../systems/animation_system.h"
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
    void set_up_opengl();
    void make_systems();

    //  Components
    ComponentSet<AnimationComponent> m_AnimationComponents;
    ComponentSet<TransformComponent> m_TransformComponents;
    ComponentSet<PhysicsComponent> m_PhysicsComponents;
    ComponentSet<CameraComponent> m_CameraComponents;
    ComponentSet<RenderComponent> m_RenderComponents;
private:
    void set_up_glfw();
    void handle_frame_timing();
    
    GLFWwindow* m_Window;
    std::string m_WinName{"HaKhaylemSoft Window: "};
    

    std::vector<unsigned int> m_Shaders;

    //  Systems
    AnimationSystem* m_AnimationSystem;
    MotionSystem* m_MotionSystem;
    CameraSystem* m_CameraSystem;
    RenderSystem* m_RenderSystem;

    //  Timing
    double m_LastTime, m_CurrentTime;
    int m_NumFrames;
    float m_FrameTime;
};