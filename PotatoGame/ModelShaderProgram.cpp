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
	this->Unif_Scale = glGetUniformLocation(this->ShaderID, "Scale");
	this->Unif_Rotate = glGetUniformLocation(this->ShaderID, "Rotation");
	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
	this->Unif_IsOverringMtl = glGetUniformLocation(this->ShaderID, "IsOverringMtl");
	this->Unif_Mat_Ambient = glGetUniformLocation(this->ShaderID, "OverridingMtl.ambient");
	this->Unif_Mat_Diffuse = glGetUniformLocation(this->ShaderID, "OverridingMtl.diffuse");
	this->Unif_Mat_Specular = glGetUniformLocation(this->ShaderID, "OverridingMtl.specular");
	this->Unif_Mat_Shinniness = glGetUniformLocation(this->ShaderID, "OverridingMtl.shininess");
	ShaderProgram::Init();
}
void ModelMtlShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition, MaterielRawData * mtl = nullptr) {
	//Todo(Marc): Maybe we should not create resource
	Quaternion* tempo = new Quaternion(v3(0.f, 0.f, 0.f));
	ModelMtlShaderProgram::Render(mesh, possition, &v3(1.f), tempo, mtl);
	delete(tempo);
}

void ModelMtlShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition, v3 * scale , Quaternion* quat,MaterielRawData * mtl = nullptr) {
	if (this->IsInitialize == true) {
		if (mesh->Mode == Vertices_Normal_Material) {
			this->Use();
			//Vertex shader uniform variable
			m4* t = new m4(1.f);
			*t = glm::scale(m4(1.f),*scale);
			glUniformMatrix4fv(this->Unif_Rotate, 1, GL_FALSE, glm::value_ptr(glm::toMat4(*quat)));
			glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);
			glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, glm::value_ptr(*t));
			if (mtl != nullptr) {
				glUniform1i(this->Unif_IsOverringMtl, 1);
				//// Set material properties
				glUniform3fv(Unif_Mat_Ambient, 1, &mtl->Ambient[0]);
				glUniform3fv(Unif_Mat_Diffuse, 1, &mtl->Diffuse[0]);
				glUniform3fv(Unif_Mat_Specular, 1, &mtl->Specular[0]);
				glUniform1f(Unif_Mat_Shinniness, mtl->Shininess);
			}
			else {
				glUniform1i(this->Unif_IsOverringMtl, 0);
			}
			
		
			mesh->BindVAO();
			glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
			delete(t);
		}
	}
	else {

	}

}

//Do not use this method
void ModelMtlShaderProgram::Render(ModelMeshV1 * mesh, m4 * possition_m, m4 * scale_m, MaterielRawData * mtl) {
	if (this->IsInitialize == true && mesh->Mode == Vertices_Normal) {
		this->Use();
		
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, glm::value_ptr(*possition_m));
		glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, glm::value_ptr(*scale_m));
		glUniform3fv(Unif_Mat_Ambient, 1, &mtl->Ambient[0]);
		glUniform3fv(Unif_Mat_Diffuse, 1, &mtl->Diffuse[0]);
		glUniform3fv(Unif_Mat_Specular, 1, &mtl->Specular[0]);
		glUniform1f(Unif_Mat_Shinniness, mtl->Shininess);
		mesh->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
	}
}
//********************************************************************************************
//********************************************************************************************
ModelShaderProgram::ModelShaderProgram() :
	ShaderProgram(base_model_vertex_shader, model_mtl_FragShader) {
}
ModelShaderProgram::~ModelShaderProgram() {
}
void ModelShaderProgram::Init() {
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "SceneAdvanceLightData_UBO"), 3);

	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
	this->Unif_Scale = glGetUniformLocation(this->ShaderID, "Scale");
	this->Unif_Rotate = glGetUniformLocation(this->ShaderID, "Rotation");

	this->Unif_Mat_Ambient = glGetUniformLocation(this->ShaderID, "OverridingMtl.ambient");
	this->Unif_Mat_Diffuse = glGetUniformLocation(this->ShaderID, "OverridingMtl.diffuse");
	this->Unif_Mat_Specular = glGetUniformLocation(this->ShaderID, "OverridingMtl.specular");
	this->Unif_Mat_Shinniness = glGetUniformLocation(this->ShaderID, "OverridingMtl.shininess");
	ShaderProgram::Init();
}

void ModelShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition, MaterielRawData * mtl) {
	ModelShaderProgram::Render(mesh, possition, &v3(1.f), mtl);
}
void ModelShaderProgram::Render(ModelMeshV1 * mesh, v3 * possition, v3 * scale, MaterielRawData * mtl) {
	if (this->IsInitialize == true && mesh->Mode == Vertices_Normal) {
		this->Use();
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);
		glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), *scale)[0][0]);
		glUniform3fv(Unif_Mat_Ambient, 1, &mtl->Ambient[0]);
		glUniform3fv(Unif_Mat_Diffuse, 1, &mtl->Diffuse[0]);
		glUniform3fv(Unif_Mat_Specular, 1, &mtl->Specular[0]);
		glUniform1f(Unif_Mat_Shinniness, mtl->Shininess);
		mesh->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
	}
}
void ModelShaderProgram::Render(ModelMeshV1 * mesh, m4 * possition_m, m4 * scale_m, MaterielRawData * mtl) {
	if (this->IsInitialize == true && mesh->Mode == Vertices_Normal) {
		this->Use();
		
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, glm::value_ptr(*possition_m));
		glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, glm::value_ptr(*scale_m));
		glUniform3fv(Unif_Mat_Ambient, 1, &mtl->Ambient[0]);
		glUniform3fv(Unif_Mat_Diffuse, 1, &mtl->Diffuse[0]);
		glUniform3fv(Unif_Mat_Specular, 1, &mtl->Specular[0]);
		glUniform1f(Unif_Mat_Shinniness, mtl->Shininess);
		mesh->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
	}
}
//********************************************************************************************