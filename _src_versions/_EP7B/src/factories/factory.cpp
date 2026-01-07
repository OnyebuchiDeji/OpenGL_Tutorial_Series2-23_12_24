#include "factory.h"
#include "../_vendor/stb_image.h"

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, RenderComponent>& renderComponents,
    std::unordered_map<unsigned int, TransformComponent>& transformComponents):
    m_PhysicsComponents(physicsComponents), m_RenderComponents(renderComponents),
    m_TransformComponents(transformComponents)
{
}

Factory::~Factory()
{
    glDeleteBuffers(m_VBOs.size(), m_VBOs.data());
    glDeleteVertexArrays(m_VAOs.size(), m_VAOs.data());
    glDeleteTextures(m_Textures.size(), m_Textures.data());
}

unsigned int Factory::make_camera(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    m_TransformComponents[m_EntitiesMade] = transform;
    return m_EntitiesMade++;
}

void Factory::make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    m_PhysicsComponents[m_EntitiesMade] = physics;

    RenderComponent render = make_cube_mesh({0.25f, 0.25f, 0.25f});
    render.material = make_texture("../_resources/img/spider_3d_image1a.jpg");
    m_RenderComponents[m_EntitiesMade++] = render;
}

void Factory::make_girl_model(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    m_TransformComponents[m_EntitiesMade] = transform;

    RenderComponent render = make_obj_mesh("../_resources/models/girl.obj");
    render.material = make_texture("../_resources/img/stargirl.png");
    m_RenderComponents[m_EntitiesMade++] = render;
}

RenderComponent Factory::make_cube_mesh(glm::vec3 size)
{
    float l = size.x;
    float w = size.y;
    float h = size.z;

    std::vector<float> vertices = {
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
    m_VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    m_VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                vertices.data(), GL_STATIC_DRAW);
    //  Position:
    /*
        Every three float data types, with a whole vertex data being 32 bytes to the next one...
        and the start of this position data being from index 0 for each vertex data
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);   //  This value is an index and it matches the above function's first argument
    //  Texture Coordinates: every 2 floats after the first three (positions) floats. 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //  Normal Coordinates
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    RenderComponent record;
    record.VAO = VAO;
    record.vertexCount = 36;

    return record;
}

RenderComponent Factory::make_obj_mesh(const char* filename)
{
    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;

    std::vector<float> vertices;

    /**
     *  Read through file twice:
     *  
     *  1.  Read through to know hw many vectors to expect to avoid dynamic memory resizing of the vectors
     *  2.  Read through the file to get the data components to populate the above vectors. 
     */

    size_t vertexCount = 0;
    size_t texCoordCount = 0;
    size_t normalCount= 0;
    size_t triangleCount = 0;

    std::string line;
    std::vector<std::string> words;

    std::ifstream file;
    file.open(filename);
    //  The below finds how many of each of the vertex data to expect. This preserves storage
    //  and gives a performance boost.
    while (std::getline(file, line))
    {
        words = ObjLoader::split(line, " ");

        //  This .compare() method compares if strings are equal by finding the difference
        //  in the characters as integers...
        //  So if they are equal, it results in 0.
        //  So by doing !, you ensure that it is not 0, to make the zero, 1
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
            //  Increment by the number of points defined - 3...
            //  because one of the words is the 'f' label
            triangleCount += words.size() - 3;;
        }
    }
    file.close();

    v.reserve(vertexCount);
    vt.reserve(texCoordCount);
    vn.reserve(normalCount);
    /**
     *  each triangle has 3 corners, and each corner has 8 floats:
     *  Now 3 floats for position data index, 2 more for texture coordinates, and 3 for the normal coordinates'index
     * This is 24 floats per triangle
     * 
     */
    vertices.reserve(triangleCount * 3 * 8);

    file.open(filename);

    while (std::getline(file, line))
    {
        words = ObjLoader::split(line, " ");

        if (!words[0].compare("v")){
            v.push_back(read_vec3(words));
        }
        else if (!words[0].compare("vt")){
            vt.push_back(read_vec2(words));
        }
        else if (!words[0].compare("vn")){
            vn.push_back(read_vec3(words));
        }
        else if (!words[0].compare("f")){
            //  read face
            read_face(words, v, vt, vn, vertices);
        }
    }
    file.close();

    std::cout << "loaded some .obj data:\n";
    std::cout << "\tvertices: " << v.size() << "\n";
    std::cout << "\ttex coords: " << vt.size() << "\n";
    std::cout << "\tnormals: " << vn.size() << "\n";

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    m_VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    m_VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                vertices.data(), GL_STATIC_DRAW);
    //  Position:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);   //  This value is an index and it matches the above function's first argument
    //  Texture Coordinates: every 2 floats after the first three (positions) floats. 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //  Normal Coordinates
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    RenderComponent record;
    record.VAO = VAO;
    record.vertexCount = vertices.size() / 8;

    return record;
}

glm::vec2 Factory::read_vec2(std::vector<std::string> words)
{
    //  The below is correct despite using an index not starting from 0...
    //  perhaps what std::stof does.
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}
glm::vec3 Factory::read_vec3(std::vector<std::string> words)
{
    return glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
}

void Factory::read_face(std::vector<std::string>& words, 
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
    std::vector<glm::vec3>& vn, std::vector<float>& vertices)
{
    size_t triangleCount = words.size() - 3;

    for (size_t i = 0; i < triangleCount; ++i)
    {
        //  read corner 1
        read_corner(words[1], v, vt, vn, vertices);
        //  read corner 2 + i
        read_corner(words[2 + i], v, vt, vn, vertices);
        //  read corner 3 + i
        read_corner(words[3 + i], v, vt, vn, vertices);
    }
}

void Factory::read_corner(std::string description,
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
    std::vector<glm::vec3>& vn, std::vector<float>& vertices)
{
    std::vector<std::string> v_vt_vn = ObjLoader::split(description, "/");

    //  position
    glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
    vertices.push_back(pos[0]);
    vertices.push_back(pos[1]);
    vertices.push_back(pos[2]);
    
    //  texture coords
    glm::vec2 tex = vt[std::stol(v_vt_vn[1]) - 1];
    vertices.push_back(tex[0]);
    vertices.push_back(tex[1]);

    //  normals
    glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
    vertices.push_back(normal[0]);
    vertices.push_back(normal[1]);
    vertices.push_back(normal[2]);
}

unsigned int Factory::make_texture(const char* filename)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(
        filename, &width, &height, &channels, STBI_rgb_alpha
    );
    //  make the texture
    unsigned int texture;
    glGenTextures(1, &texture);
    m_Textures.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //  load data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //  free data
    stbi_image_free(data);

    //  configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;

}