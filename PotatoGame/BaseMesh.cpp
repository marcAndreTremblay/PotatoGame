#include "stdafx.h"
#include "BaseMesh.h"


BaseMesh::BaseMesh() {
	Vertices_Count = 0;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
}


BaseMesh::~BaseMesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void BaseMesh::Build() {

}

void BaseMesh::BindVAO() {
	glBindVertexArray(this->VAO);
}
int BaseMesh::GetVeticesCount() {
	return this->Vertices_Count;
}


