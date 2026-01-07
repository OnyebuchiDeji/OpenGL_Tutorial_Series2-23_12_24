#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

CameraSystem::CameraSystem(uint32_t shader)
{
    this->m_Shader = shader;
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Eulers = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Forward = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Right = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Up = glm::vec3(0.0f, 0.0f, 0.0f);

	constexpr float fovY = glm::radians(22.5f);
	float aspect = windowWidth / windowHeight;
	float near = 0.1f;
	float far = 200.0f;
	
	m_Projection = glm::perspective(fovY, aspect, near, far);
	/*
	std::cout << "----" << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << projection[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	*/
	m_ViewProjLocation = glGetUniformLocation(shader, "u_View");

	//std::cout << "\Eye: <" << position.x << ", " << position.y << ", " << position.z << ">" << std::endl;
}

void CameraSystem::update()
{
    m_Forward = {
        glm::cos(glm::radians(m_Eulers.z)) * glm::cos(glm::radians(m_Eulers.y)),
        glm::sin(glm::radians(m_Eulers.z)) * glm::cos(glm::radians(m_Eulers.y)),
        glm::sin(glm::radians(m_Eulers.y))
    };
    m_Right = glm::normalize(glm::cross(m_Forward,  glm::vec3(0.0f, 0.0f, 1.0f)));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
    glm::mat4 viewProj = m_Projection * glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

    /*
	std::cout << "---- Camera Data ----" << std::endl;

	std::cout << "\tForwards: <" << forwards.x << ", " << forwards.y << ", " << forwards.z << ">" << std::endl;
	std::cout << "\tRight: <" << right.x << ", " << right.y << ", " << right.z << ">" << std::endl;
	std::cout << "\tUp: <" << up.x << ", " << up.y << ", " << up.z << ">" << std::endl;

	std::cout << "\Eye: <" << position.x << ", " << position.y << ", " << position.z << ">" << std::endl;
	std::cout << "\tCenter: <" << (position + forwards).x << ", " << (position + forwards).y << ", " << (position + forwards).z << ">" << std::endl;
	std::cout << "\tUp: <" << up.x << ", " << up.y << ", " << up.z << ">" << std::endl;

	std::cout << "Resulting view matrix:" << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << view[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	*/

	glUniformMatrix4fv(m_ViewProjLocation, 1, GL_FALSE, glm::value_ptr(viewProj));
}

void CameraSystem::move(glm::vec3 dPos){
	m_Position += m_Forward * dPos.x;
	m_Position += m_Right * dPos.y;
	m_Position += m_Up * dPos.z;
	//std::cout << "\Eye: <" << position.x << ", " << position.y << ", " << position.z << ">" << std::endl;
}

void CameraSystem::spin(glm::vec3 dEulers){
	m_Eulers.z += dEulers.z;
	if (m_Eulers.z > 360.0f){
		m_Eulers.z -= 360.0f;
	}
	if (m_Eulers.z < 0.0f){
		m_Eulers.z += 360.0f;
	}

	m_Eulers.y = std::min(89.0f, std::max(-89.0f, m_Eulers.y + dEulers.y));
}