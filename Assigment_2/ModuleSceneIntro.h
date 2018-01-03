#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

#define MAX_SNAKE 2

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
	void CreateCar(int x, int y, int z);
	void CameraCalc(); //Calculates the position of the camera based on the player's position

public:
	Cube s_win;
	PhysBody3D* sensor_win;

	Cube s_lose;
	PhysBody3D* sensor_lose;

	Cube c,c1,c2,c3,c4,c5;

	vec3 relative;


	
};


