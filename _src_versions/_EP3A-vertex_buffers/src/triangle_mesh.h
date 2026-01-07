
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

class TriangleMesh{
public:
    TriangleMesh();
    ~TriangleMesh() = default;


public:
    void draw();

private:
    unsigned int m_vertexCount;
    unsigned int m_vbo;
    unsigned int m_vao;
    // unsigned int m_ibo;

};