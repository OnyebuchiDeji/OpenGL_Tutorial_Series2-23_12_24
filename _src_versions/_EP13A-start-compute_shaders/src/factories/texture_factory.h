#pragma once
#include "../config.h"

class TextureFactory
{
public:
    /**
     *  Window is passed in here to get the size to be used...
     *  It's to ensure that these custom color buffer and depth buffers
     *  are built to accommodate this window.
     * 
     *  And these new buffers are represented by an ID unsigned integer...
     */
    unsigned int build_colorbuffer(GLFWwindow* window);
    
};