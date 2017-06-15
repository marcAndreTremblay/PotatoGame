#pragma once

#include "stdafx.h"
#include "Core.h"
#include "IAnimation.h"

#include "PGShaderSources.h"

class DayTimeAnimation : public IAnimation {
private:
	v4 sun_noon_point;
	m4 rot_matrix_per_degree;
	PGDirectionalLight* target_light;
	double cpt_timer;
	double interval_timer;
public:
	DayTimeAnimation(PGDirectionalLight * target);
	virtual ~DayTimeAnimation();
	void Update(double delta_time);
};

