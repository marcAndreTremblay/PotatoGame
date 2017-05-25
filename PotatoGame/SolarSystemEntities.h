#pragma once

#include "Core.h"
#include "List.h"
using namespace PG::Core;
#include "BaseRenderer.h"
#include "Entity.h"
using namespace PG::Engine;

#include "IAnimation.h" //Move this to anothe file



class CelestialBody : public Entity {
public:
	// If not null possition in relatiion
	CelestialBody* parent; // Not owned
	m4 *translation_matrix;
	m4 *scale_matrix;
	v3 size;
	r32 orbit_radius;
	r32 angular_speed;
	m4 GetPossition() {
		if (parent == nullptr) {
			
			return *translation_matrix;
		}
		else {
			return *parent->translation_matrix**translation_matrix; 
		}
	}
	void SetPossition(v3 *new_possition);
	void SetParent(CelestialBody* _parent);
	CelestialBody(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size);
	virtual ~CelestialBody();
	virtual void CelestialBody::Render();
};

class Star : public CelestialBody {
public:
	Star(r32 size);
	virtual ~Star();
	void Star::Render(BaseRenderer *renderer);
};

class Planet : public CelestialBody {
public:
	Planet();
	Planet(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size);
	Planet(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size, CelestialBody * parent);
	virtual ~Planet();
	void Planet::Render(BaseRenderer *renderer);
};
class Moon : public CelestialBody {
public:
	Moon(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size, CelestialBody* parent);
	virtual ~Moon();
	void Moon::Render(BaseRenderer *renderer);
};

/*
	Other celestial body ideas
		-Comet
		-Asteorid (belt)
*/


class CelestialBodyAnimation : public IAnimation{
private:
	CelestialBody* update_target; //Not owned
	m4 rot_matrix_per_interval;
	double timer_cpt;
	double timer_intervale;
public:
	CelestialBodyAnimation(CelestialBody * target);
	CelestialBodyAnimation(CelestialBody* target, double update_intervale);
	~CelestialBodyAnimation();
	void Update(double delta_time);
};


class SolorSystemEntities {
private:
public:
	List<CelestialBody>* bodies_list;
	SolorSystemEntities();
	~SolorSystemEntities();
};

