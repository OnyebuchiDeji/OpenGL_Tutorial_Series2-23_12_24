/**
 * @date: 08-01-2025
 * 
 *  Episode 13: "OpenGL with C++ 12: Post Processing"
 *  This shows the concpet of 'Post Processing', in which
 * 	everything that needs to be rendered is not rendered immediately
 * 	but is 'rendered' in memory so that post-rendering processes
 * 	like manipulating the color can be done on that scene
 * 	before it is finally rendered. 
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"

#include "factories/factory.h"

int main()
{
	App* app = new App();
	Factory* factory = new Factory(
		app->m_PhysicsComponents,
		app->m_RenderComponents,
		app->m_TransformComponents,
		app->m_AnimationComponents,
		app->m_CameraComponents
	);

	factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
	);
	
	factory->make_cube(
		{3.0f, 0.0f, 0.25f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f}
	);

	factory->destroy_camera(0);

	
	factory->make_revy_model(
		{4.0f, 2.0f, 0.25f},
		{0.0f, 0.0f, 270.0f});


	factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
	);

	app->set_up_opengl();

	app->make_systems();

	app->run();

	delete app;

	return 0; 
}