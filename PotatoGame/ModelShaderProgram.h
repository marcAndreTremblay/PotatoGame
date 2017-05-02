#if !defined(MODEL_SHADER_PROGRAM_H)
#define MODEL_SHADER_PROGRAM_H

#include "stdafx.h"
#include "ShaderProgram.h"
#include "BaseMesh.h"
#include "ModelMeshV1.h"

using namespace PG::Core;



class ModelMtlShaderProgram :
	public ShaderProgram {
private:
	GLuint Unif_Translate;
	GLuint Unif_IsOverringMtl;
	
	GLuint Unif_Mat_Ambient;
	GLuint Unif_Mat_Diffuse;
	GLuint Unif_Mat_Specular;
	GLuint Unif_Mat_Shinniness;
public:
	ModelMtlShaderProgram();
	virtual ~ModelMtlShaderProgram();
	 void Init();
	 void Render(ModelMeshV1 * mesh, v3 *possition, MaterielRawData* mtl);
};

class ModelShaderProgram :
	public ShaderProgram {
private:
	GLuint Unif_Translate;
	
	GLuint Unif_Mat_Ambient;
	GLuint Unif_Mat_Diffuse;
	GLuint Unif_Mat_Specular;
	GLuint Unif_Mat_Shinniness;
public:
	ModelShaderProgram();
	virtual ~ModelShaderProgram();
	void Init();
	void Render(ModelMeshV1 * mesh, v3 *possition, MaterielRawData *color);
};
//Shader for model  todo(Marc): Make the lighting work for this shit
//Vertex shader
#if 1 
PG_SHADER(const char* base_model_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position; //<- world space already
	layout(location = 1) in vec3 vertex_normal;

	struct PGMaterial {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};

	uniform mat4 Translate; //Note(Marc): will translate all the world space coord of the map
	uniform PGMaterial OverridingMtl;

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
		Matl = OverridingMtl;
		Vertex_World_Possiton = (Translate)* vertex_position;
		gl_Position = WorldProjection  * WorldView * Vertex_World_Possiton;
		FragPos = vec3(WorldView*(Translate)* vertex_position);
		Normal = mat3(transpose(inverse(WorldView))) * vertex_normal;
	}
));
#endif
//Fragment shader
#if 1 
PG_SHADER(const char* base_model_FragShader = GLSL330(
	struct PGLight {
		vec4 position;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	};
	uniform vec4 Model_Color;

	layout(std140) uniform Renderer_UBO {
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog; // ->W = radius
	};
	layout(std140) uniform SceneAdvanceLightData_UBO {
		PGLight Light;
	};

	in vec3 Normal;
	in vec3 FragPos;
	in vec4 Vertex_World_Possiton;

	out vec4 color;

void main() {
	color = Model_Color;
}
));
#endif
//Shader for model using Materiel
//Vertex shader
#if 1 
PG_SHADER(const char* model_mtl_vertex_shader = GLSL330(
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
	uniform int IsOverringMtl;
	uniform PGMaterial OverridingMtl;

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
		if (IsOverringMtl == 1) 			{
			Matl = OverridingMtl;
		}
		else {
			Matl.ambient = ambient;
			Matl.diffuse = diffuse;
			Matl.specular = specular;
			Matl.shininess = shininess.x;
		}
		Vertex_World_Possiton = (Translate)* vertex_position;
		
		gl_Position = WorldProjection  * WorldView * Vertex_World_Possiton;
		FragPos = vec3(WorldView*(Translate)* vertex_position);
		Normal = mat3(transpose(inverse(WorldView /**  Translate*/))) * vertex_normal;
	}
));
#endif
//Fragment shader
#if 1 
PG_SHADER(const char* model_mtl_FragShader = GLSL330(
	struct PGMaterial {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct PGLight {
	vec4 position;
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
	PGLight Light;
};

in vec3 Normal;
in vec3 FragPos;
in PGMaterial Matl;
in vec4 Vertex_World_Possiton;

out vec4 color;

void main() {
	float alpha = 1.f;
	float radius_fog = 15;
	float decay_lenght = 4;
	float dist = distance(CenterOfFog, Vertex_World_Possiton);
	if (dist > radius_fog) {
		dist -= radius_fog;
		alpha = 1 - dist / decay_lenght;
		if (dist > decay_lenght) {
			alpha = 0.0f;
		}
	}
	// Ambient
	vec3 ambient = vec3(Light.ambient) * Matl.ambient;

	// Diffuse 
	vec3 LightPos = vec3(WorldView * Light.position);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = vec3(Light.diffuse) * (diff * Matl.diffuse);

	vec3 viewDir = normalize(-FragPos); // The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
	vec3 specular = vec3(Light.specular) * (spec * Matl.specular);

	//Combine each	colors
	color = vec4((ambient + diffuse + specular), 1.0f);

}
));
#endif
#endif //MODEL_SHADER_PROGRAM_H

