#include "stdafx.h"
#include "HexaGridMapShaderProgram.h"


HexaGridMapShaderProgram::HexaGridMapShaderProgram() : 
	ShaderProgram(map_hexa_vertex_shader, map_hexa_FragShader){
}
HexaGridMapShaderProgram::~HexaGridMapShaderProgram() {

}
void HexaGridMapShaderProgram::Init(){
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
	glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "SceneAdvanceLightData_UBO"), 3);
	this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
	ShaderProgram::Init();
}
void HexaGridMapShaderProgram::Render(BaseMesh * mesh, v3 *possition) {
	if (this->IsInitialize == true)	{ 
		this->Use();
	
		mesh->BindVAO();
		//Vertex shader uniform variable
		glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), *possition)[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVeticesCount());
	}
	else {
		//Todo(Marc): Add debugg
	}
}
