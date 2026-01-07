#include "app.h"


App::App()
{
    set_up_glfw();
}

App::~App()
{
    glDeleteProgram(m_Shader);

    delete m_AnimationSystem;
    delete m_MotionSystem;
    delete m_CameraSystem;
    delete m_RenderSystem;
    
    glfwTerminate();
}

void App::run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        m_MotionSystem->update(
            m_TransformComponents, m_PhysicsComponents,
            16.67f/1000.0f
        );
        bool should_close = m_CameraSystem->update(
            m_TransformComponents, m_CameraID, *m_CameraComponent, 16.67f / 1000.0f
        );
        if (should_close){
            break;
        }
        m_AnimationSystem->update(m_AnimationComponents, 16.667f);
        m_RenderSystem->update(m_TransformComponents, m_RenderComponents, m_AnimationComponents);
    }
}

void App::set_up_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_Window = glfwCreateWindow(640, 480, "HaKhaylemSoft Window", NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not load opengl!\n";
        glfwTerminate();
    }
}

void App::set_up_opengl()
{
    glClearColor(0.25f, 0.13f, 0.34f, 1.0f);
    //  Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(m_Window, &w, &h);
    //  (left, top, width, height)
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_Shader = make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    );

    glUseProgram(m_Shader);
    unsigned int projLocation = glGetUniformLocation(m_Shader, "u_Projection");
    //  args: fov, aspect_ratio, z_near, z_far
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 10.0f
    );
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

}

void App::make_systems()
{
    m_AnimationSystem = new AnimationSystem();
    m_MotionSystem = new MotionSystem();
    m_CameraSystem = new CameraSystem(m_Shader, m_Window);
    m_RenderSystem = new RenderSystem(m_Shader, m_Window);
}