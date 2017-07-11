#pragma once

#include "Core.h"
using namespace PG::Core;

class Light {
public:
	v4 ambient; //Todo(Marc): Remove this
	v4 diffuse;
	v4 specular;
	Light();
	virtual ~Light();
};


class PointLight : public Light {
public:
	v4 position;
	v4 attenuation_factors;
	PointLight();
	virtual ~PointLight();
};


class DirectionalLight : public Light {
public:
	v4 direction;
	DirectionalLight();
	virtual ~DirectionalLight();
};

