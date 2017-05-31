#include "stdafx.h"
#include "HexaGridMapMeshV2.h"

//Note(Marc): This function will override the model's file material
void HexaGridMapMeshV2::PushModelToBuffer(int *buffer_cursor, ModelRawDataV1 * model_data, MaterielRawData * material , m4* offset,m4* scale,m4* rotate) {
	
	unsigned int *faces_array_ptr = model_data->GetFacesArrayPtr();
	v3* vertices_array_ptr = model_data->GetVertivesArrayPtr();
	v3* normals_array_ptr = model_data->GetNormalsArrayPtr();
	for (int i = 0; i < model_data->GetFaceCount() * 3; i++) {

		v4 posstion_world_space = *offset**scale**rotate*v4(vertices_array_ptr[*faces_array_ptr - 1], 1.f);

		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v4), &posstion_world_space);
		faces_array_ptr++;
		*buffer_cursor += sizeof(v4);

		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v3), &v4(normals_array_ptr[*faces_array_ptr - 1], 1.f));
		faces_array_ptr++;
		*buffer_cursor += sizeof(v3);

		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v3), &material->Ambient); //Note dont know bender
		*buffer_cursor += sizeof(v3);
		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v3), &material->Diffuse);
		*buffer_cursor += sizeof(v3);
		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v3), &material->Specular);
		*buffer_cursor += sizeof(v3);
		glBufferSubData(GL_ARRAY_BUFFER, *buffer_cursor, sizeof(v4), &v4(material->Shininess, 1.f, 1.f, 1.f));
		*buffer_cursor += sizeof(v4);

		if (model_data->UseMaterialFile == true) {
			faces_array_ptr++;
		}
		
	}
}
//Note(Marc): This function will use the model's file material
void HexaGridMapMeshV2::PushModelToBuffer(int * buffer_cursor, ModelRawDataV1 * model_data, m4* offset, m4* scale, m4* rotate) {
}

HexaGridMapMeshV2::HexaGridMapMeshV2(GridRawDataV2 * data) :BaseMesh() {
	Grid_Data = data;
}

HexaGridMapMeshV2::~HexaGridMapMeshV2() {
}
int HexaGridMapMeshV2::CalculateRegionVerticesCount() {
	int total_vertices = 0;
	int tile_count = Grid_Data->Grid_size.x*Grid_Data->Grid_size.y;

	int * top_style_cursor = Grid_Data->GetTopStyleArrayPtr();
	for (int grid_index = 0; grid_index < tile_count; grid_index++) {
		total_vertices += Grid_Data->bottom->GetFaceCount()*3;
		total_vertices += Grid_Data->top->GetFaceCount() * 3;
		top_style_cursor++;
	}
	return total_vertices;
}
void HexaGridMapMeshV2::Build() {
	BaseMesh::Build();
	BuildableObject::StartBuilding();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	this->Vertices_Count = CalculateRegionVerticesCount();
	this->Data_Size_Per_vertex = sizeof(v4) + //LOC (0)
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

	//Gen buffer memory
	//*********************************************************************
	glBufferData(GL_ARRAY_BUFFER,
		this->Data_Size_Per_vertex * this->Vertices_Count,
		nullptr, GL_DYNAMIC_DRAW);
	//*********************************************************************


	int* tile_top_style_array = Grid_Data->GetTopStyleArrayPtr();
	int* tile_top_mtl_array = Grid_Data->GetTopMaterialPtr();
	int* tile_bottom_mtl_array = Grid_Data->GetBottomMaterialPtr();

	m4 scale_matrix = m4(1.f);
	m4 translate_matrix = m4(1.f);
	m4 rotate_matrix = m4(1.f);

	int data_buffer_cursor = 0; //Note(Marc): Main buffer cursor
	
	int tile_count = Grid_Data->Grid_size.x*Grid_Data->Grid_size.y;
	for (int grid_index = 0; grid_index < tile_count; grid_index++) {
		ModelRawDataV1 *bottom_model = Grid_Data->bottom;
		ModelRawDataV1 *top_model = Grid_Data->top;
		MaterielRawData * current_top_mtl = nullptr;
		MaterielRawData * current_bottom_mtl = nullptr;
		if (tile_top_mtl_array[grid_index] != 0) {
			current_top_mtl = Grid_Data->mtl_file->FindByNameId(tile_top_mtl_array[grid_index]);
		}
		if (tile_bottom_mtl_array[grid_index] != 0) {
			current_bottom_mtl = Grid_Data->mtl_file->FindByNameId(tile_bottom_mtl_array[grid_index]);
		}
		if (tile_top_style_array[grid_index] != 0) {
			
		}
		translate_matrix = glm::translate(m4(1.f), v3(Grid_Data->grid_pos_data[grid_index].x, Grid_Data->grid_pos_data[grid_index].y, 0.f));
		scale_matrix = glm::scale(m4(1.f), v3(1.f, 1.f, Grid_Data->grid_height_data[grid_index])); //Z = tile height
		rotate_matrix = glm::rotate(m4(1.f), 0.f, v3(0.f, 0.f, 1.f));		
		PushModelToBuffer(&data_buffer_cursor, bottom_model, current_bottom_mtl,&translate_matrix, &scale_matrix,&rotate_matrix);

	
		translate_matrix = glm::translate(m4(1.f), v3(Grid_Data->grid_pos_data[grid_index].x, Grid_Data->grid_pos_data[grid_index].y, Grid_Data->grid_height_data[grid_index]));
		scale_matrix = glm::scale(m4(1.f), v3(1.f, 1.f, 1.f)); //Z = tile height
		rotate_matrix = glm::rotate(m4(1.f), 0.f, v3(0.f, 0.f, 1.f));
		PushModelToBuffer(&data_buffer_cursor, top_model, current_top_mtl, &translate_matrix, &scale_matrix, &rotate_matrix);

	}

	BuildableObject::EndBuilding();
}


