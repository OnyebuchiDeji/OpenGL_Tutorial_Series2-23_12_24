#include "config.h"

class Cube {
public:
    Cube(glm::vec3 position, glm::vec3 size);
    ~Cube();
    void update(float dt);
    void draw(unsigned int shader);

private:
    glm::vec3 m_Position, m_Eulers;
    unsigned int m_VAO, m_VBO, m_Texture;

    void make_texture();
    void make_mesh(float l, float w, float h);
};