#include "mesh_factory.h"

StaticMesh MeshFactory::make_cube_mesh(glm::vec3 size)
{
    float l = size.x;
    float w = size.y;
    float h = size.z;

    m_Vertices = {
         l,  w, -h, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         l, -w, -h, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l,  w, -h, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         l,  w, -h, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,

        -l, -w,  h, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         l, -w,  h, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -l,  w,  h, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -l, -w,  h, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

        -l,  w,  h, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -l,  w, -h, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w,  h, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -l,  w,  h, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

         l, -w, -h, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         l,  w, -h, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l, -w,  h, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l, -w, -h, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -l, -w, -h, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         l, -w, -h, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         l, -w,  h, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         l, -w,  h, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -l, -w,  h, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

         l,  w,  h, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         l,  w, -h, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w, -h, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w, -h, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w,  h, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float),
        m_Vertices.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    m_Vertices.clear();

    StaticMesh mesh;
    mesh.VAO = VAO;
    mesh.vertexCount = 36;
    mesh.VBO = VBO;
    return mesh;
}


StaticMesh MeshFactory::make_obj_mesh(
    const char* objFilepath, glm::mat4 preTransform)
{
    this->m_PreTransform = preTransform;

    size_t vertexCount = 0;
    size_t texCoordCount = 0;
    size_t normalCount = 0;
    size_t triangleCount = 0;

    std::string line;
    std::vector<std::string> words;

    std::ifstream file;

    file.open(objFilepath);
    while (std::getline(file, line))
    {
        words = ObjLoader::split(line, " ");

        if (!words[0].compare("v")){
            ++vertexCount;
        }
        else if (!words[0].compare("vt")){
            ++texCoordCount;
        }
        else if (!words[0].compare("vn")){
            ++normalCount;
        }
        else if (!words[0].compare("f")){
            triangleCount += words.size() - 3;
        }
    }
    file.close();

    m_V.reserve(vertexCount);
    m_Vt.reserve(texCoordCount);
    m_Vn.reserve(normalCount);
    //  Three corners per triangle, 8 floats per corner
    m_Vertices.reserve(triangleCount * 3 * 8);

    file.open(objFilepath);
    while (std::getline(file, line))
    {
        words = ObjLoader::split(line, " ");
        if (!words[0].compare("v")){
            m_V.push_back(read_vec3(words, 1.0f));
        }
        else if (!words[0].compare("vt")){
            m_Vt.push_back(read_vec2(words));
        }
        else if (!words[0].compare("vn")){
            m_Vn.push_back(read_vec3(words, 0.0f));
        }
        else if (!words[0].compare("f")){
            read_face(words);
        }
    }
    file.close();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), 
        m_Vertices.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    StaticMesh mesh;
    mesh.VAO = VAO;
    mesh.vertexCount = m_Vertices.size() / 8;
    mesh.VBO = VBO;

    m_V.clear();
    m_Vt.clear();
    m_Vn.clear();
    m_Vertices.clear();

    return mesh;
}


glm::vec3 MeshFactory::read_vec3(std::vector<std::string> words, float w) {
    //  Note how the vec4 is turned to vec3
    return glm::vec3(
        m_PreTransform * glm::vec4(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]), w)
    );
}

glm::vec2 MeshFactory::read_vec2(std::vector<std::string> words) {
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

void MeshFactory::read_face(std::vector<std::string> words)
{
    size_t triangleCount = words.size() - 3;

    for (size_t i = 0; i < triangleCount; ++i) {
        read_corner(words[1]);
        read_corner(words[2 + i]);
        read_corner(words[3 + i]);
    }
}


void MeshFactory::read_corner(std::string description)
{
    std::vector<std::string> v_vt_vn = ObjLoader::split(description, "/");

    //position
    glm::vec3 pos = m_V[std::stol(v_vt_vn[0]) - 1];
    m_Vertices.push_back(pos[0]);
    m_Vertices.push_back(pos[1]);
    m_Vertices.push_back(pos[2]);

    //tex coord
    glm::vec2 texcoord = m_Vt[std::stol(v_vt_vn[1]) - 1];
    m_Vertices.push_back(texcoord[0]);
    m_Vertices.push_back(texcoord[1]);

    //normal
    glm::vec3 normal = m_Vn[std::stol(v_vt_vn[2]) - 1];
    m_Vertices.push_back(normal[0]);
    m_Vertices.push_back(normal[1]);
    m_Vertices.push_back(normal[2]);
}
