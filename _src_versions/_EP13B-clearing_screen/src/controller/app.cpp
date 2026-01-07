#include "app.h"
#include "../factories/texture_factory.h"

App::App()
{
    set_up_glfw();
}

App::~App()
{
    for (unsigned int& shader : m_Shaders){
        glDeleteProgram(shader);
    }

    glDeleteTextures(1, &m_ColorBuffer);

    delete m_CameraSystem;
    delete m_RenderSystem;

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void App::run()
{
    m_LastTime = glfwGetTime();
    m_NumFrames = 0;
    m_FrameTime = 16.0f;
    
    while (!glfwWindowShouldClose(m_Window))
    {

        bool should_close = m_CameraSystem->update(m_FrameTime/1000.0f);
        if (should_close){
            break;
        }

        m_RenderSystem->update();
        
        //  After rendering, update screen
        //  because another render system is to be made.
        glfwSwapBuffers(m_Window);

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

    m_Window = glfwCreateWindow(640, 480, m_WinName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(0);
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

    glDisable(GL_DEPTH_TEST);

    m_Shaders.push_back(make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    ));

    m_Shaders.push_back(make_compute_shader(
        "../core/src/shaders/raytracer.txt"
    ));


    TextureFactory factory;
    //  Consider this color buffer as a frame buffer
    m_ColorBuffer = factory.build_colorbuffer(m_Window);
}

void App::make_systems()
{
    m_CameraSystem = new CameraSystem(m_Shaders, m_Window,
                         m_CameraComponents);
    m_RenderSystem = new RenderSystem(m_Shaders, m_Window, m_ColorBuffer);
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
        title << "Running at " << framerate << " fps.";
        glfwSetWindowTitle(m_Window, (m_WinName + title.str()).c_str());
        m_LastTime = m_CurrentTime;
        m_NumFrames = -1;
        m_FrameTime = float(1000.0 / framerate);
    }
    ++m_NumFrames;
}