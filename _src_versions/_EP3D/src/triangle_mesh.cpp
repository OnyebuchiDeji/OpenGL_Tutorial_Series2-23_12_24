
/**
 *  Date: 24-12-2024
 *  Triangle Mesh class created by GetIntoGameDev
 * 
 *  In _EP3D, he demonstrates the use of index buffers.
 *  Bit here he calls them ElementBuffers/ElementIndices
 */

#include "triangle_mesh.h"


TriangleMesh::TriangleMesh()
{

    std::vector<float> positions = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
    };
    std::vector<int> colorIndices = {
        // 0, 1, 2, 2, 0, 1,
        0, 1, 2, 3, 0, 1,
    };
    std::vector<int> elementIndices ={
        0, 1, 2, 2, 1, 3
    };
    m_vertexCount = 6;

    /**
     *  The VAO wraps up all the states needed to draw the VBO associated with its attributes
     *  specified by VertexAttribPointer.
     *  The VAO automatically records the data and its attributes.
     */

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);


    m_vbos.resize(2);

    //  Make Buffer Objects
    glGenBuffers(2, m_vbos.data());

    //  Position Vertex Buffer and Attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3u, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

    //  Color Vertex Buffer and Attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(int), colorIndices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    /**
     *  Now, because it's an integer, it is `glVertexAttribIPointer`, not `glVertexAttribPointer`
     *  Also, arg1: 1 because it represents its id/location to be accessed by in the Shader Code.
     *  
     *  Also, note that unlike glVertexAttribPointer, glVertexAttribIPointer has no 'normalized' argument
     *  since integers should generally not be normalized.
     * 
     */
    glVertexAttribIPointer(1, 1u, GL_INT, sizeof(int), (const void*)0);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(int), elementIndices.data(), GL_STATIC_DRAW);
}


void TriangleMesh::draw()
{
    glBindVertexArray(m_vao);
    // glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, nullptr);
}


TriangleMesh::~TriangleMesh()
{
   glBindVertexArray(0);
   
   for (unsigned int i=0; i < m_vbos.size(); i++){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   
   glDeleteVertexArrays(1, &m_vao);
   glDeleteBuffers(2, m_vbos.data());
   glDeleteVertexArrays(1, &m_ebo);
}

