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

public:
	Cube s;
	PhysBody3D* sensor;

	//For creation a car
	VehicleInfo car2;
	PhysVehicle3D* vehicle2;

	VehicleInfo car3;
	PhysVehicle3D* vehicle3;
};


/*
#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
ModuleSceneIntro(Application* app, bool start_enabled = true);
~ModuleSceneIntro();

bool Start();
update_status Update(float dt);
bool CleanUp();

void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
Cube s;
PhysBody3D* sensor;
};
*/

