/**
 * @date: 29-12-2024
 * 
 *  Episode 6: "openGL with C++ 6: Design Patterns"
 *  This _EP6A demonstrates the first strucutre, the use of pure Object-Oriented programming.
 *  
 *  Note how the Cube and Camera classes are on their own, and contain all the data, transformations, and
 *  draw code.
 */
#include "config.h"
#include "cube.h"
#include "camera.h"

unsigned int make_shader_module(const std::string& filePath, unsigned int moduleType);

unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);


/**
 *  You'll see that the window pointer is not made static or such.
 *  This is because `glfwCreateWindow` returns the memory address to an opened window.
 *  This handle to an open window remains at that memory location until the window is closed
 *  or the program is exited.
 */
GLFWwindow* set_up_glfw()
{
    GLFWwindow* window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "HaKhaylem Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    return window;
}

void set_up_opengl(GLFWwindow* window)
{
    glClearColor(0.25f, 0.13f, 0.53f, 1.0f);
    //  Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    //  (left, top, width, height)
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


int main()
{
    std::cout << "This is the OpenGL Learning Tutorial!\n";

    if (!glfwInit())
    {
        std::cout << "GLFW could not start!!!\n";
        return -1;
    }

    GLFWwindow* window = set_up_glfw();

    //  Tell glad to fetch all openGL procedures
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Could not load opengl1\n";
        glfwTerminate();
        return -1;
    }

    set_up_opengl(window);

    //  Make Objects
    Cube* cube = new Cube({3.0f, 0.0f, 0.25f}, {0.25f, 0.25f, 0.25f});
    Camera* player = new Camera({0.0f, 0.0f, 1.0f});

    //  Create Shader
    unsigned int shader = make_shader_program(
        "../core/src/shaders/vertex.txt",
        "../core/src/shaders/fragment.txt"
    );

    //  Configure Shader
    glUseProgram(shader);
    unsigned int view_location = glGetUniformLocation(shader, "u_View");
    unsigned int proj_location = glGetUniformLocation(shader, "u_Projection");
    glm::mat4 projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window))
    {
        //  Keys
        glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            dPos.x += 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            dPos.y -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            dPos.x -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            dPos.y += 1.0f;
        }
        if (glm::length(dPos) > 0.1f){
            dPos = glm::normalize(dPos);
            player->move(dPos);
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            break;
        }
 
        //  Mouse
        glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        glfwSetCursorPos(window, 320.0, 240.0);
        glfwPollEvents();

        //  Taking the mouse's distance from the center of the screen
        //  where center is (320.0, 240.0)
        dEulers.z = -0.01f * static_cast<float>(mouse_x - 320.0);
        dEulers.y = -0.01f * static_cast<float>(mouse_y - 240.0);

        player->spin(dEulers);

        cube -> update(16.67f / 1000.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        glUniformMatrix4fv(
            view_location, 1, GL_FALSE,
            glm::value_ptr(player->get_view_transform()));
        cube->draw(shader);
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete cube;
    delete player;
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