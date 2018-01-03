
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "Timer.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	

	
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//creating sensor win
	s_win.size = vec3(1, 1, 1);
	s_win.SetPos(0, 8, 75);
	
	sensor_win = App->physics3D->AddBody(s_win, 0.0f);
	sensor_win->SetAsSensor(true);
	sensor_win->collision_listeners.add(this);

	//creating sensor lose

	s_lose.size = vec3(1, 1, 1);
	s_lose.SetPos(0, 2, 75);

	sensor_lose = App->physics3D->AddBody(s_lose, 0.0f);
	sensor_lose->SetAsSensor(true);
	sensor_lose->collision_listeners.add(this);

	//creating cars in the scene
	//n
	//App->scene_intro->CreateCar(-15, 6, 75);
	//App->scene_intro->CreateCar(-12, 6, 75);
	//App->scene_intro->CreateCar(-9, 6, 75);
	//App->scene_intro->CreateCar(-6, 6, 75);
	//App->scene_intro->CreateCar(-3, 6, 75);
	////App->scene_intro->CreateCar(0, 6, 75);
	//App->scene_intro->CreateCar(3, 6, 75);
	//App->scene_intro->CreateCar(6, 6, 75);
	//App->scene_intro->CreateCar(9, 6, 75);
	//App->scene_intro->CreateCar(12, 6, 75);
	//App->scene_intro->CreateCar(15, 6, 75);
	//App->scene_intro->CreateCar(0, 6, 40);

	{
		////s
		//App->scene_intro->CreateCar(-12, 6, 43);
		//App->scene_intro->CreateCar(-15, 6, 43);
		//App->scene_intro->CreateCar(-9,  6, 43);
		//App->scene_intro->CreateCar(-6,  6, 43);

		//App->scene_intro->CreateCar(6,   6, 43);
		//App->scene_intro->CreateCar(9,   6, 43);
		//App->scene_intro->CreateCar(12,  6, 43);
		//App->scene_intro->CreateCar(15,  6, 43);

		////e
		//App->scene_intro->CreateCar(15, 6, 47, true);
		//App->scene_intro->CreateCar(15, 6, 50, true);
		//App->scene_intro->CreateCar(15, 6, 53, true);
		//App->scene_intro->CreateCar(15, 6, 56, true);
		//App->scene_intro->CreateCar(15, 6, 59, true);
		//App->scene_intro->CreateCar(15, 6, 62, true);
		//App->scene_intro->CreateCar(15, 6, 65, true);
		//App->scene_intro->CreateCar(15, 6, 68, true);
	}
	

	{
		//create a plane
		c.size = vec3(10, 1, 20);

		//create ramp
		c1.size = vec3(20, 1, 500);
		c1.SetPos(0, 80, 100);

		vec3 x_rotation(1, 0, 0); //Pitch
		vec3 y_rotation(0, 1, 0); //Yaw
		vec3 z_rotation(0, 0, 1);  //Roll

		c1.SetRotation(20, -x_rotation);
		App->physics3D->AddBody(c1, 0)->collision_listeners.add(this);

		////Create first floor
		//c2.size = vec3(40, 1, 40);
		//c2.SetPos(0, 5.4f, 59.2);

		//App->physics3D->AddBody(c2, 0)->collision_listeners.add(this);
	}
	


	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	btVector3 player_position_origin = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin();
	//App->camera->LookAt(vec3(player_position_origin.getX(), player_position_origin.getY(), player_position_origin.getZ()));


	if (spawn_rate.Read() >= 5000.0f)
	{
		App->scene_intro->CreateCar(-8, 160, 320);
		App->scene_intro->CreateCar(-4, 160, 320);
		App->scene_intro->CreateCar(0, 160, 320);
		App->scene_intro->CreateCar(4, 160, 320);
		App->scene_intro->CreateCar(8, 160, 320);
		spawn_rate.Start();
	}
	

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor_win->GetTransform(&s_win.transform);
	s_win.Render();

	c1.Render();
	c2.Render();



	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit! %f", App->player->vehicle->GetKmh());
	if (body1 == sensor_win)
	{
		if (body2 == App->player->vehicle && App->player->vehicle->GetKmh() < 1)
		{
			btVector3 player_position = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin();
			App->player->vehicle->SetPos(0, 0, 0);
			App->scene_intro->CreateCar(player_position.getX(), player_position.getY() + 1, player_position.getZ());
		}
	}
	if (body1 == sensor_lose)
	{
		
	}

	

}

void ModuleSceneIntro::CreateCar(int x, int y, int z, bool rotate)
{
	VehicleInfo car; 
	//CAR CREATION

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 100.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 2000.0f;
	

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = false;
	car.wheels[0].drive = false;
	car.wheels[0].brake = false;
	car.wheels[0].steering = false;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = false;
	car.wheels[1].drive = false;
	car.wheels[1].brake = false;
	car.wheels[1].steering = false;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = false;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = false;
	car.wheels[3].steering = false;

	vehicle = App->physics3D->AddVehicle(car);
	vehicle->SetPos(x, y, z);
	//float rotation = 0.0f;
	//if (rotate == true)
	//{
	//	 rotation = 5.0f;
	//}
	//else
	//	rotation = 1.0f;
	//mat4x4 RotationMatrix = mat4x4
	//	(1.0f, 1.0f, rotation, 1.0f, 
	//	1.0f, 1.0f, 1.0f, 1.0f, 
	//	1.0f, 1.0f, 1.0f, 1.0f, 
	//	(float)x, (float)y, (float)z, 1.0f);

	//AI_vehicle->SetTransform(&RotationMatrix);

	//Create argument for rotating the cars
	/*
	const float* matrix; //matrix = rotation matrix;
	vehicle->SetTransform(matrix);
	*/


}

void ModuleSceneIntro::CameraCalc()
{
	//Direction of the car
	App->player->vehicle->vehicle->getRigidBody()->getLinearVelocity();

	btVector3 player_position = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin();
	App->camera->LookAt(vec3(player_position.getX(), player_position.getY()+5, player_position.getZ()));

	relative.x = 0;
	relative.y = -5;
	relative.z = 15;

	App->camera->Position.x = player_position.getX() - relative.x;
	App->camera->Position.y = player_position.getY() - relative.y;
	App->camera->Position.z = player_position.getZ() - relative.z;
}



