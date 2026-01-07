#pragma once
#include "../config.h"
#include "../components/render_component.h"

struct StaticMesh
{
    unsigned int VAO, VBO, vertexCount;
};

class MeshFactory
{
public:
    //  This is to make meshes
    void start_obj_mesh();
    void append_cube_mesh(glm::vec3 size, float layer);
    //  The layer identifies the texture.
    //  for each object data appended, the specified texture data: (u, v, id) are appended
    void append_obj_mesh(const char* objFilepath, glm::mat4 preTransform, float layer);

    StaticMesh build_obj_mesh();

private:

    /**
     *  This reserves space in the appropriate buffer after reading the file
     *  to count how many vertices, texture vertices, and vertex normals there are.
     */
    void reserve_space(const char* filepath);
    //  Then this loads the actual data from the file.
    void read_file(const char* filepath);

    glm::vec3 read_vec3(std::vector<std::string> words, float w);

    glm::vec2 read_vec2(std::vector<std::string> words);

    void read_face(std::vector<std::string> words);
    
    void read_corner(std::string description);

private:
    std::vector<glm::vec3> m_V;
    std::vector<glm::vec2> m_Vt;
    std::vector<glm::vec3> m_Vn;
    std::vector<float> m_Vertices;

    /**
     *  Now, because batch rendering, which involves loading all the .obj file data
     *  into a single VBO, is used, the below members keep track of how many
     *  vertices, texture vertices, and vertices' normals have been loaded,
     *  as a way of keeping ID of which 3d model is which. 
     */
    size_t m_VLoaded, m_VtLoaded, m_VnLoaded;
    float m_CurrentLayer;

    
    
    glm::mat4 m_PreTransform;
};