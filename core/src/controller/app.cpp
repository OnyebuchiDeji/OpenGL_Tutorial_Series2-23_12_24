#include "app.h"
#include "../factories/model_factory.h"
#include "../backend/shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

App::App() {

	set_up_glfw();
	set_up_opengl();

	make_objects();
	make_systems();

}

App::~App() {

	glDeleteProgram(m_Shader);

    delete m_RenderSystem;
	delete m_InputSystem;
	delete m_World;
	delete m_CameraSystem;
    
    glfwTerminate();
}

void App::make_objects() {

	m_ComponentRegistry.renderables.m_Entities.reserve(maxObjectCount);
	m_ComponentRegistry.renderables.m_Components.reserve(maxObjectCount);
	m_ComponentRegistry.transforms.m_Entities.reserve(maxObjectCount);
	m_ComponentRegistry.transforms.m_Components.reserve(maxObjectCount);
	m_ComponentRegistry.velocities.m_Entities.reserve(maxObjectCount);
	m_ComponentRegistry.velocities.m_Components.reserve(maxObjectCount);

	m_Factory = new Factory(m_ComponentRegistry, m_Shader);

	for (size_t i = 0; i < maxObjectCount; ++i) {
		m_Factory->make_object();
	}
}

void App::run() {

	m_LastTime = glfwGetTime();
	m_LastFrameTime = glfwGetTime();
	m_NumFrames = 0;
	m_FrameTime = 0.0f;

    while (!glfwWindowShouldClose(m_Window)) {

		//Input
		if (m_InputSystem->m_Keys.contains(GLFW_KEY_ESCAPE) 
			&& m_InputSystem->m_Keys[GLFW_KEY_ESCAPE]) {
			break;
		}
		handle_controls();
		glfwPollEvents();

		//Objects
		m_CameraSystem->update();
		m_World->update(m_FrameTime);

		//Rendering, Animation etc
		m_RenderSystem->update();

		//End of frame housekeeping
		handle_frame_timing();
	}
}

void App::set_up_glfw() {

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	
	m_Window = glfwCreateWindow(static_cast<int>(windowWidth), static_cast<int>(windowHeight), m_WinName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(0);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

}

void App::set_up_opengl() {

	//Set the rendering region to the actual screen size
	int w,h;
	glfwGetFramebufferSize(m_Window, &w, &h);

	//(left, top, width, height)
	glViewport(0,0,w,h);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	m_Shader = make_shader_program(
		"../core/src/shaders/vertex.txt", 
		"../core/src/shaders/fragment.txt");
	glUseProgram(m_Shader);
}

void App::make_systems() {
	m_CameraSystem = new CameraSystem(m_Shader);
	m_World = new World(m_ComponentRegistry);
    m_RenderSystem = new RenderSystem(m_Shader, m_Window, m_ComponentRegistry);
	m_InputSystem = new InputSystem(m_Window);
}

void App::handle_frame_timing() {
	m_CurrentTime = glfwGetTime();
	double delta = m_CurrentTime - m_LastTime;
	double frameDelta = m_CurrentTime - m_LastFrameTime;
	m_FrameTime = float(1000.0f * frameDelta);
	m_LastFrameTime = m_CurrentTime;

	if (delta >= 1) {
		int framerate{ std::max(1, int(m_NumFrames / delta)) };
		std::stringstream title;
		title << "Running at " << framerate << " fps.";
		glfwSetWindowTitle(m_Window, (m_WinName + title.str()).c_str());
		m_LastTime = m_CurrentTime;
		m_NumFrames = -1;
	}

	++m_NumFrames;
}

void App::handle_controls() {

	std::unordered_map<int, bool>& keys = m_InputSystem->m_Keys;

	glm::vec3 dPos = glm::vec3(0.0f);
	glm::vec3 dEulers = glm::vec3(0.0f);
	
	if (keys.contains(GLFW_KEY_W) && keys[GLFW_KEY_W]) {
		dPos.x += 1.0f;
	}
	if (keys.contains(GLFW_KEY_A) && keys[GLFW_KEY_A]) {
		dPos.y -= 1.0f;
	}
	if (keys.contains(GLFW_KEY_S) && keys[GLFW_KEY_S]) {
		dPos.x -= 1.0f;
	}
	if (keys.contains(GLFW_KEY_D) && keys[GLFW_KEY_D]) {
		dPos.y += 1.0f;
	}

	if (glm::length(dPos) > 0.01f) {
		m_CameraSystem->move(m_FrameTime / 1000.0f * glm::normalize(dPos));
	}

	double mouse_x, mouse_y;
	glfwGetCursorPos(m_Window, &mouse_x, &mouse_y);
	glfwSetCursorPos(m_Window, static_cast<double>(windowWidth / 2), static_cast<double>(windowHeight / 2));
	glfwPollEvents();

	dEulers.z = -0.05f * static_cast<float>(mouse_x - static_cast<double>(windowWidth / 2));
	dEulers.y = -0.05f * static_cast<float>(mouse_y - static_cast<double>(windowHeight / 2));

	m_CameraSystem->spin(dEulers);
}