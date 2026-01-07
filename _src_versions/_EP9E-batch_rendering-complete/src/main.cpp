/**
 * @date: 30-12-2024
 * 
 *  Episode 9: "OpenGL with C++ 9: Static Geometry"
 *  This shows the completed episode, as it includes the textures
 *  
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

#include "factories/factory.h"

int main()
{
	App* app = new App();
	Factory* factory = new Factory(
		app->m_PhysicsComponents,
		app->m_RenderComponents,
		app->m_TransformComponents,
		app->m_AnimationComponents
	);

	factory->make_cube(
		{3.0f, 0.0f, 0.25f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f}
	);
	factory->make_cube2(
		{2.0f, 0.0f, 0.15f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 15.0f}
	);

	// factory->make_girl_model({5.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 180.0f});

	factory->make_revy_model({3.0f, 2.0f, 0.25f}, {0.0f, 0.0f, 270.0f});

	unsigned int cameraEntity = factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
	);
	
	//	Now, make camera component
	CameraComponent* camera = new CameraComponent();
	//	And because there's only one Camera, no Vector store is used to store this Camera Entity's
	//	CameraComponent, just a normal member variable is used.
	app->m_CameraComponent = camera;
	//	Likewise store the CameraEntity's ID/
	app->m_CameraID = cameraEntity;
	
	//	Start OpenGL
	app->set_up_opengl();
	//	Make Systems
	app->make_systems();

	//	Run
	app->run();

	delete app;

	// std::cout << "Done!\n";
	return 0; 
}


void test_code()
{
	std::string line = "This is a line";
	std::cout << line << "\n";

	for (std::string word : ObjLoader::split(line, " "))
	{
		std::cout << word << '\n';

	}
}