#include "app.h"
#include "../_vendor/stb_image.h"


App::App()
{
    set_up_glfw();
}

App::~App()
{
    glDeleteBuffers(m_VBOs.size(), m_VBOs.data());
    glDeleteVertexArrays(m_VAOs.size(), m_VAOs.data());
    glDeleteTextures(m_Textures.size(), m_Textures.data());
    
    delete m_MotionSystem;
    delete m_CameraSystem;
    delete m_RenderSystem;
    
    glfwTerminate();
}

/**
 *  Because each entity is represented by an ID...
 *  this just returns the ID of the current entity starting from 0.
 */
unsigned int App::make_entity()
{
    return m_EntityCount++;
}

unsigned int App::make_cube_mesh(glm::vec3 size)
{
    float l = size.x; float w = size.y; float h = size.z;
    std::vector<float> vertices = {
         l,  w, -h, 1.0f, 1.0f,
         l, -w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l,  w, -h, 0.0f, 1.0f,
         l,  w, -h, 1.0f, 1.0f,

        -l, -w,  h, 0.0f, 0.0f,
         l, -w,  h, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f,
        -l,  w,  h, 0.0f, 1.0f,
        -l, -w,  h, 0.0f, 0.0f,

        -l,  w,  h, 1.0f, 1.0f,
        -l,  w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l,  w,  h, 1.0f, 1.0f,

         l, -w, -h, 0.0f, 0.0f,
         l,  w, -h, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f,
         l, -w,  h, 0.0f, 1.0f,
         l, -w, -h, 0.0f, 0.0f,

        -l, -w, -h, 0.0f, 0.0f,
         l, -w, -h, 1.0f, 0.0f,
         l, -w,  h, 1.0f, 1.0f,  
         l, -w,  h, 1.0f, 1.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l, -w, -h, 0.0f, 0.0f,

         l,  w,  h, 1.0f, 1.0f,
         l,  w, -h, 1.0f, 0.0f,
        -l,  w, -h, 0.0f, 0.0f, 
        -l,  w, -h, 0.0f, 0.0f,
        -l,  w,  h, 0.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f
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
    //  position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    //  texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int App::make_texture(const char* filename)
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

void App::run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        m_MotionSystem->update(
            m_TransformComponents, m_PhysicsComponents,
            16.67f/1000.0f
        );
        bool should_close = m_CameraSystem->update(
            m_TransformComponents, m_CameraID, *m_CameraComponent, 16.67f / 1000.0f
        );
        if (should_close){
            break;
        }
        m_RenderSystem->update(m_TransformComponents, m_RenderComponents);
    }
}

void App::set_up_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_Window = glfwCreateWindow(640, 480, "HaKhaylemSoft Window", NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not load opengl!\n";
        glfwTerminate();
    }
}

void App::set_up_opengl()
{
    glClearColor(0.25f, 0.13f, 0.34f, 1.0f);
    //  Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(m_Window, &w, &h);
    //  (left, top, width, height)
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_Shader = make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    );

    glUseProgram(m_Shader);
    unsigned int projLocation = glGetUniformLocation(m_Shader, "u_Projection");
    //  args: fov, aspect_ratio, z_near, z_far
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 10.0f
    );
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

}

void App::make_systems()
{
    m_MotionSystem = new MotionSystem();
    m_CameraSystem = new CameraSystem(m_Shader, m_Window);
    m_RenderSystem = new RenderSystem(m_Shader, m_Window);
}