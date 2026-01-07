#include "render_system.h"
#include "../factories/mesh_factory.h"
#include "../factories/texture_factory.h"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {
    
    m_ModelLocation = glGetUniformLocation(shader, "u_Model");
    this->m_Window = window;

    m_Textures.resize(2);

    build_models();
    build_geometry();
}

RenderSystem::~RenderSystem()
{
    for (auto& [objectType, animations] : m_VAOs)
    {
        for (auto& [animation, VAO] : animations){
            glDeleteVertexArrays(1, &VAO);
        } 
    }
    for (auto& [objectType, animations] : m_VBOs)
    {
        for (auto& [animation, VBO] : animations)
        {
            glDeleteBuffers(1, &VBO);
        }
    }
    /* for (auto& [objectType, texture] : m_Textures){
        glDeleteTextures(1, &texture);
    } */
   //   Because there are just two textures:
   glDeleteTextures(m_Textures.size(), m_Textures.data());
}

void RenderSystem::build_models()
{
    
    MeshFactory meshFactory;
    TextureFactory textureFactory;


    ObjectType objectType = ObjectType::eBox;
    AnimationType animationType = AnimationType::eNone;

    meshFactory.start_obj_mesh();
    meshFactory.append_cube_mesh({0.25f, 0.25f, 0.25f}, 0);
    StaticMesh mesh = meshFactory.build_obj_mesh();
    m_VAOs[objectType][animationType] = mesh.VAO;
    m_VBOs[objectType][animationType] = mesh.VBO;
    m_VertexCounts[objectType] = mesh.vertexCount;

    objectType = ObjectType::eBox2;
    meshFactory.start_obj_mesh();
    meshFactory.append_cube_mesh({0.25f, 0.25f, 0.25f}, 1);
    mesh = meshFactory.build_obj_mesh();
    m_VAOs[objectType][animationType] = mesh.VAO;
    m_VBOs[objectType][animationType] = mesh.VBO;
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
    meshFactory.start_obj_mesh();
    
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform,{0.0f, 0.0f, -0.25f});
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
        meshFactory.append_obj_mesh(built_filepath.c_str(), preTransform, 2);
    }
    mesh = meshFactory.build_obj_mesh();
    m_VAOs[objectType][animationType] = mesh.VAO;
    m_VBOs[objectType][animationType] = mesh.VBO;
    /**
     *  Dividing by 19 based on the assumption that every animation frame .obj object has the same number of points.
     *  so the mesh stores the vertexCount for the 19 vertices.
     *  But since each *should* have the same number of vertices, and only one is to be rendered
     *  at a time, the below divides by 19.
     */
    m_VertexCounts[objectType] = mesh.vertexCount / 19;

    textureFactory.start_texture_array(3);
    textureFactory.load_into_array("../_resources/img/paper.jpg", 0);
    textureFactory.load_into_array("../_resources/img/spider_3d_image1a.jpg", 1);
    textureFactory.load_into_array("../_resources/img/Revy_Final.png", 2);
    m_Textures[1] = textureFactory.finalize_texture_array();
}
    

void RenderSystem::build_geometry()
{
    MeshFactory meshFactory;
    TextureFactory textureFactory;

    ObjectType objectType = ObjectType::eGeometry;
    AnimationType animationType = AnimationType::eNone;
    meshFactory.start_obj_mesh();

    //  Ground
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::scale(preTransform, {2.0f, 2.0f, 1.0f});
    meshFactory.append_obj_mesh("../_resources/models/ground.obj", preTransform, 0);
    //  West wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, 0.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/wall.obj", preTransform, 1);
    //  East wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, 0.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/wall.obj", preTransform, 1);
    //  North wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {0.0f, 10.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 0.0f, 1.0f});
    meshFactory.append_obj_mesh("../_resources/models/wall.obj", preTransform, 1);
    //  South wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {0.0f, -10.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 0.0f, 1.0f});
    meshFactory.append_obj_mesh("../_resources/models/wall.obj", preTransform, 1);
    //  Northwest Corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, 10.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/corner.obj", preTransform, 2);
    //  Southwest Corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, -10.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/corner.obj", preTransform, 2);
    //  Southeast Corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, -10.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/corner.obj", preTransform, 2);
    //  Northeast Corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, 10.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/corner.obj", preTransform, 2);
    //  A Tree
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {3.0f, -2.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/tree.obj", preTransform, 3);
    //  Another Tree
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-2.0f, 1.0f, 0.0f});
    meshFactory.append_obj_mesh("../_resources/models/tree.obj", preTransform, 3);

    StaticMesh mesh = meshFactory.build_obj_mesh();
    m_VAOs[objectType][animationType] = mesh.VAO;
    m_VBOs[objectType][animationType] = mesh.VBO;
    //  Note this one does not divide by anything, because all are to be rendered
    m_VertexCounts[objectType] = mesh.vertexCount;

    //  Start a Texture array with 4 layers
    textureFactory.start_texture_array(4);
    //  Load in the things you need.
    textureFactory.load_into_array("../_resources/img/GrassAndDirt_S.jpg", 0);
    textureFactory.load_into_array("../_resources/img/brick.jpeg", 1);
    textureFactory.load_into_array("../_resources/img/red_brick.jpg", 2);
    textureFactory.load_into_array("../_resources/img/Tree_Texture.png", 3);
    //  Then finish setting u[]
    m_Textures[0] = textureFactory.finalize_texture_array(); 

}


void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent>& transformComponents,
    std::unordered_map<unsigned int,RenderComponent>& renderComponents,
    std::unordered_map<unsigned int,AnimationComponent>& animationComponents
    ) {
    
    //  Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Hard Code Static Geometry Draw Call
    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
    //  Bind the Static Geometry's textures
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Textures[0]);
    glBindVertexArray(m_VAOs[ObjectType::eGeometry][AnimationType::eNone]);
    glDrawArrays(GL_TRIANGLES, 0, m_VertexCounts[ObjectType::eGeometry]);
    

    //  Now bind the texture of everything else
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Textures[1]);
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
        
        // glBindTexture(GL_TEXTURE_2D, m_Textures[renderable.objectType]); <-- no more needed
        unsigned int vertexCount = m_VertexCounts[renderable.objectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone){
            frame = static_cast<size_t>(animationComponents[entity].frame);
        }
        //  Note how this is no more: glBindVertexArray(m_VAOs[renderable.objectType][renderable.animationType][frame]);
        glBindVertexArray(m_VAOs[renderable.objectType][renderable.animationType]);
        //  Now, the second argument is the offset at the different frame's buffer data start. 
	    glDrawArrays(GL_TRIANGLES, frame * vertexCount, vertexCount);
    }
	glfwSwapBuffers(m_Window);
}