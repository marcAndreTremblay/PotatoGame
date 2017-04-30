#include "stdafx.h"
#include "ModelMeshV1.h"



ModelMeshV1::ModelMeshV1(ModelRawDataV1 * _data) :BaseMesh(){
	Model_Data = _data;
	bool UseMaterialFile;
	bool UseTextureMap;
	if (_data->UseMaterialFile == true) {
		this->Mode = Vertices_Normal_Material;
	}
	else{
		if (_data->UseTextureMap == true) {
			this->Mode = Vertices_Normal_Texture;
		}
		else {
			this->Mode = Vertices_Normal;
		}
	}
}

ModelMeshV1::~ModelMeshV1() {

}

void ModelMeshV1::Build() {
	BaseMesh::Build();
	BuildableObject::StartBuilding();
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	this->Data_Size_Per_vertex = 0;
	this->Vertices_Count = Model_Data->GetFaceCount() * 3;

	unsigned int *faces_array_ptr = Model_Data->GetFacesArrayPtr();
	v3* vertices_array_ptr = Model_Data->GetVertivesArrayPtr();
	v3* normals_array_ptr = Model_Data->GetNormalsArrayPtr();
	
	switch (Mode) {
		case Vertices_Normal: { 
			Data_Size_Per_vertex =
				sizeof(v4) + //LOC (0)
				sizeof(v3); //LOC (1)
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
			break; }
		case Vertices_Normal_Material: {
			Data_Size_Per_vertex =
				sizeof(v4) + //LOC (0)
				sizeof(v3) + //LOC (1)
				sizeof(v3) + //LOC (2)
				sizeof(v3) + //LOC (3)
				sizeof(v3) + //LOC (4)
				sizeof(v4); //LOC (5)
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4) + sizeof(v3)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4) + 2 * sizeof(v3)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4) + 3 * sizeof(v3)));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, Data_Size_Per_vertex, (GLvoid*)(sizeof(v4) + 4 * sizeof(v3)));
			glEnableVertexAttribArray(5);
			glBindVertexArray(0);
			break; }
		case Vertices_Normal_Texture: { 
			//Note(Marc): Not suported yet
			break; }
		default: {Data_Size_Per_vertex = 0; break; }
	}
	
	//Gen buffer memory
	//*********************************************************************
	glBufferData(GL_ARRAY_BUFFER, 
		this->Data_Size_Per_vertex * this->Vertices_Count, 
		nullptr, GL_DYNAMIC_DRAW);
	//*********************************************************************

	int buffer_offet = 0;
	for (int i = 0; i < Model_Data->GetFaceCount() * 3; i++) {
		switch (Mode) {
			case Vertices_Normal: {
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(vertices_array_ptr[*faces_array_ptr - 1], 1.f));
				faces_array_ptr++;
				buffer_offet += sizeof(v4);
				//Add v3

				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &v4(normals_array_ptr[*faces_array_ptr - 1], 1.f));
				faces_array_ptr++;
				buffer_offet += sizeof(v3);
				break; }
			case Vertices_Normal_Material: { 
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(vertices_array_ptr[*faces_array_ptr - 1], 1.f));
				faces_array_ptr++;
				buffer_offet += sizeof(v4);
				//Add v3

				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &v4(normals_array_ptr[*faces_array_ptr - 1], 1.f));
				faces_array_ptr++;
				buffer_offet += sizeof(v3);
			
				MaterielRawData* current_mat = Model_Data->mtl_file->FindByNameId(*faces_array_ptr);
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Ambient); //Note dont know bender
				buffer_offet += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Diffuse);
				buffer_offet += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Specular);
				buffer_offet += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(current_mat->Shininess, 1.f, 1.f, 1.f));
				buffer_offet += sizeof(v4);

				faces_array_ptr++;
				break; }
			case Vertices_Normal_Texture: {
				//Note(Marc): Not suported yet
				break; }
			default: {break; }
		}
	}
	glBindVertexArray(0);
	BuildableObject::EndBuilding();
}
