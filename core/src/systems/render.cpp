#include "render.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



RenderSystem::RenderSystem(uint32_t shader, GLFWwindow* window, ComponentRegistry& componentRegistry):
    m_ComponentRegistry(componentRegistry)
{
   this->m_Shader = shader;
   this->m_Window = window;
   build_models();

   glUseProgram(m_Shader);
   m_ModelLocation = glGetUniformLocation(m_Shader, "u_Model");
   m_ObjectTypeLocation = glGetUniformLocation(m_Shader, "u_ObjectType");
}

RenderSystem::~RenderSystem()
{
    for (std::pair<ObjectType, Mesh> item : m_Meshes){
        Mesh model = item.second;
        glDeleteVertexArrays(1, &model.VAO);
        glDeleteBuffers(1, &model.VBO);
        glDeleteTextures(1, &model.material);
    }
}

void RenderSystem::build_models()
{
    MeshFactory meshFactory;
    for (uint32_t i = 0; i < objectTypeCount; ++i){
        m_Meshes[static_cast<ObjectType>(i)] = meshFactory.make_mesh(i);
    }
    m_Material = meshFactory.load_materials();
}

void RenderSystem::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Material);

    for (size_t i = 0; i < m_ComponentRegistry.renderables.m_Entities.size(); ++i) {
        uint32_t& id = m_ComponentRegistry.renderables.m_Entities[i];
        RenderComponent& object = m_ComponentRegistry.renderables.m_Components[i];
        TransformComponent& transform = m_ComponentRegistry.transforms.get_component(id);
        Mesh& mesh = m_Meshes[object.objectType];

        //   Not needed since its a GL_TEXTURE_2D_ARRAY being used
        // glBindTexture(GL_TEXTURE_2D, mesh.material);
        glBindVertexArray(mesh.VAO);
        glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, glm::value_ptr(build_model_transform(transform)));
        glUniform1f(m_ObjectTypeLocation, static_cast<float>(object.objectType));
        glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, (void*) 0);
    }
    
    glfwSwapBuffers(m_Window);
}

glm::mat4 RenderSystem::build_model_transform(TransformComponent& transform)
{
    float& scale = transform.scale;

    glm::mat4 scale_and_flip = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.position);
    glm::mat4 rotate_y = glm::rotate(glm::mat4(1.0f), glm::radians(transform.eulers.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotate_z = glm::rotate(glm::mat4(1.0f), glm::radians(transform.eulers.z), glm::vec3(0.0f, 0.0f, 1.0f));
    return translate * rotate_z * rotate_y * scale_and_flip;
}