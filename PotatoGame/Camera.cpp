#include "stdafx.h"
#include "Camera.h"

PG::Engine::CameraAnimation::CameraAnimation(Camera * camera) : IAnimation(){
	animated_camera = camera;

	nor_direction = v3(1.f, 1.f, 1.f);
	nor_direction = glm::normalize(nor_direction);
	speed = 0.5f; //Unit / s;

	

	cpt_timer = 0.f;
	interval_timer = PG_60HZT;
}

PG::Engine::CameraAnimation::~CameraAnimation() {
}

void PG::Engine::CameraAnimation::Update(double delta_time) {

	cpt_timer+= delta_time;
	if (cpt_timer >= interval_timer) {
		cpt_timer -= interval_timer;
		//Do stuff here
		

		//animated_camera->Possition += nor_direction*(speed*(r32)interval_timer);
		animated_camera->RotateZAxis(PG_Pi32/10.f * interval_timer, v3(0.f));
	}
}
