
#include "shader.h"

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

unsigned int make_compute_shader(const std::string& filepath)
{
    unsigned int module = make_shader_module(filepath, GL_COMPUTE_SHADER);

    //  Attach all the modules then link the program
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, module);
    glLinkProgram(shader);

    //  Check that the linking worked 
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success){
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Linking Error:" << errorLog << "\n";
    }
    glDeleteShader(module);

    return shader;
}