#include "stdafx.h"
#include "GeometryShaderProgram.h"


GeometryShaderProgram::GeometryShaderProgram() :
	ShaderProgram(Geometry_VertexShader, Geometry_FragShader){
}


GeometryShaderProgram::~GeometryShaderProgram() {
}

void GeometryShaderProgram::Init() {
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "unif_translate");
	this->Unif_Color = glGetUniformLocation(this->ShaderID, "unif_color");
	this->Unif_Scale = glGetUniformLocation(this->ShaderID, "unif_Scale");
	ShaderProgram::Init();
}

void GeometryShaderProgram::Render(BaseMesh * mesh, v3 * possition, v3 *scale, v4 *color) {
	if (this->IsInitialize == true) {
		this->Use();

		mesh->BindVAO();
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);
		glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), *scale)[0][0]);

		glUniform4fv(this->Unif_Color, 1, &color->x);
		
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
		//Todo(Marc): Add debugg
	}
}
