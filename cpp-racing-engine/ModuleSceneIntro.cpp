
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
	s_win.SetPos(0, 182, 380);
	
	sensor_win = App->physics3D->AddBody(s_win, 0.0f);
	sensor_win->SetAsSensor(true);
	sensor_win->collision_listeners.add(this);
	
	//creating sensor delete
	s_delete.size = vec3(1000, 1, 1000);
	s_delete.SetPos(0, 4, 0);

	sensor_delete = App->physics3D->AddBody(s_delete, 0.0f);
	sensor_delete->SetAsSensor(true);
	sensor_delete->collision_listeners.add(this);

	s_delete2.size = vec3(20, 20, 2);
	s_delete2.SetPos(0, 10, -110);

	sensor_delete2 = App->physics3D->AddBody(s_delete2, 0.0f);
	sensor_delete2->SetAsSensor(true);
	sensor_delete2->collision_listeners.add(this);


	//creating sensor lose
	s_lose.size = vec3(1000, 1, 1000);
	s_lose.SetPos(0, 1, 0);

	sensor_lose = App->physics3D->AddBody(s_lose, 0.0f);
	sensor_lose->SetAsSensor(true);
	sensor_lose->collision_listeners.add(this);

	//floors
	{
	//create ramp
	c1.size = vec3(20, 1, 500);
	c1.SetPos(0, 95, 120);

	vec3 x_rotation(1, 0, 0); //Pitch
	vec3 y_rotation(0, 1, 0); //Yaw
	vec3 z_rotation(0, 0, 1);  //Roll

	c1.SetRotation(20, -x_rotation);
	App->physics3D->AddBody(c1, 0)->collision_listeners.add(this);

	//Create Spawn floor
	c2.size = vec3(20, 1, 50);
	c2.SetPos(0, 10, -130);
	App->physics3D->AddBody(c2, 0)->collision_listeners.add(this);

	c3.size = vec3(20, 1, 40);
	c3.SetPos(0, 180.5f, 375);
	App->physics3D->AddBody(c3, 0)->collision_listeners.add(this);
	}

	//Spheres
	{
		for (int i = 0; i < MAX_ROUNDS; i++)
		{
			sphere[i].SetPos(0, 180, 320);
			sphere[i].radius = NULL;
			sphere[i].dead = false;
			spheres.add(sphere[i]);
		}
	}

	spawn_rate.Start();

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


	if (spawn_rate.Read() >= 1000.0f)
	{
		//adding spheres to list
		i++;
		int position_x = rand() % 20 - 9;
		sphere[i].radius = 2;
		sphere[i].SetPos(position_x, 180, 320);
		pspheres.add(App->physics3D->AddBody(sphere[i], 1000.0f));

		spawn_rate.Start();
	}

	//render spheres
	for (int i = 1; i < MAX_ROUNDS; i++)
	{
		if (sphere[i].dead == false)
		{
			sphere[i].Render();
		}
	}

	//adding images to sphear physics
	if (pspheres.getFirst())
	{
		p2List_item<PhysBody3D*>* item = pspheres.getFirst();
		for (int y = 1; item != NULL; y++)
		{
			float matrix[16];
			item->data->GetTransform(matrix);
			vec3 position(matrix[12], matrix[13], matrix[14]);
			if (position.y >= 15)
			{
				sphere[y].SetPos(position.x, position.y, position.z);
			}
			else
			{
				sphere[y].dead = true;	
			}

			item = item->next;
		}

	}

	p2List_item<btRigidBody*>* item = deleted_rigidbody.getFirst();
	while (item != NULL)
	{
		App->physics3D->world->removeRigidBody(item->data);
		item = item->next;
	}
	
	//render sensors
	sensor_win->GetTransform(&s_win.transform);
	s_win.Render();

	//render floors
	c1.Render();
	c2.Render();
	c3.Render();

	if(end_game == true)
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sensor_win)
	{
		if (body2 == App->player->vehicle)
		{
			end_game = true;
		}
	}
	if (body1 == sensor_lose)
	{
		LOG("Player_Vehicle");
		mat4x4 matrix = mat4x4
		(1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 10.0f, -145.0f, 0.0f);

		App->player->vehicle->SetTransform(&matrix);
	}
	if (body1 == sensor_delete2 || body1 == sensor_delete)
	{
		if (body2 != App->player->vehicle)
		{
			LOG("AI_Vehicle");
			deleted_rigidbody.add(body2->GetRigidBody());
		}
	}
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



