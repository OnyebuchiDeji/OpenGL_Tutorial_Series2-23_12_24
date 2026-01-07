/**
 * @date: 08-01-2025
 * 
 *  Episode 13: "OpenGL with C++ 13: Compute Shaders"
 *  This shows the completed Raytrace Rendering using a compute shader
 * 	as well as fragment and vertex shaders.
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"

#include "factories/factory.h"

int main()
{
	App* app = new App();
	Factory* factory = new Factory(
		app->m_CameraComponents
	);

	factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
	);

	app->set_up_opengl();

	app->make_systems();

	app->run();

	delete app;

	return 0; 
}