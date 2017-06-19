#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H


#include "stdafx.h"
#include "Core.h"

#define PG_SHADER(shader_text) static shader_text;

#define GLSL330(src) "#version 330 core\n"  #src ;
#define GlobalStruct(src) "#version 330 core\n"  #src ;

class ShaderProgram {
protected:
	void ShaderProgram::Use();
	GLuint ShaderID;
	bool IsInitialize;
private:
	GLuint VertexShaderID;
	GLuint FragmentShaderID;
	GLuint GeometryShaderID;
	GLuint CompileShaderScr(GLuint shaderId, const char * shader_scr);
public:
	ShaderProgram(const char * vertex_src, const char * fragment_src);
	ShaderProgram(const char * vertex_src, const char * fragment_src, const char * geometry_src);
	virtual ~ShaderProgram();
	void virtual ShaderProgram::Render();
	void virtual ShaderProgram::Init();

};
#endif //SHADERPROGRAM_H
