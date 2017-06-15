#include "stdafx.h"
#include "DayTimeAnimation.h"


DayTimeAnimation::DayTimeAnimation(PGDirectionalLight* target) {
	target_light = target;
	sun_noon_point = v4(0.f, 0.f, 1.f, 1.f);
	cpt_timer = 0.f;
	interval_timer = 0.5f;
	rot_matrix_per_degree = glm::rotate(m4(1.f), (PG_Pi32/360.f)/60.f, v3(1.f, 0.f, 0.f));
}


DayTimeAnimation::~DayTimeAnimation() {
}

void DayTimeAnimation::Update(double delta_time) {
	cpt_timer += delta_time;
	if (cpt_timer >= interval_timer) {
		cpt_timer -= interval_timer;
		//Do stuff here
		sun_noon_point = rot_matrix_per_degree*sun_noon_point;
		target_light->direction = glm::normalize(v4(0.f) - sun_noon_point);
	}
}
