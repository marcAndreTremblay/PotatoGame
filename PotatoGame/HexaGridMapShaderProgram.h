#ifndef HEXA_GRID_SHADER_PROGRAM_H
#define HEXA_GRID_SHADER_PROGRAM_H

#include "stdafx.h"
#include "ShaderProgram.h"
#include "BaseMesh.h"
using namespace PG::Core;

//Vertex shader
#if 1 
PG_SHADER(const char* map_hexa_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position; //<- world space already
	layout(location = 1) in vec3 vertex_normal;
	layout(location = 2) in vec3 ambient;
	layout(location = 3) in vec3 diffuse;
	layout(location = 4) in vec3 specular;
	layout(location = 5) in vec4 shininess;

	struct PGMaterial {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};

	uniform mat4 Translate; //Note(Marc): will translate all the world space coord of the map

	out vec3 Normal;
	out vec3 FragPos;
	out vec4 Vertex_World_Possiton;

	out PGMaterial Matl;

	layout(std140) uniform Renderer_UBO {
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};


	void main() {	
		Matl.ambient = ambient;
		Matl.diffuse = diffuse;
		Matl.specular = specular;
		Matl.shininess = shininess.x;
		Vertex_World_Possiton = (Translate)* vertex_position;
		FragPos = vec3(WorldView* Vertex_World_Possiton);
		gl_Position = WorldProjection  * WorldView * Vertex_World_Possiton;		
		Normal = mat3(transpose(inverse(WorldView))) * vertex_normal;
	}
));
#endif
//Fragment shader
#if 1 
PG_SHADER(const char* map_hexa_FragShader = GLSL330(
	struct PGMaterial {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct PGLightSettings {
	int UseDirectional; // 1 = true , 0 = false
	int UsePoint;// 1 = true , 0 = false
	int UseGamma;// gamme value , 0 = false
	int Point_Light_Max_Cap; // Number of entity of point light reserve in memory
};
struct PGPointLight {
	vec4 setting; // x = is in use 1 = true = false
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 attenuation_factors; //Kc = constant , Kl = linear , Kq = quadratic , use attenuation 1=true 2=false 
};
struct PGDirectionalLight {
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


layout(std140) uniform Renderer_UBO {
	mat4 WorldProjection;
	mat4 WorldView;
	mat4 GUIProjection;
	vec4 CenterOfFog; // ->W = radius
};
layout(std140) uniform SceneAdvanceLightData_UBO {
	PGLightSettings Light_Setting;
	PGDirectionalLight D_Light;
	PGPointLight P_Light[10];
};

in vec3 Normal;
in vec3 FragPos;
in PGMaterial Matl;
in vec4 Vertex_World_Possiton;

out vec4 color;
vec3 CalcPointLight(PGPointLight p_light, vec3 normal, vec3 viewDir, float distance) {
	// Ambient
	vec3 ambient = vec3(0.3f*p_light.diffuse) * Matl.ambient;

	// Diffuse 
	vec3 LightPos = vec3(WorldView * p_light.position);
	vec3 lightDir = normalize(LightPos - FragPos);
	
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = vec3(p_light.diffuse) * (diff * Matl.diffuse);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
	vec3 specular = vec3(p_light.specular) * (spec * Matl.specular);

	//Attenuation
	if (p_light.attenuation_factors.w == 1.f) { // 1=true 0=false
		float attenuation = 1.f / (p_light.attenuation_factors.x +
			p_light.attenuation_factors.y * distance +
			p_light.attenuation_factors.z * (distance*distance));
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}

	return (ambient+ diffuse + specular);
}
vec3 CalcDirLight(PGDirectionalLight d_light, vec3 normal, vec3 viewDir) {
	// Ambient 
	vec3 ambient = vec3(0.3f*d_light.diffuse) * Matl.ambient;
	// Diffuse 
	
	vec3 lightDir = normalize(vec3(WorldView *-d_light.direction));
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = vec3(d_light.diffuse) * (diff * Matl.diffuse);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
	vec3 specular = vec3(d_light.specular) * (spec * Matl.specular);
	


	return (ambient + diffuse + specular);
}

void main() {
	vec3 viewDir = normalize(-FragPos); //Note() The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
	vec3 norm = normalize(Normal);
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	
	//Point light calculation
	if (Light_Setting.UsePoint == 1) {
		for (int i = 0; i < 10; i++) {
			if (P_Light[i].setting.x == 1.f) { //Check if light is in the scene
				float distance = length(vec3(P_Light[i].position) - vec3(Vertex_World_Possiton)); //Calculate distance, 
				if (P_Light[i].setting.y == 0 ||//Check if the light is too far
					distance < P_Light[i].setting.y) {
					result += CalcPointLight(P_Light[i], norm, viewDir, distance);
				}
			}
		}
		
	}
	//Dirrectional light calculation
	if (Light_Setting.UseDirectional == 1) {
		result += 0.1f*CalcDirLight(D_Light, norm, viewDir);
	}
	//Gamma calculation
	if (Light_Setting.UseGamma == 1) {
		result = pow(result, vec3(1.0f / 2.2f));
	}
	color = vec4(result, 1.0f);

}
));
#endif
class HexaGridMapShaderProgram :
	public ShaderProgram {
private:
	GLuint Unif_Translate;
public:
	HexaGridMapShaderProgram();
	virtual ~HexaGridMapShaderProgram();
	virtual void Init();
	virtual void Render(BaseMesh * mesh, v3 *possition);
};
#endif //HEXA_GRID_SHADER_PROGRAM_H

