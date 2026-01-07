#include "post_system.h"

PostSystem::PostSystem(unsigned int shader, unsigned int colorbuffer):
    m_Shader(shader), m_ColorBuffer(colorbuffer)
{
    
}

void PostSystem::update()
{
    /**
     *  The 0 is the value of the default frame buffer
     *  so this sets the screen as the render target
     *  so anything drawn appears there
     * 
     */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //  Since just a normal quad is being drawn, no
    //  no Depth Testing is needed here
    glDisable(GL_DEPTH_TEST);
    //  Clear Screen but don't clear depth buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //  Screen
    glUseProgram(m_Shader);
    //  Ensure target texture unit is 0 because Sky uses texture unit 1
    glActiveTexture(GL_TEXTURE0);
    //  Get the texture that was rendered to and set it as the draw source
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    //  Note no mesh is bound --- that is, no VBO or VAO, because
    //  they are hard-coded in the shader.
    glDrawArrays(GL_TRIANGLES, 0, 6);
}