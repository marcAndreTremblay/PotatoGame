#include "stdafx.h"
#include "BaseMesh.h"


BaseMesh::BaseMesh() {
	Vertices_Count = 0;
}


BaseMesh::~BaseMesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void BaseMesh::Build() {
	BuildableObject::StartBuilding();
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	BuildableObject::EndBuilding();
}

void BaseMesh::BindVAO() {
	glBindVertexArray(this->VAO);
}
int BaseMesh::GetVeticesCount() {
	return this->Vertices_Count;
}


