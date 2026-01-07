#pragma once
#include "../config.h"

class TextureFactory
{
public:
    //  Declares how many layers of ttextures to be made
    void start_texture_array(int layers);

    void load_into_array(const char* filepath, int layer);
    
    unsigned int finalize_texture_array();

    unsigned int build_cubemap(std::vector<const char*> filepaths);

    /**
     *  Window is passed in here to get the size to be used...
     *  It's to ensure that these custom color buffer and depth buffers
     *  are built to accommodate this window.
     * 
     *  And these new buffers are represented by an ID unsigned integer...
     */
    unsigned int build_colorbuffer(GLFWwindow* window);

    unsigned int build_depthbuffer(GLFWwindow* window);

    /**
     *  This abstract object has things attached to it, specifically
     *  the color and depth buffers
     */
    unsigned int build_framebuffer(unsigned int colorbuffer, unsigned int depthbuffer);

private:
    unsigned int rows, cols;
    unsigned int m_Texture;
    
};