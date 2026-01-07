#include "config.h"
#include "../_vendor/stb_image.h"



class Material
{
public:
    Material(const char* fileName);
    ~Material();
    void use();

private:
    GLuint m_texture;
};