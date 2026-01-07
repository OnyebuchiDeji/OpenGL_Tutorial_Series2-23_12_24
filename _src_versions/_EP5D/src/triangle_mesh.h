
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

class TriangleMesh{
public:
    TriangleMesh();
    ~TriangleMesh();


public:
    void draw();

private:
    unsigned int m_vertexCount;
    std::vector<unsigned int> m_vbos;
    unsigned int m_vao, m_ebo;  //  ebo for element buffer object

};