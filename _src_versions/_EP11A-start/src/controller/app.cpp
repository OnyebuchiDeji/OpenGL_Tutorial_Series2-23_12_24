#include "app.h"


App::App()
{
    set_up_glfw();
}

App::~App()
{
    for (unsigned int& shader : m_Shaders){
        glDeleteProgram(shader);
    }

    delete m_AnimationSystem;
    delete m_MotionSystem;
    delete m_CameraSystem;
    delete m_RenderSystem;
    
    glfwTerminate();
}

void App::run()
{
    m_LastTime = glfwGetTime();
    m_NumFrames = 0;
    m_FrameTime = 16.0f;
    
    while (!glfwWindowShouldClose(m_Window))
    {
        m_MotionSystem->update(m_FrameTime/1000.0f);

        bool should_close = m_CameraSystem->update(m_FrameTime/1000.0f);
        if (should_close){
            break;
        }

        m_AnimationSystem->update(m_FrameTime);

        m_RenderSystem->update();
        
        handle_frame_timing();
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
    glClearColor(0.25f, 0.25f, 0.34f, 1.0f);
    //  Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(m_Window, &w, &h);
    //  (left, top, width, height)
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_Shaders.push_back(make_shader_program(
        "../core/src/shaders/vertex_sky.txt",
        "../core/src/shaders/fragment_sky.txt"
    ));
    m_Shaders.push_back(make_shader_program(
        "../core/src/shaders/geometry_vertex.txt",
        "../core/src/shaders/fragment.txt"
    ));
    m_Shaders.push_back(make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    ));

    //  args: fov, aspect_ratio, z_near, z_far
    //  Changing z_far from 10.0f to 50.0f
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 50.0f
    );

    for (size_t i = 1; i < 3; ++i)
    {
        unsigned int shader = m_Shaders[i];
        glUseProgram(shader);
        unsigned int projLocation = glGetUniformLocation(shader, "u_Projection");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }
}

void App::make_systems()
{
    m_AnimationSystem = new AnimationSystem(m_AnimationComponents);
    m_MotionSystem = new MotionSystem(m_TransformComponents, m_PhysicsComponents);
    m_CameraSystem = new CameraSystem(m_Shaders, m_Window,
        m_TransformComponents, m_CameraComponents);
    m_RenderSystem = new RenderSystem(m_Shaders, m_Window, m_TransformComponents,
        m_RenderComponents, m_AnimationComponents);
}

/**
 *  This gets the frame rate
 *  then updates the Window Title showing the frame rate.
 *  then updates the frame rate variable.
 *  
 *  Now it ensures the number of frames passed through is counted, to update
 *  the frame rate accordingly.
 * 
 *  Every one second, the frame time is updated, and framerate gotten.
 *  
 */
void App::handle_frame_timing()
{
    m_CurrentTime = glfwGetTime();
    double delta = m_CurrentTime - m_LastTime;

    if (delta >= 1)
    {
        int framerate{ std::max(1, int(m_NumFrames / delta))};
        std::stringstream title;
        title << "Running at " << framerate << "fps.";
        glfwSetWindowTitle(m_Window, title.str().c_str());
        m_LastTime = m_CurrentTime;
        m_NumFrames = -1;
        m_FrameTime = float(1000.0 / framerate);
    }
    ++m_NumFrames;
}