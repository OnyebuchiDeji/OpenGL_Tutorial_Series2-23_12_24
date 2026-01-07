#include "render_system.h"
#include "../factories/mesh_factory.h"
#include "../factories/texture_factory.h"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {
    
    m_ModelLocation = glGetUniformLocation(shader, "u_Model");
    this->m_Window = window;

    build_models();
    build_geometry();
}

RenderSystem::~RenderSystem()
{
    for (auto& [objectType, animations] : m_VAOs)
    {
        for (auto& [animation, arrays] : animations){
            glDeleteVertexArrays(arrays.size(), arrays.data());
        } 
    }
    for (auto& [objectType, animations] : m_VBOs)
    {
        for (auto& [animation, buffers] : animations)
        {
            glDeleteBuffers(buffers.size(), buffers.data());
        }
    }
    for (auto& [objectType, texture] : m_Textures){
        glDeleteTextures(1, &texture);
    }
}

void RenderSystem::build_models()
{
    ObjectType objectType;
    AnimationType animationType = AnimationType::eNone;
    
    MeshFactory meshFactory;
    TextureFactory textureFactory;


    objectType = ObjectType::eBox;
    m_Textures[objectType] = textureFactory.make_texture("../_resources/img/spider_3d_image1a.jpg");
    StaticMesh mesh = meshFactory.make_cube_mesh({0.25f, 0.25f, 0.25f});
    m_VAOs[objectType][animationType].push_back(mesh.VAO);
    m_VBOs[objectType][animationType].push_back(mesh.VBO);
    m_VertexCounts[objectType] = mesh.vertexCount;

/*     objectType = ObjectType::eGirl;
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform,
        glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
    preTransform = glm::rotate(preTransform,
        glm::radians(90.0f), {0.0f, 1.0f, 0.0f});
    mesh = meshFactory.make_obj_mesh("../_resources/models/girl.obj", preTransform);
    m_VAOs[objectType][animationType].push_back(mesh.VAO);
    m_VBOs[objectType][animationType].push_back(mesh.VBO);
    m_VertexCounts[objectType] = mesh.vertexCount;
    m_Textures[objectType] = textureFactory.make_texture("../_resources/img/stargirl.png");
 */
    objectType = ObjectType::eRevy;
    animationType = AnimationType::eRun;
    m_Textures[objectType] = textureFactory.make_texture("../_resources/img/Revy_Final.png");
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform,{0.0f, 0.0f, -1.0f});
    preTransform = glm::rotate(preTransform,
        glm::radians(-90.0f), { 0.0f, 0.0f, 1.0f });
    
    
    std::stringstream filepath;
    std::string built_filepath;
    //  Building file paths of .obj files to read from 
    for (size_t i = 0; i < 19; ++i){
        filepath.str("");
        filepath << "../_resources/models/Revy_run_0000";
        if (i <= 9){
            filepath << "0";
        }
        filepath << i << ".obj";
        built_filepath = filepath.str();
        mesh = meshFactory.make_obj_mesh(built_filepath.c_str(), preTransform);
        m_VAOs[objectType][animationType].push_back(mesh.VAO);
        m_VBOs[objectType][animationType].push_back(mesh.VBO);
        //  Extract the vertex count
        //  They should be the same for every .obj file that makes up the animation -- can print these to check.
        m_VertexCounts[objectType] = mesh.vertexCount;
    }

}
    

void RenderSystem::build_geometry()
{
    //  To Do...
}


void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent>& transformComponents,
    std::unordered_map<unsigned int,RenderComponent>& renderComponents,
    std::unordered_map<unsigned int,AnimationComponent>& animationComponents
    ) {
    
    //  Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  Loop throught every entity's render components to render them
    //  Note how it unpacks like in python; here the `entity` identifier
    //  holds the index/number of the entity as  it loops through the vector
    for (auto& [entity, renderable] : renderComponents)
    {
        //  Getting the current entity's transform data
        TransformComponent& transform = transformComponents[entity];
        glm::mat4 model = glm::mat4(1.0f);
	    model = glm::translate(model, transform.position);
        //  Last argument is the axis around which to rotate the model
	    model = glm::rotate(
            model, glm::radians(transform.eulers.z), 
            { 0.0f, 0.0f, 1.0f });
            
        //  Send the Uniform to GPU/Shaders
        glUniformMatrix4fv(
		    m_ModelLocation, 1, GL_FALSE, 
		    glm::value_ptr(model));
        
        glBindTexture(GL_TEXTURE_2D, m_Textures[renderable.objectType]);
        unsigned int vertexCount = m_VertexCounts[renderable.objectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone){
            frame = static_cast<size_t>(animationComponents[entity].frame);
        }
        glBindVertexArray(m_VAOs[renderable.objectType][renderable.animationType][frame]);
	    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
	glfwSwapBuffers(m_Window);
}