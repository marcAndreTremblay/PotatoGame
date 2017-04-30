#include "stdafx.h"
#include "ModelShaderProgram.h"

//********************************************************************************************
ModelMtlShaderProgram::ModelMtlShaderProgram() :
	ShaderProgram(model_mtl_vertex_shader, model_mtl_FragShader) {
}
ModelMtlShaderProgram::~ModelMtlShaderProgram() {
}
void ModelMtlShaderProgram::Init() {
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "SceneAdvanceLightData_UBO"), 3);
	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
	ShaderProgram::Init();
}
void ModelMtlShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition) {
	if (this->IsInitialize == true && mesh->Mode == Vertices_Normal_Material) {
		this->Use();
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);
		mesh->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {	
	}
}
//********************************************************************************************
//********************************************************************************************
ModelShaderProgram::ModelShaderProgram() :
	ShaderProgram(base_model_vertex_shader, base_model_FragShader) {
}
ModelShaderProgram::~ModelShaderProgram() {
}
void ModelShaderProgram::Init() {
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
	this->Unif_Color = glGetUniformLocation(this->ShaderID, "Model_Color");
	ShaderProgram::Init();
}
void ModelShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition, v4 * color) {
	if (this->IsInitialize == true && mesh->Mode == Vertices_Normal) {
		this->Use();
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);
		glUniform4fv(this->Unif_Color, 1, &color->x);
		mesh->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
	}
}
//********************************************************************************************