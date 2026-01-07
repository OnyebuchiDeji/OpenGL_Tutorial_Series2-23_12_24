#pragma once
#include "../config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../components/registry.h"
#include "../factories/model_factory.h"
// #include "../components/component_set.h"

class RenderSystem
{
public:
    RenderSystem(uint32_t shader, GLFWwindow* window,
         ComponentRegistry& componentRegistry);  
    ~RenderSystem();
    
    void update();
 
private:
    void build_models();
    glm::mat4 build_model_transform(TransformComponent& transform);
    
    uint32_t m_Shader, m_ModelLocation;
    GLFWwindow* m_Window;
    ComponentRegistry& m_ComponentRegistry;
    std::unordered_map<ObjectType, Mesh> m_Meshes;
    uint32_t m_Material, m_ObjectTypeLocation;
};