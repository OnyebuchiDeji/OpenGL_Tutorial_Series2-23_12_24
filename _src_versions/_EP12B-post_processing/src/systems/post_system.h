#pragma once
#include "../config.h"

/**
 *  The system takes this shader and the color buffer (texture rendered to offline)
 *  and works with them
 */
class PostSystem
{
public:
    PostSystem(unsigned int shader,
        unsigned int colorbuffer);
    void update();
private:
    unsigned int m_Shader, m_ColorBuffer;
};