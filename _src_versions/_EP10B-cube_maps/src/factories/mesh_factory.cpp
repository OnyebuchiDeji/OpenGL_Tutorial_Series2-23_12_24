#include "mesh_factory.h"

/**
 *  @NOTE: The Layer data is usd to identify the appropriate texture for the corresponding model
 *  especially in the batch rendering of static components.
 */


void MeshFactory::start_obj_mesh()
{
    //  Clear ANy State
    m_V.clear();
    m_Vt.clear();
    m_Vn.clear();
    m_Vertices.clear();
    m_Indices.clear();
    m_VLoaded = 0;
    m_VtLoaded = 0;
    m_VnLoaded = 0;
    m_LastIndex = 0;
    m_LastIndexCurrent = 0;
    m_ElementCount = 0;
    m_Offset = 0;

    // m_CurrentLayer = 0;  //  No more reset here
}

void MeshFactory::append_obj_mesh(
    const char* objFilepath, glm::mat4 preTransform, float layer)
{
    m_CurrentLayer = layer;
    m_History.clear();

    this->m_PreTransform = preTransform;

    reserve_space(objFilepath);
    read_file(objFilepath);

    m_LastIndex = m_LastIndexCurrent + 1;

    m_VLoaded = m_V.size();
    m_VtLoaded = m_Vt.size();
    m_VnLoaded = m_Vn.size();
    m_Offset = m_Indices.size();
}

//  Updated to use Index or Element buffer
StaticMesh MeshFactory::build_obj_mesh()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), 
        m_Vertices.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 36, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 36, (void*)12);
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 36, (void*)24);
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_Indices.size() * sizeof(unsigned int),
        m_Indices.data(), GL_STATIC_DRAW);

    StaticMesh mesh;
    mesh.VAO = VAO;
    mesh.VBO = VBO;
    mesh.EBO = EBO;
    m_V.clear();
    m_Vt.clear();
    m_Vn.clear();
    m_Vertices.clear();
    m_Indices.clear();

    return mesh;
}



void MeshFactory::reserve_space(const char* filepath)
{
    //  To know the count since the previous read
    size_t vertexCount = m_V.size();
    size_t texCoordCount = m_Vt.size();
    size_t normalCount = m_Vn.size();
    size_t dataCount = m_Vertices.size();
    size_t indexCount = m_Indices.size();

    std::string line;
    std::vector<std::string> words;

    std::ifstream file;

    file.open(filepath);
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
            //  The number of vertex data per point was 8, now 9 because of 'layer' data
            //  Number of floats per triangle: 3
            dataCount += 3 * 9 * (words.size() - 3);
            //  Each word contains a number of vertices
            //  This keeps track of one whole vertex data for a point   
            indexCount += 3 * (words.size() - 3);
        }
    }
    file.close();

    m_V.reserve(vertexCount);
    m_Vt.reserve(texCoordCount);
    m_Vn.reserve(normalCount);
    //  Three corners per triangle, 8 floats per corner
    m_Vertices.reserve(dataCount);
    m_Indices.reserve(indexCount);
}

void MeshFactory::read_file(const char* filepath)
{
   std::string line;
    std::vector<std::string> words;

    std::ifstream file;

    file.open(filepath);
    
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
            m_Vn.push_back(glm::normalize(read_vec3(words, 0.0f)));
        }
        else if (!words[0].compare("f")){
            read_face(words);
        }
    }
    file.close();
}

glm::vec2 MeshFactory::read_vec2(std::vector<std::string> words) {
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

glm::vec3 MeshFactory::read_vec3(std::vector<std::string> words, float w) {
    //  Note how the vec4 is turned to vec3
    return glm::vec3(
        m_PreTransform * glm::vec4(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]), w)
    );
}

/** Takes points that make up a triangle */
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
    ++m_ElementCount;

    if (m_History.contains(description)){
        m_Indices.push_back(m_History[description]);
        return;
    }

    unsigned int index = m_History.size() + m_LastIndex;
    m_History[description] = index;
    m_Indices.push_back(index);

    if (index > m_LastIndexCurrent){
        m_LastIndexCurrent = index;
    }

    std::vector<std::string> v_vt_vn = ObjLoader::split(description, "/");

    //position
    glm::vec3 pos = m_V[m_VLoaded + std::stol(v_vt_vn[0]) - 1];
    m_Vertices.push_back(pos[0]);
    m_Vertices.push_back(pos[1]);
    m_Vertices.push_back(pos[2]);

    //tex coord
    glm::vec2 texcoord = m_Vt[m_VtLoaded + std::stol(v_vt_vn[1]) - 1];
    m_Vertices.push_back(texcoord[0]);
    m_Vertices.push_back(texcoord[1]);
    m_Vertices.push_back(m_CurrentLayer);

    //normal
    glm::vec3 normal = m_Vn[m_VnLoaded + std::stol(v_vt_vn[2]) - 1];
    m_Vertices.push_back(normal[0]);
    m_Vertices.push_back(normal[1]);
    m_Vertices.push_back(normal[2]);
}
