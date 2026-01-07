#include "render_system.h"
#include "../factories/mesh_factory.h"
#include "../factories/texture_factory.h"

RenderSystem::RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
        ComponentSet<TransformComponent>& transforms,
        ComponentSet<RenderComponent>& renderables,
        ComponentSet<AnimationComponent>& animations):
    m_Shaders(shaders), m_Transforms(transforms), m_Renderables(renderables),
    m_Animations(animations)
{
    
    this->m_Window = window;

    m_Textures.resize(2);
    m_VAOs.resize(2);
    m_VBOs.resize(2);
    m_EBOs.resize(2);
    build_sky();
    build_models();
    build_geometry();

    glUseProgram(m_Shaders[0]);
    glUniform1i(glGetUniformLocation(m_Shaders[0], "u_Sky"), 1);
    glUseProgram(m_Shaders[1]);
    glUniform1i(glGetUniformLocation(m_Shaders[1], "u_Materials"), 0);
    glUniform1i(glGetUniformLocation(m_Shaders[1], "u_Sky"), 1);
    glUseProgram(m_Shaders[2]);
    glUniform1i(glGetUniformLocation(m_Shaders[2], "u_Materials"), 0);
    glUniform1i(glGetUniformLocation(m_Shaders[2], "u_Sky"), 1);
    m_ModelLocation = glGetUniformLocation(m_Shaders[2], "u_Model");
}

RenderSystem::~RenderSystem()
{
    glDeleteVertexArrays(m_VAOs.size(), m_VAOs.data());

    glDeleteBuffers(m_VBOs.size(), m_VBOs.data());

    glDeleteBuffers(m_EBOs.size(), m_EBOs.data());

    glDeleteTextures(m_Textures.size(), m_Textures.data());
    glDeleteTextures(1, &m_SkyTexture);
}


void RenderSystem::build_sky()
{
    TextureFactory textureFactory;
    m_SkyTexture = textureFactory.build_cubemap({
        "../_resources/img/sky_front.png",  //  x+
        "../_resources/img/sky_back.png",   //  x-
        "../_resources/img/sky_left.png",   //  y+
        "../_resources/img/sky_right.png",  //  y-
        "../_resources/img/sky_top.png",    //  z+
        "../_resources/img/sky_bottom.png"  //  z-
    });
}

void RenderSystem::build_models()
{
    
    ObjectType objectType = ObjectType::eBox;
    AnimationType animationType = AnimationType::eNone;
    MeshFactory meshFactory;
    TextureFactory textureFactory;


    meshFactory.start_obj_mesh();
    m_Offsets[objectType][animationType] = meshFactory.m_Offset;
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::scale(preTransform, {0.25f, 0.25f, 0.25f});
    meshFactory.append_obj_mesh("../_resources/models/cube.obj", preTransform, 0);
    m_ElementsCount[objectType] = meshFactory.m_ElementCount;
    meshFactory.m_ElementCount = 0;

    objectType = ObjectType::eRevy;
    animationType = AnimationType::eRun;
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform,{0.0f, 0.0f, -0.25f});
    preTransform = glm::rotate(preTransform,
        glm::radians(-90.0f), { 0.0f, 0.0f, 1.0f });

    std::stringstream filepath;
    std::string built_filepath;
    m_Offsets[objectType][animationType] = meshFactory.m_Offset;
    //  Building file paths of .obj files to read from 
    for (size_t i = 0; i < 19; ++i){
        filepath.str("");
        filepath << "../_resources/models/Revy_run_0000";
        if (i <= 9){
            filepath << "0";
        }
        filepath << i << ".obj";
        built_filepath = filepath.str();
        meshFactory.append_obj_mesh(built_filepath.c_str(), preTransform, 1);
        if (i == 0){
            m_ElementsCount[objectType] = meshFactory.m_ElementCount;
            meshFactory.m_ElementCount = 0;
        }
    }
    StaticMesh mesh = meshFactory.build_obj_mesh();
    m_VAOs[1] = mesh.VAO;
    m_VBOs[1] = mesh.VBO;
    m_EBOs[1] = mesh.EBO;

    textureFactory.start_texture_array(2);
    textureFactory.load_into_array("../_resources/img/spider_3d_image1a.jpg", 0);
    textureFactory.load_into_array("../_resources/img/Revy_Final.png", 1);
    m_Textures[1] = textureFactory.finalize_texture_array();
}
    

void RenderSystem::build_geometry()
{
    ObjectType objectType = ObjectType::eGeometry;
    MeshFactory meshFactory;
    TextureFactory textureFactory;

    // AnimationType animationType = AnimationType::eNone;
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
    m_ElementsCount[objectType] = meshFactory.m_ElementCount;

    StaticMesh mesh = meshFactory.build_obj_mesh();
    m_VAOs[0] = mesh.VAO;
    m_VBOs[0] = mesh.VBO;
    //  Note this one does not divide by anything, because all are to be rendered
    m_EBOs[0] = mesh.EBO;

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


void RenderSystem::update() {
    //  Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Sky
    glUseProgram(m_Shaders[0]);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);


    glUseProgram(m_Shaders[1]);
    //  Bind the Static Geometry's textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Textures[0]);
    glBindVertexArray(m_VAOs[0]);
    glDrawElements(GL_TRIANGLES, m_ElementsCount[ObjectType::eGeometry],
        GL_UNSIGNED_INT, 0);

    //  Everything Else
    glUseProgram(m_Shaders[2]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Textures[1]);
    glBindVertexArray(m_VAOs[1]);
    for (size_t i = 0; i < m_Renderables.m_Entities.size(); ++i)
    {
        uint32_t entity = m_Renderables.m_Entities[i];
        RenderComponent& renderable = m_Renderables.m_Components[i];
        //  Getting the current entity's transform data
        TransformComponent& transform = m_Transforms.get_component(entity);
        
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
        
        unsigned int elementCount = m_ElementsCount[renderable.objectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone){
            AnimationComponent& animation = 
                m_Animations.get_component(entity);
            frame = static_cast<size_t>(animation.frame);
        }
        unsigned int offset =
            sizeof(unsigned int) * (
                m_Offsets[renderable.objectType][renderable.animationType]
                + frame * elementCount
            );
        //  Now, the second argument is the offset at the different frame's buffer data start. 
	    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)(offset));
    }
	glfwSwapBuffers(m_Window);
}