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

private:
    unsigned int rows, cols;
    unsigned int m_Texture;
};