
/**
 *  Date: 24-12-2024
 *  Triangle Mesh class created by me, Ebenezer Ayo-Metibemu...
 *  because GetIntoGameDev just couldn't show the source code for these two files in the last episode.
 */

#include "triangle_mesh.h"


TriangleMesh::TriangleMesh()
{
    //  For x y, r, g, b
    m_vertices = new float[15]{
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 
    };

    m_indices = new unsigned int[3]{
        0,1,2
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    //  Make Buffer Object
    //  Maikng it static is only for this method
    //  so best to make it a member
    // static unsigned int buffer;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), m_vertices, GL_STATIC_DRAW);
    
    /***
     *  Takeaways:
     *      The Stride is the stride in bytes between separate vertex data; it is the second to last argument in the
     *      glVertexAttribPointer() function.
     *           That is,
     *                  -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,     <-- One Vertex Data = (3 + 2) floats
     *                   0.5f, -0.5f, 0.0f, 1.0f, 0.0f,      <-- Second Vertex Data = (3 + 2) floats
     *                   0.0f,  0.5f, 0.0f, 0.0f, 1.0f,      <-- Third Vertex Data = (3 + 2) floats

     *       The Offset is the offset to identify the different data types that are sent to the GPU, that is:
     *          glVertexAttribPointer(0, 2u, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0); <-- specifies for the x and y
     *      
     *          glVertexAttribPointer(1, 3u, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(2 * sizeof(float))); <<---
     *                  Consider how the last argument specifies the offset from the first type of data type (x and y), so the GPU
     *                  knows where the color data starts from.
     */
    glEnableVertexAttribArray(0);
    //  arg2: should be 2, since each vertex data consists of 2 floats for x and y in the first part
    glVertexAttribPointer(0, 2u, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)0);
    //  arg2: should be 3, since each vertex data consists of 3 floats for r, g, b in this second part
    glEnableVertexAttribArray(1);
    //  That last arg is offset of this part of the vertex data, from the beginning parts (the x and y)
    glVertexAttribPointer(1, 3u, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(2 * sizeof(float)));

    // static unsigned int ibo;
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), m_indices, GL_STATIC_DRAW);
}

TriangleMesh::~TriangleMesh()
{
    delete[] m_vertices;
    delete[] m_indices;

    glBindVertexArray(0);   //  Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);   //  Unbind VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   //  Unbind IBO
   
   //   They should be deleted normally -- The Cherno didn't do this
    // glDeleteVertexArrays(1, &m_vao);
    // glDeleteBuffers(1, &m_vbo);
    // glDeleteBuffers(1, &m_ibo);
}

void TriangleMesh::draw()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}