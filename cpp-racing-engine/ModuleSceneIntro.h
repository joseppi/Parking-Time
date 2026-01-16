#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

#define MAX_SNAKE 2
#define MAX_ROUNDS 500

struct PhysBody3D;
struct PhysMotor3D;
struct VehicleInfo;
class vec3;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CameraCalc(); //Calculates the position of the camera based on the player's position

public:
	Cube s_win;
	PhysBody3D* sensor_win;

	Cube s_delete;
	PhysBody3D* sensor_delete;

	Cube s_delete2;
	PhysBody3D* sensor_delete2;

	Cube s_lose;
	PhysBody3D* sensor_lose;

	Cube c,c1,c2,c3,c4,c5;

	vec3 relative;

	PhysVehicle3D* vehicle;

	Timer spawn_rate;

	p2List<Sphere> spheres;
	p2List<PhysBody3D*> pspheres;
	p2List<btRigidBody*> deleted_rigidbody;

	Sphere sphere[MAX_ROUNDS];
	int i = 0;
	bool end_game = false;
	
};


