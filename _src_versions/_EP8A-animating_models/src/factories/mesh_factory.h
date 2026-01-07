#pragma once
#include "../config.h"
#include "../components/render_component.h"

class MeshFactory
{
public:
    ~MeshFactory();

    RenderComponent make_cube_mesh(
        ObjectType objectType, glm::vec3 size);
    RenderComponent make_obj_mesh(
        ObjectType objectType, const char* filepath,
        glm::mat4 preTransform
    );
    
    unsigned int make_texture(ObjectType objectType, const char* filename);

    glm::vec3 read_vec3(std::vector<std::string> words, float w);

    glm::vec2 read_vec2(std::vector<std::string> words);

    void read_face(std::vector<std::string> words);
    
    void read_corner(std::string description);

private:
    std::unordered_map<ObjectType, unsigned int> m_VAOs;
    std::unordered_map<ObjectType, unsigned int> m_VertexCounts;
    std::unordered_map<ObjectType, unsigned int> m_VBOs;
    std::unordered_map<ObjectType, unsigned int> m_Textures;

    std::vector<glm::vec3> m_V;
    std::vector<glm::vec2> m_Vt;
    std::vector<glm::vec3> m_Vn;
    std::vector<float> m_Vertices;

    glm::mat4 m_PreTransform;
};