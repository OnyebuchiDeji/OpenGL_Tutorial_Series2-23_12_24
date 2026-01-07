#include "texture_factory.h"

unsigned int TextureFactory::build_colorbuffer(GLFWwindow* window)
{
    int width, height;
    // This queries for the size of the window to give the variables
    //  the appropriate size of the window.
    glfwGetFramebufferSize(window, &width, &height);

    unsigned int colorbuffer;
    glGenTextures(1, &colorbuffer);
    glBindTexture(GL_TEXTURE_2D, colorbuffer);
    //  Configure texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /**
     *  Allocate Storage for the Image
     *  the reason GL_RGBA8 is used to to ensure 8 bytes for RGBA are allocated
     *  Using glTexImage2D allocates memory and initialized/used at once
     *  whereas glTexStorage2D allocates memory and fixes / doesn't use it
     *  
     *  Type is changed to 32-float, as it's sent to the Compute Shader.
     */
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width, height);

    return colorbuffer;
}
