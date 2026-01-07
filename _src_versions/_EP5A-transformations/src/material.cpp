#include "material.h"


Material::Material(const char* fileName)
{
    //  Load Data from Image file
    int width, height, channels;
    /**
     *  This populates this 'data' buffer with the image bytes. data is a pointer to it.
     *  and it stores the needed information about the image in the above variables (width, height, channels)
     *  by taking pointers to them.
     * 
     *  The last argument ensures the image is loaded with 4 channels even if the original image has just
     *  one or three channels. This makes things very easy.
     */
    unsigned char* data = stbi_load(fileName, &width, &height, &channels, STBI_rgb_alpha);

    //  Make the texture
    // glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);  //  <-- for some reason was not found. Maybe because of version of GLAD
    

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    //  Send Data to GPU
    /**
     *  arg1: gl target
     *  arg2: texture_level: 0
     *  arg3: how opengl should read/interpret the pixel data format.
     *      Here it is GL_RGBA, but can also be GL_RGBA8. 
     *      The latter specifies RGBA and 8 bits per channel
     *  arg6: border color -- 0 for black
     *  arg7: format of data being supplied
     *  arg8: type of data, which is a byte; unsigned byte; 8 bits
     *  arg9: pointer to data buffer.
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //  Free Data
    stbi_image_free(data);

    //  Configure Texture Sampler

    /**
     *  The minify filter describes how one samples when the image is shrunk down
     *  Likewise, the magnify filter does the same for when the image is enlarged
     */
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Material::~Material()
{
    glDeleteTextures(1, &m_texture);
}


void Material::use(int unitId)
{
    glActiveTexture(GL_TEXTURE0 + unitId);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}