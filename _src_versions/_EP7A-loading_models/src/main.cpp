/**
 * @date: 29-12-2024
 * 
 *  Episode 7: "openGL with C++ 7: Loading Models"
 *  This _EP7A demonstrates the continuation fo the ECS method from Episode 6, but removes a lot
 * 	functionality previously defined in the main function and defiens it int he Factory class. 
 *  Also, simple lighting effects are added.
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

#include "factories/factory.h"

int main() {

	App* app = new App();
	Factory* factory = new Factory(
		app->m_PhysicsComponents,
		app->m_RenderComponents,
		app->m_TransformComponents
	);

	factory->make_cube(
		{3.0f, 0.0f, 0.25f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f}
	);

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

	delete factory;
	delete app;
	return 0;
}