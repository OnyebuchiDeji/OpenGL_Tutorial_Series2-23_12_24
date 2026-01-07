/**
 * @date 2024-12-24
 * 
 * Episode 4: "OpenGL with C++ 4: Textures"
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

    //  From the GLAD library for the OpenGL functions
    glClearColor(0.85f, 0.3f, 0.7f, 1.0f);

    //  Get Frame Buffer Size to set the Viewport to render to
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    //  This double checks that the frame has been setup correctly!
    std::cout << "Width: " << w << ", Height: " << h << "\n";
    /**
     *  Now one can modify the viewport to change the effect of the normalized coordinates
     *  E.g., by setting it to: glViewport(0, 0, w * 0.5, h * 0.5)...
     *  one changes the [-1..1] normalization to be as [-2..2] because now,
     *  [-1..1] maps to [320px...240px] of the screen, but the screen is [640..480]...
     *  Now, OpenGL can only work with the pixels within [0, 0] and [320, 240]...
     *  hence it considers the pixels between [320..240] as the only pixels to draw to
     *  This can be useful.
     *  But it's not like it actually affects the pixelspace, just where OpenGL thinks is the pixel space.
     * 
     *  Proof is that when, in the TriangleMesh, one of the vertices was changed to -2.0, because
     *  this is above -1.0, OpenGL didn't process that pixel. It remained clamped to -1.0 within the
     *  [320..240] region
     *  
     *  
     */
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
    
    glEnable(GL_BLEND);
    /**
     *  What the below does is that a weighted sum or linear combination of the two values.
     *  These values are:
     *      The Src Pixel's Alpha value.
     *      The Destination Pixel's alpha value
     *  arg1: the formula for the source pixel weighting.
     *  arg2: the formula for the destination pixel weighting
     *  The Blend Functions specifies that it wants to do a weighted sum of the two values.
     *  Specifically, one between the source pixels * its alpha and the target pixels * (1 - source pixel's alpha value) 
     *  For example, if the source pixel has 75% for its alpha value...
     *  it is added to 25% of the destination pixel's alpha value.
     *  one that consists of 10% of the source_pixel_alpha, and 90% of the destination pixel alpha.
     * 
     *  This causes blending. 
     */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /**
     * @brief 
     *  Keep the window up until the Close button is clicked.
     * 
     */
    while (!glfwWindowShouldClose(window))
    {
        /**
         * @brief 
         *  This keeps the event queue from overflowing by clearing it every frame. 
         */
        glfwPollEvents();

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