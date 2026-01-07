/**
 * @date 2024-12-24
 * 
 *  Episode 5: "OpenGL with C++ 5: Transformations"
 *      Implemented many Transformations:
 *          +   Translation
 *          +   Rotation around X axis
 *          +   Combined Translation and Rotation matrices -- formed a Geometric Matrix.
 *  
 *  This _EP5B: Here, both the Translation and Rotational matrices are made.
 *  Also, a Matrix that combines both transformations is made.
 * 
 *  In _EP5C, the Vieew Matrix is created.
 */
#include "config.h"
#include "triangle_mesh.h"
#include "material.h"
#include "linear_maths.h"

unsigned int make_shader_module(const std::string& filePath, unsigned int moduleType);

unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);

int main()
{
    std::cout << "This is the OpenGL Learning Tutorial!\n";

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "GLFW could not start!!!\n";
        return -1;
    }

    /**
     * @brief
     *  arg4: specifies which monitor the window will be full screened on.
     *      if NULL, it floats as a random window, not fullscreen anywhere.
     *      though one could specify primary monitor or secondary monitor fot it to appear
     *      full screen there.
     * 
     */
    window = glfwCreateWindow(640, 480, "Yo Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    //  Tell glad to fetch all openGL procedures
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //  From the GLAD library for the OpenGL functions
    glClearColor(0.85f, 0.3f, 0.7f, 1.0f);

    //  Get Frame Buffer Size to set the Viewport to render to
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    //  This double checks that the frame has been setup correctly!
    std::cout << "Width: " << w << ", Height: " << h << "\n";
    // glViewport(0, 0, w, h);
    // glViewport(0, 0, w*0.5, h*0.5);

    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material("../core/_resources/img/spider_3d_image1a.jpg");
    Material* mask = new Material("../core/_resources/img/vignette_mask1.jpg");

    //  Create Shader:
    unsigned int shader = make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    );

    //  Must Use the program before setting the Texture Units
    glUseProgram(shader);
    //  Set Texture Units.
    //  This looks for the Texture's location in the shader and
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    glUniform1i(glGetUniformLocation(shader, "mask"), 1);
    /**
     *  Defined the Transalation Vector.
     *  This should move each pixel position in the Vertex Data by 0.1f to the right
     *  and 0.2f downwards.
     *  The result should be the pixture being displaced downward to the right.
     */
    lm::vec3 quad_position = {0.1f, -0.2f, 0.0f};
    // lm::mat4 model = lm::create_matrix_transform(quad_position);

    /**
     *  Getting a Uniform first includes getting its location and
     *  then giving it a value and sending that value through it in this way: 
     */
    unsigned int model_location = glGetUniformLocation(shader, "u_Model");


    while (!glfwWindowShouldClose(window))
    {
        /**
         * @brief 
         *  This keeps the event queue from overflowing by clearing it every frame. 
         */
        glfwPollEvents();

        // lm::mat4 model = lm::create_z_rotation(10 * glfwGetTime());
        lm::mat4 model = lm::create_model_transform(quad_position, 10 * glfwGetTime());
         /**
         *  arg1: location of the uniform data is being uploaded to
         *  arg2: how many matrix uniforms are being uploaded
         *  arg3: should the matrices be transposed? This shouls always be false
         *  arg4: Pointer to the array being uploaded
         */

        glUniformMatrix4fv(model_location, 1, GL_FALSE, model.entries);
        
        //  To clear the color buffer and signalled by this bit.
        glClear(GL_COLOR_BUFFER_BIT);

        /**
         * Although no need for multiple calls on *glUseProgram*, it is good practice
         * to do this especially when coordinating programs.
         */
        glUseProgram(shader);
        material->use(0);
        mask->use(1);
        triangle->draw();

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete triangle;
    delete material;
    delete mask;
    glfwTerminate();


    return 0;
}


/**
 * @brief:
 *  This takes a fight path and creates a shader module.
 *  A shader module are the individual parts of the whole shader program.
 *  Shader Program = vertex_shader + fragment_shader
 *  vertex_shader and fragment_shader are shader modules.
 * 
 *  Note that the shader module returned is represented by an unsigned integer
 */


unsigned int make_shader_module(const std::string& filePath, unsigned int moduleType)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filePath);
    while (std::getline(file, line))
    {
        //  Dumping in StringStream that piles up strings
        bufferedLines << line << "\n";
    }
    std::string shaderModuleSource = bufferedLines.str();
    //  Converting from C++ string to C-style string
    const char* c_shaderModuleSource = shaderModuleSource.c_str();
    bufferedLines.str("");  //  Erases a string stream, but it doesn't matter
    file.close();

    unsigned int shaderModule = glCreateShader(moduleType);

    //  multiple source codes can be attached here.
    //  If NULL is specified, the whole file is looked through
    glShaderSource(shaderModule, 1, &c_shaderModuleSource, NULL);
    glCompileShader(shaderModule);

    int success;
    //  This reads the value into the status variable but you need to pass a pointer to that status variable
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module Compilation Error:\n" << errorLog << "\n";
    }

    return shaderModule;
}


unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_shader_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_shader_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();

    //  Attach/Link the Modules into one Program
    for (unsigned int shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Module Compilation Error:\n" << errorLog << "\n";
    }

    //  After Linking, delete the modules
    for (unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }
    modules.clear();

    return shader;
}