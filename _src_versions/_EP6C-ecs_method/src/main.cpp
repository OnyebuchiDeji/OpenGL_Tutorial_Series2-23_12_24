/**
 * @date: 29-12-2024
 * 
 *  Episode 6: "openGL with C++ 6: Design Patterns"
 *  This _EP6B demonstrates the third strucutre, the use of Entity Component System
 *  
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

int main() {

	App* app = new App();

	//	Get ID for cube entity
	unsigned int cubeEntity = app->make_entity();
	TransformComponent transform;	//	Create Transform Component object
	//	Modify for Cube
	transform.position = {3.0f, 0.0f, 0.25f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	//	Register this custom TransformComponent for the Cube in the App's Vector store
	app->m_TransformComponents[cubeEntity] = transform;

	PhysicsComponent physics;		//	Create Physics Component
	//	Customize this component for the Cube
	physics.velocity = {0.0f, 0.0f, 0.0f};
	physics.eulerVelocity = {0.0f, 0.0f, 10.0f};
	//	Register this custom PhysicsComponent for the Cube likewise
	app->m_PhysicsComponents[cubeEntity] = physics;
	
	RenderComponent render;			//	Create RenderComponent
	//	Customize the values of this component for the Cube Entity
	render.mesh = app->make_cube_mesh({0.25f, 0.25f, 0.25f});
	render.material = app->make_texture("../core/_resources/img/spider_3d_image1a.jpg");
	//	Register it in the App's Vector store as belonging to the Cube using the Cube Entity's ID, like afore-done
	app->m_RenderComponents[cubeEntity] = render;

	//	Create CameraEntity; starts with getting a new ID that represents this Entity
	unsigned int cameraEntity = app->make_entity();
	//	Customize the TransformComponent for the Camera Entity 
	transform.position = {0.0f, 0.0f, 1.0f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	//	Register this custom TransformComponent as belonging to the camera...
	//	in the App's vector store	for TransformComponents
	app->m_TransformComponents[cameraEntity] = transform;

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
	return 0;
}