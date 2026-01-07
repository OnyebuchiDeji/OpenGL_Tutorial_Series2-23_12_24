#include "render_system.h"

RenderSystem::RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
        unsigned int colorbuffer):
    m_Shaders(shaders), m_ColorBuffer(colorbuffer)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

RenderSystem::~RenderSystem()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void RenderSystem::update() {
    //  Screen
    glUseProgram(m_Shaders[0]);
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}