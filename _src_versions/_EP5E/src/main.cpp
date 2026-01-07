/**
 * @date 2024-12-24
 * 
 *  Episode 5: "OpenGL with C++ 5: Transformations"
 *      Implemented many Transformations:
 *          +   Translation
 *          +   Rotation around X axis
 *          +   Combined Translation and Rotation matrices
 *          +   Creating View matrix.
 *          +   Creating the Projection matrix
 *          
 *  In this _EP5E, everything is done but with GLM, GL Math Library, not our own linear_maths
 *  library.
 *  
 */
#include "config.h"
#include "triangle_mesh.h"
#include "material.h"

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
    glm::vec3 quad_position = {-0.2f, 0.4f, 0.0f};
    // lm::mat4 model = lm::create_matrix_transform(quad_position);
    /**
     *  This will cause us to be further from the quad and a little above the quad
     *  while looking at the origin
     */
    // lm::vec3 camera_pos = {-0.4f, 0.0f, 0.2f};
    glm::vec3 camera_pos = {-5.0f, 0.0f, 3.0f};  //  Further Away
    glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
    glm::vec3 up = {0.0f, 0.0f, 1.0f};

    /**
     *  Getting a Uniform first includes getting its location and
     *  then giving it a value and sending that value through it in this way: 
     */
    unsigned int model_location = glGetUniformLocation(shader, "u_Model");
    unsigned int view_location = glGetUniformLocation(shader, "u_View");
    unsigned int projection_location = glGetUniformLocation(shader, "u_Projection");

    glm::mat4 view = glm::lookAt(camera_pos, camera_target, up);
    //  The glm::value_ptr gets a pointer to the rotations in the matrix.
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    /**
     *  arg1: FOV
     *  arg2: Aspect Ratio
     *  arg3: Anything closer than 0.1f will not be drawn
     *  arg4: Anything further than 10.0f will not be drawn.
     */
    // lm::mat4 projection = lm::create_perspective_projection(
    //     45.0f, 640.0f/480.0f, 0.1f, 10.0f
    // );
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f/480.0f, 0.1f, 10.0f
    );
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));


    while (!glfwWindowShouldClose(window))
    {
        /**
         * @brief 
         *  This keeps the event queue from overflowing by clearing it every frame. 
         */
        glfwPollEvents();

        // glm::mat4 model = lm::create_z_rotation(10 * glfwGetTime());
        // glm::mat4 model = lm::create_model_transform(quad_position, 10 * glfwGetTime());
        /**
         *  It stacks the transformations. Note how it takes the og matrix
         *  `model`
         *   then stacks the transformation
         *   then does the same for the rotate
        */
        glm::mat4 model = glm::mat4(1.0f);
        //  The translation matrix
        model = glm::translate(model, quad_position);
        //  The rotation matrix; arg1: matrix to transform
        //  arg2: angle rotating by --- should convert to float to avoid errors
        //  arg3: the point being rotated around
        model = glm::rotate(model, (float)glfwGetTime(), {0.0f, 0.0f, 1.0f});
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        
        
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