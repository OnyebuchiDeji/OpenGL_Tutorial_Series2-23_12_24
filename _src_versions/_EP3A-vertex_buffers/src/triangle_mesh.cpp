
/**
 *  Date: 24-12-2024
 *  Triangle Mesh class created by GetIntoGameDev
 *  Turns out the triangle is 3D in vector
 */

#include "triangle_mesh.h"


TriangleMesh::TriangleMesh()
{
    //  For x y, r, g, b
    // std::vector<float> vertices = {
    //     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //      0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    // };

    /**
     * @brief 
     *  These vertices are laid out to form a right-angled triangle
     * 
     *  Consider what is called the Normalised Device Coordinates (NDC)
     *  as they are normalized between [-1..1]
     * 
     *  Now, the vertices data can contain position values, colour values, texture coordinates, normals,
     *  and other heterogenous data like texture_indices (int), light_indices (int)
     *  even in skeletal animation, to save the integer index of the bone that will be influenceing a specific
     *  vertex.
     * 
     *  Heterogenous data is different data types together.
     * 
     *  Hence why vertices or Vertex Data contain Attribute Data... such as mentioned above.
     * 
     *  So a Vertex as below is a collection of attributes that are used to draw the points.
     */
    std::vector<float> vertices = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //  blue in bottom left
         1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //  yellow in bottom right
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,   //  yellow in top left
    };
    m_vertexCount = 3;

    // unsigned int indices[3] {
    //     0,1,2
    // };

    /**
     *  The VAO wraps up all the states needed to draw the VBO associated with its attributes
     *  specified by VertexAttribPointer.
     *  The VAO automatically records the data and its attributes.
     */

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    //  Make Buffer Object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    /**
     *  Note how `vertices.size()` gives the number of elements in the std::vector
     *  and how `vertices.data()` returns a pointer that gives (or points to) the memory address
     *  to the start of where the data is in memory.
     */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    /**
     *  These are what the GPU uses to know how to interpret the attributes
     *  specified in the buffer.
     * 
     *  arg4: Whether to normalize the data or not --- false
     *  arg5: stride; the number of bytes to step through to get to the next set of vertex data, e.g:
     *      [from here] -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   <--- to here is 6 * sizeof(float) = 24 bytes
     *      [from here] 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,    <--- to here is 24 bytes
     *  arg6: the offset between different attributes in a vertex data set
     *         (pos data starts at: 0) x, y, z, (color data starts at: 3 floats) r, g, b (end)
     *         -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
     * 
     *  Lastly is the `glEnableVertexAttribArray` vs. `glEnableVertexArrayAttrib`
     *  The first is the right one.
     *  The difference has to do with Direct State Access (DSA).
     *  The latter uses DSA but DSA is slower but meant to be semantically friendlier
     *      
     */
    //  Position Attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3u, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
    //  Color Attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3u, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

    // glGenBuffers(1, &m_ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}


void TriangleMesh::draw()
{
    glBindVertexArray(m_vao);
    /*
        Below two are for when an index buffer is used
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    */
   glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}