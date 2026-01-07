
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class TriangleMesh{
public:
    TriangleMesh();
    ~TriangleMesh();


public:
    void draw();

private:
    float* m_vertices;
    unsigned int* m_indices;
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ibo;

};