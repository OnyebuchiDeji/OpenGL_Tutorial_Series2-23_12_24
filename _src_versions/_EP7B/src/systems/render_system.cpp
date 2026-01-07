#include "render_system.h"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {
    
    m_ModelLocation = glGetUniformLocation(shader, "u_Model");
    this->m_Window = window;
}
    
void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent>& transformComponents,
    std::unordered_map<unsigned int,RenderComponent>& renderComponents) {
    
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
        
        glBindTexture(GL_TEXTURE_2D, renderable.material);
        glBindVertexArray(renderable.VAO);
	    glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount);
    }
	glfwSwapBuffers(m_Window);
}