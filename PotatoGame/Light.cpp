#include "stdafx.h"
#include "Light.h"


Light::Light() {
}


Light::~Light() {
}

PointLight::PointLight() :Light() {
}

PointLight::~PointLight() {
}

DirectionalLight::DirectionalLight() :Light(){
}

DirectionalLight::~DirectionalLight() {
}
