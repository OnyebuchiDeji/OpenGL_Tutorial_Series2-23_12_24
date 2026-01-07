#include "app.h"


App::App()
{
    set_up_glfw();
    m_Scene = new Scene();
    m_Renderer = new Renderer(m_Window);
}

App::~App()
{
    delete m_Scene;
    delete m_Renderer;
    glfwTerminate();
}

void App::run()
{
    while (!glfwWindowShouldClose(m_Window)){
        if (handle_input()){
            break;
        }
        m_Scene->update(16.67f / 1000.0f);
        m_Renderer->render(m_Scene);
    }
}

bool App::handle_input()
{
    //  Keys
    glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS){
        dPos.x += 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS){
        dPos.y -= 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS){
        dPos.x -= 1.0f;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS){
        dPos.y += 1.0f;
    }
    if (glm::length(dPos) > 0.1f){
        dPos = glm::normalize(dPos);
        m_Scene->move_player(dPos);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        return true;
    }

    //  Mouse
    glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
    double mouse_x, mouse_y;
    glfwGetCursorPos(m_Window, &mouse_x, &mouse_y);
    glfwSetCursorPos(m_Window, 320.0, 240.0);
    glfwPollEvents();

    dEulers.z = -0.01f * static_cast<float>(mouse_x - 320.0);
    dEulers.y = -0.01f * static_cast<float>(mouse_y - 240.0);

    m_Scene->spin_player(dEulers);
    return false;
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