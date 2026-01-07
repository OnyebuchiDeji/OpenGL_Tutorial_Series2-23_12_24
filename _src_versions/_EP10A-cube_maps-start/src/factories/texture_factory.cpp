#include "texture_factory.h"
#include "../_vendor/stb_image.h"


void TextureFactory::start_texture_array(int layers)
{
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Texture);

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, layers, GL_RGBA8, 1024, 1024, layers);
}

void TextureFactory::load_into_array(const char* filepath, int layer)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    
	unsigned char* data = stbi_load(
        filepath, &width, &height, &channels, STBI_rgb_alpha);

	
    //  Appending Texture data
    /**
     *  arg1: Target Object
     *  arg2:  Texture Level
     *  arg3: x offset in buffer
     *  arg4: y offset
     *  arg5: z offset -- points to which layer to register the current texture to
     *  arg6: Internal Format / source image format
     *  arg7:  source width
     *  arg8:  source height
     *  arg9:  depth refers to which layer is being registered.
     *  arg10: Dest Format
     *  arg11: Data type
     *  arg12: Data address
     */
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