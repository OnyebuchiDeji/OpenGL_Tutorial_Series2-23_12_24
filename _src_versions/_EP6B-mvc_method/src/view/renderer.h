#pragma once
#include "../config.h"
#include "shader.h"
#include "cube_mesh.h"
#include "material.h"
#include "../model/scene.h"

class Renderer
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    void render(Scene* scene);
private:
    void set_up_opengl(GLFWwindow* window);
    void make_assets();

    CubeMesh* m_CubeMesh;
    Material* m_CubeMaterial;
    GLFWwindow* m_Window;
    unsigned int m_Shader, m_ModelLocation, m_ViewLocation; 
};