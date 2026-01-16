//#include "Globals.h"
//#include "Application.h"
//#include "ModuleSceneIntro.h"
//#include "Primitive.h"
//#include "PhysBody3D.h"
//
////
//// CODE EXAMPLE: HOW TO COMPRESS CODE TO AVOID REPETITION
////
//
//#define SIZE_ARRAY(_A_) (sizeof(_A_)/sizeof(_A_[0]))
//// Road dimensions
//static const float R_W = 15.0f;
//static const float R_H = 5.0f;
//// Circuit positions
//static const float C_X = 150.0f;
//static const float C_Y = 80.0f;
//// Circuit definition
//struct CubeDef {
//	float size_x, size_y, size_z;
//	float pos_x, pos_y, pos_z;
//	bool  add_collision_listener;
//};
//CubeDef cube_defs[] = {
//	{ R_W      , R_H, C_X ,   0     , R_H / 2,  C_X / 2      , true },
//	{ C_Y + R_W, R_H, R_W,   -C_Y / 2 , R_H / 2,  C_X + R_W / 2, false },
//	{ R_W      , R_H, C_X ,  -C_Y   , R_H / 2,  C_X / 2      , false },
//	{ C_Y + R_W, R_H, R_W,   -C_Y / 2 , R_H / 2, -R_W / 2      , false },
//};
//
//
//ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
//{
//	graphics = NULL;
//}
//ModuleSceneIntro::~ModuleSceneIntro()
//{}
//// Load assets
//bool ModuleSceneIntro::Start()
//{
//	LOG("Loading Intro assets");
//	bool ret = true;
//
//	App->physics3D->AddBody(Plane(0, 1, 0, 0))->collision_listeners.add(this);
//	for (int i = 0; i < SIZE_ARRAY(cube_defs); i++)
//	{
//		Cube c;
//		c.size.Set(cube_defs[i].size_x, cube_defs[i].size_y, cube_defs[i].size_z);
//		c.SetPos(cube_defs[i].pos_x, cube_defs[i].pos_y, cube_defs[i].pos_z);
//		PhysBody3D *p = App->physics3D->AddBody(c);
//		if (cube_defs[i].add_collision_listener)
//			p->collision_listeners.add(this);
//	}
//	/*
//	c1.size.Set(R_W, R_H, C_X);
//	c1.SetPos(0, R_H / 2, C_X / 2);
//	App->physics3D->AddBody(c1, 0)->collision_listeners.add(this);
//	c2.size.Set(C_Y + R_W, R_H, R_W);
//	c2.SetPos(-C_Y / 2, R_H / 2, C_X + R_W / 2);
//	App->physics3D->AddBody(c2, 0);
//	c3.size.Set(R_W, R_H, C_X);
//	c3.SetPos(-C_Y, R_H / 2, C_X / 2);
//	App->physics3D->AddBody(c3, 0);
//	c4.size.Set(C_Y + R_W, R_H, R_W);
//	c4.SetPos(-C_Y / 2, R_H / 2, -R_W / 2);
//	App->physics3D->AddBody(c4, 0);
//	*/
//
//	y1.height = R_W / 2;
//	y1.radius = 1.0f;
//	y1.SetPos(-y1.height / 2, R_H, C_X / 6);
//	App->physics3D->AddBody(y1, 0);
//	y2.height = R_W / 2;
//	y2.radius = 1.0f;
//	y2.SetPos(y1.height / 2, R_H, (C_X / 6) * 2);
//	App->physics3D->AddBody(y2, 0);
//	y3.height = R_W / 2;
//	y3.radius = 1.0f;
//	y3.SetPos(-y1.height / 2, R_H, (C_X / 6) * 3);
//	App->physics3D->AddBody(y3, 0);
//	y4.height = R_W / 2;
//	y4.radius = 1.0f;
//	y4.SetPos(y1.height / 2, R_H, (C_X / 6) * 4);
//	App->physics3D->AddBody(y4, 0);
//	s1.radius = 7.0f;
//	s1.SetPos(-C_Y - y1.height / 2, R_H - s1.radius*0.9, C_X / 6);
//	App->physics3D->AddBody(s1, 0);
//	s2.radius = 7.0f;
//	s2.SetPos(-C_Y + y1.height / 2, R_H - s1.radius*0.9, (C_X / 6) * 2);
//	App->physics3D->AddBody(s2, 0);
//	s3.radius = 7.0f;
//	s3.SetPos(-C_Y - y1.height / 2, R_H - s1.radius*0.9, (C_X / 6) * 3);
//	App->physics3D->AddBody(s3, 0);
//	s4.radius = 7.0f;
//	s4.SetPos(-C_Y + y1.height / 2, R_H - s1.radius*0.9, (C_X / 6) * 4);
//	App->physics3D->AddBody(s4, 0);
//	App->camera->Move(vec3(0, 30, -30));
//	return ret;
//}
//// Load assets
//bool ModuleSceneIntro::CleanUp()
//{
//	LOG("Unloading Intro scene");
//	return true;
//}
//// Update: draw background
//update_status ModuleSceneIntro::Update(float dt)
//{
//	Plane(0, 1, 0, 0).Render();
//	p2List_item<Cube>* s_item = cubes.getFirst();
//	while (s_item)
//	{
//		s_item->data.Render();
//		s_item = s_item->next;
//	}
//	// c1.Render();
//	// c2.Render();
//	// c3.Render();
//	// c4.Render();
//
//	y1.Render();
//	y2.Render();
//	y3.Render();
//	y4.Render();
//	s1.Render();
//	s2.Render();
//	s3.Render();
//	s4.Render();
//	return UPDATE_CONTINUE;
//}
//void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
//{
//	int a = 0;
//}
//
//Welcome to MeetingWords!
//
//This pad text is synchronized as you type, so that everyone viewing this page sees the same text.This allows you to collaborate seamlessly on documents!
//
