#include "stdafx.h"
#include "SolarSystemEntities.h"


SolorSystemEntities::SolorSystemEntities() {
	//Create planet antities
	bodies_list = new List<CelestialBody>(true);
}


SolorSystemEntities::~SolorSystemEntities() {
	delete(bodies_list);
}

Planet::Planet() :
	CelestialBody(0.f, 0.f,1.f, 1.f) {
}

Planet::Planet(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size) :
	CelestialBody(orbit_r, starting_angle, _angular_speed, size) {
}
Planet::Planet(r32 orbit_r, r32 starting_angle, r32 _angular_speed ,r32 size, CelestialBody* parent) :
	CelestialBody(orbit_r, starting_angle, _angular_speed, size) {
	this->SetParent(parent);
}


Planet::~Planet() {
}

void Planet::Render(BaseRenderer *renderer) {
	
}

Moon::Moon(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 size, CelestialBody * parent) :
	CelestialBody(orbit_r, starting_angle, _angular_speed, size) {
	this->SetParent(parent);
}

Moon::~Moon() {
} 

void Moon::Render(BaseRenderer * renderer) {
	
}


void CelestialBody::SetPossition(v3 *new_possition) {
	this->World_Possition = *new_possition;
	*translation_matrix = glm::translate(m4(1.f), *new_possition);
}

void CelestialBody::SetParent(CelestialBody* _parent) {
	parent = _parent;
}

CelestialBody::CelestialBody(r32 orbit_r, r32 starting_angle, r32 _angular_speed, r32 _size) :Entity(){

	this->size = v3(_size);
	scale_matrix = new m4();
	*scale_matrix = glm::scale(m4(1.f), this->size);
	
	this->orbit_radius = orbit_r;
	this->angular_speed = _angular_speed;
	this->parent = nullptr;
	
	//Calcul starting possition
	m4 rot_mat = glm::rotate(m4(1.f), starting_angle, v3(0.f, 0.f, 1.f));
	v4 tempo_possition = v4(orbit_r, 0.f, 0.f, 1.f);
	this->World_Possition = v3(rot_mat*tempo_possition);
	translation_matrix = new m4();
	*translation_matrix = glm::translate(m4(1.f), this->World_Possition);
}

CelestialBody::~CelestialBody() {
	delete(translation_matrix);
	delete(scale_matrix);
}

void CelestialBody::Render() {
	
}

CelestialBodyAnimation::CelestialBodyAnimation(CelestialBody * target) :IAnimation(){
	target->SetAnimation(this);
	update_target = target;
	timer_intervale = PG_60HZT;
	timer_cpt = 0.f;
	rot_matrix_per_interval = glm::rotate(m4(1.f),target->angular_speed*(r32)timer_intervale, v3(0.f, 0.f, 1.f));
}

CelestialBodyAnimation::CelestialBodyAnimation(CelestialBody * target, double update_intervale) :IAnimation() {
	update_target = target;
	timer_intervale = update_intervale;
	timer_cpt = 0.f;
}

CelestialBodyAnimation::~CelestialBodyAnimation() {
}

void CelestialBodyAnimation::Update(double delta_time) {
	timer_cpt += delta_time;
	if (timer_cpt >= timer_intervale) {
		timer_cpt -= timer_intervale;
		v4 tempo_pos = v4(update_target->World_Possition, 1.f);
		this->update_target->World_Possition = v3(rot_matrix_per_interval*tempo_pos);
	}
}


Star::Star(r32 _size) : CelestialBody(0.f,0.f,0.f, _size){
	this->World_Possition = v3(0.f, 0.f, 0.f);
	this->size = v3(_size, _size, _size);
}

Star::~Star() {
}

void Star::Render(BaseRenderer * renderer) {
}
