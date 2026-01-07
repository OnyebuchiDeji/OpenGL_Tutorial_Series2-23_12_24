#include "renderer.h"

Renderer::Renderer(GLFWwindow* window)
{
    this->m_Window = window;
    make_assets();
    set_up_opengl(window);
}

void Renderer::render(Scene* scene)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_Shader);
    glUniformMatrix4fv(
        m_ViewLocation, 1, GL_FALSE,
        glm::value_ptr(scene->m_Camera.get_view_transform())
    );
    m_CubeMaterial->use();
    for (Cube& cube : scene->m_Cubes)
    {
        glUniformMatrix4fv(
            m_ModelLocation, 1, GL_FALSE,
            glm::value_ptr(cube.get_model_transform())
        );
        m_CubeMesh->draw();
    }
    glfwSwapBuffers(m_Window);
}

Renderer::~Renderer()
{
    glDeleteProgram(m_Shader);
    delete m_CubeMesh;
    delete m_CubeMaterial;
}

void Renderer::set_up_opengl(GLFWwindow* window)
{
    glClearColor(0.25f, 0.13f, 0.53f, 1.0f);
    //  Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    //  (left, top, widht, height)
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glUseProgram(m_Shader);
    m_ModelLocation = glGetUniformLocation(m_Shader, "u_Model");
    m_ViewLocation = glGetUniformLocation(m_Shader, "u_View");
    unsigned int projLocation = glGetUniformLocation(m_Shader, "u_Projection");
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 10.0f
    );
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::make_assets()
{
    m_CubeMesh = new CubeMesh({0.25f, 0.25f, 0.25f});
    m_CubeMaterial = new Material("../core/_resources/img/spider_3d_image1a.jpg");
    m_Shader = make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    );
}