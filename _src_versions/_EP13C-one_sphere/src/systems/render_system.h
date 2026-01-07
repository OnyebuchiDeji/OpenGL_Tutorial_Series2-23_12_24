#pragma once
#include "../config.h"
// #include "../components/component_set.h"

class RenderSystem
{
public:
    RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
        unsigned int colorbuffer);  
    ~RenderSystem();
    
    void update();
 
private:
    /**
     *  This is for the animations...
     *  it is used to keep track of the different frames for every object made... especially the
     *  objects with animations as they would have more than one VBO object
     * 
     *  If not animated, it is a collection with one frame in it; so one VBO.
     
     */
    std::vector<unsigned int>& m_Shaders;

    unsigned int m_VAO, m_ColorBuffer;
    int m_WorkGroupCountX, m_WorkGroupCountY;
};