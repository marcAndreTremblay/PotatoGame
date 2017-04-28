#ifndef GEOMETRY_SHADER_PROGRAM_H
#define GEOMETRY_SHADER_PROGRAM_H

#include "stdafx.h"
#include "ShaderProgram.h"
#include "BaseMesh.h"
using namespace PG::Core;

//Vertex shader
#if 1 
PG_SHADER(const char* Geometry_VertexShader = GLSL330(
	layout(location = 0) in vec4 vertex_position;

	uniform mat4 Translate;
	uniform mat4 Scale;

	layout(std140) uniform Renderer_UBO {
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vertex_position;
	}
));
#endif
//Fragment shader
#if 1 
PG_SHADER(const char* Geometry_FragShader = GLSL330(
	uniform vec4 FragColor;
	out vec4 color;

	void main() {
		color = FragColor;
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
	virtual void Render(BaseMesh * mesh, v3 possition, v3 scale, v4 color);
};
#endif //GEOMETRY_SHADER_PROGRAM_H

