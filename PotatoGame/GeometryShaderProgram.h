#ifndef GEOMETRY_SHADER_PROGRAM_H
#define GEOMETRY_SHADER_PROGRAM_H

#include "stdafx.h"
#include "ShaderProgram.h"
#include "BaseMesh.h"
using namespace PG::Core;

//Vertex shader
#if 1 
PG_SHADER(const char* Geometry_VertexShader = GLSL330(
	layout(location = 0) in vec4 vertex_position; //<- world space already

	uniform mat4 unif_translate; //Note(Marc): will translate all the world space coord of the map
	uniform mat4 unif_Scale;

	layout(std140) uniform Renderer_UBO {
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};


	void main() {
		gl_Position = WorldProjection  * WorldView * (unif_translate*unif_Scale)* vertex_position;
	}
));
#endif
//Fragment shader
#if 1 
PG_SHADER(const char* Geometry_FragShader = GLSL330(

	layout(std140) uniform Renderer_UBO {
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog; // ->W = radius
	};

	uniform vec4 unif_color;
	out vec4 color;

	void main() {
		//Combine each	colors
		color = unif_color;
	}
));
#endif
class GeometryShaderProgram :
	public ShaderProgram {
private:
	GLuint Unif_Translate;
	GLuint Unif_Color;
	GLuint Unif_Scale;
public:
	GeometryShaderProgram();
	virtual ~GeometryShaderProgram();
	virtual void Init();
	virtual void Render(BaseMesh * mesh, v3 * possition, v3 *scale, v4 *color);
};
#endif //GEOMETRY_SHADER_PROGRAM_H

