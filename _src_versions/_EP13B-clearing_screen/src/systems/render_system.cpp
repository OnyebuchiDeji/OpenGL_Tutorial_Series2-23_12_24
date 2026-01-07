#include "render_system.h"

RenderSystem::RenderSystem(std::vector<unsigned int>& shaders,
        GLFWwindow* window, unsigned int colorbuffer):
    m_Shaders(shaders), m_ColorBuffer(colorbuffer)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    m_WorkGroupCountX = (w + 7) / 8;
    m_WorkGroupCountY = (h + 7) / 8;    //  quick ceiling calculation
}

RenderSystem::~RenderSystem()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void RenderSystem::update() {
    //  Raytrace
    glUseProgram(m_Shaders[1]);
    glBindImageTexture(0, m_ColorBuffer, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(m_WorkGroupCountX, m_WorkGroupCountX, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    
    //  Screen
    glUseProgram(m_Shaders[0]);
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}