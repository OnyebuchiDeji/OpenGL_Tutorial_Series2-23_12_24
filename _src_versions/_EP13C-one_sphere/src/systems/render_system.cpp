#include "render_system.h"

RenderSystem::RenderSystem(std::vector<unsigned int>& shaders,
        GLFWwindow* window, unsigned int colorbuffer):
    m_Shaders(shaders), m_ColorBuffer(colorbuffer)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    //  This rounds up values to nearest multiple of 8.
    m_WorkGroupCountX = (w + 7) / 8;
    m_WorkGroupCountY = (h + 7) / 8;    //  quick ceiling calculation
}

RenderSystem::~RenderSystem()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void RenderSystem::update() {
    //  Raytrace
    //  Use Compute Shader Program
    glUseProgram(m_Shaders[1]);
    //  Binding Resources for the Compute Shader
    /**
     *  args: <texture_unit>, <texture_obj_id>, <mipmap level>, <layered?>, <layer to bind>,
     *      <access permission>, <format>
     * 
     *  This binds the image, preparing it to be written to.
     */
    glBindImageTexture(0, m_ColorBuffer, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    /**
     *  Sends these to compute shader rather, specifies the 2D work group
     *  Now, because this deploys this parallel work force, which will cause them to 
     *  start working on the image immediately...
     */
    glDispatchCompute(m_WorkGroupCountX, m_WorkGroupCountX, 1);


    /**
     *  So, as a solution, put up this memory barrier
     *  This really improved performance, removing a large overhead,
     *  of trying to access data not yet ready,  as against not having one.
     */
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    
    //  Screen
    glUseProgram(m_Shaders[0]);
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}