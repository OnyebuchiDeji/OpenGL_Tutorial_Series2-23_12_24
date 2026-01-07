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
    for (std::pair<unsigned int, RenderComponent> entity : renderComponents)
    {
        //  Getting the current entity's transform data
        TransformComponent& transform = transformComponents[entity.first];
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
        
        glBindTexture(GL_TEXTURE_2D, entity.second.material);
        glBindVertexArray(entity.second.mesh);
	    glDrawArrays(GL_TRIANGLES, 0, 36);
    }
	glfwSwapBuffers(m_Window);
}