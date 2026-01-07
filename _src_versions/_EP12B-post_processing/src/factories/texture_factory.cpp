#include "texture_factory.h"
#include "../_vendor/stb_image.h"


void TextureFactory::start_texture_array(int layers)
{
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Texture);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 1024, 1024, layers);
}

void TextureFactory::load_into_array(const char* filepath, int layer)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    
	unsigned char* data = stbi_load(
        filepath, &width, &height, &channels, STBI_rgb_alpha);

    //  Upload to GPU
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
        0, 0, layer, width, height, 1,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
	stbi_image_free(data);
}

unsigned int TextureFactory::finalize_texture_array()
{
    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //  The below is just to wrap the value around
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    return m_Texture;
}

unsigned int TextureFactory::build_cubemap(std::vector<const char*> filepaths)
{
    //    Make Texture
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
    glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGBA8, 1024, 1024);

    //  Load Images
    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < 6; ++i)
    {
        int width, height, channels;
        unsigned char* data = stbi_load(filepaths[i],
            &width, &height, &channels, STBI_rgb_alpha);
        // Goes from +x -> -x -> +y -> -y -> +z -> -z
        //  By adding the integer you can go to the next
        //  The below loads in all 6 images into the cube map. 
        glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        //  Free Data
        stbi_image_free(data);
    }

    return m_Texture;

}

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
    //  Allocate Storage for the Image
    //  the reason GL_RGBA8 is used to to ensure 8 bytes for RGBA are allocated
    //  Using glTexImage2D allocates memory and initialized/used at once
    //  whereas glTexStorage2D allocates memory and fixes / doesn't use it
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);

    return colorbuffer;
}

unsigned int TextureFactory::build_depthbuffer(GLFWwindow* window)
{
    int width, height;
    //  Get image width and height
    glfwGetFramebufferSize(window, &width, &height);

    unsigned int depthbuffer;
    /**
     *  Render Buffer vs Texture
     *  A Texture is a Texture object + Sampler Object (for linear sampling)
     *  whereas, a Render Buffer is just a Buffer, a storage unit --- it
     *  just has a texture and no Sampler, and is unique because a shader
     *  can read from it as is, without a Sampler.
     */
    glGenRenderbuffers(1, &depthbuffer);    //  Generates render buffer
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    //  Allocates Memory:
    //  args: <target>, <format>, <w>, <h>
    //  One can use GL_DEPTH32... but using 32 bits without needing the extra space
    //  makes the depth test take longer.
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    return depthbuffer;
}

unsigned int TextureFactory::build_framebuffer(
    unsigned int colorbuffer, unsigned int depthbuffer)
{
    unsigned int framebuffer;

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    //  Attaching the frame buffer
    /**
     *  args: <target_being_attached>, <attach_slot_index>,
     *      <target type: texture >, <color buffer or texture id>, <mipmap level of texture>
     */
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D, colorbuffer, 0
    );

    //  Attaching
    /**
     *  args: <target_being_attached>, <attachment type>, <target type: render buffer>
     *      <depth/render buffer id>
     */
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER, depthbuffer
    );

    return framebuffer;
}