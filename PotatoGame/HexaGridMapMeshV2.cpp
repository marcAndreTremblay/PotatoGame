#include "stdafx.h"
#include "HexaGridMapMeshV2.h"


HexaGridMapMeshV2::HexaGridMapMeshV2(GridRawDataV2 * data) :BaseMesh() {
	Data = data;
}

HexaGridMapMeshV2::~HexaGridMapMeshV2() {
}

void HexaGridMapMeshV2::Build() {
	BaseMesh::Build();
	BuildableObject::StartBuilding();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Todo(Marc): Finis up , load map base model then create the vbo for the region

	BuildableObject::EndBuilding();
}
