#include "stdafx.h"
#include "BasicGeometryMesh.h"


BasicGeometryMesh::BasicGeometryMesh() :
	BaseMesh(){
}


BasicGeometryMesh::~BasicGeometryMesh() {
}

//Todo(Marc):Make this be able to build defferent shape
void BasicGeometryMesh::Build() {
	BaseMesh::Build();
	//Build the Vao buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(geo_square_vertex_data), geo_square_vertex_data, GL_STATIC_DRAW);
	this->Vertices_Count = 6;
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	BuildableObject::EndBuilding();
}
