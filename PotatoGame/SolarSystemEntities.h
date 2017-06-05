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
	
	
	m4 * rotation_matrix;
	Quaternion* quat;

	v3 size;
	r32 orbit_radius;
	r32 angular_speed;
	v3 GetWorldPossition();
	v3 GetWorldSize();
	void SetPossition(v3 *new_possition);
	void SetParent(CelestialBody* _parent);
	CelestialBody(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size, r32 height_plane);
	virtual ~CelestialBody();
	virtual void CelestialBody::Render();
};

class Star : public CelestialBody {
public:
	Star(r32 size, r32 height_plane);
	virtual ~Star();
	void Star::Render(BaseRenderer *renderer);
};

class Planet : public CelestialBody {
public:
	Planet();
	Planet(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size, r32 height_plane);
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
	float rot_cpt;
public:
	float WaveFct(float w, //Frequence angulaire
				  double t, 
				  float k, 
				  float x, 
			      float A, 
				  float dephasage = 0.f) {
		return A*glm::cos(w*t - k*x + dephasage);
	}
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

