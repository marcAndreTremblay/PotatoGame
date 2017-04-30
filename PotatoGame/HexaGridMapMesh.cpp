#include "stdafx.h"
#include "HexaGridMapMesh.h"


HexaGridMapMesh::HexaGridMapMesh(PGGridRawData *_grid_data) : BaseMesh() {
	grid_data = _grid_data;
}
HexaGridMapMesh::~HexaGridMapMesh() {

}
v3 HexaGridMapMesh::ReadVector3(const GLfloat* target) {
	v3 vec = {};
	vec.x = *target;
	target++;
	vec.y = *target;
	target++;
	vec.z = *target;
	target++;
	return vec;
}
void HexaGridMapMesh::Build() {
	BaseMesh::Build();


	//Build the Vao buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	//Note(Marc):	This is a solution for rendering bottleneck for back ground with
	//					this we could easily add environment vertex
	int face_count = 17;
	int vertex_per_face = 3;
	int per_model_vertex = face_count*vertex_per_face; //Hexagone mesh , maybe we should centralize mesh data like ths
	v2 grid_size = grid_data->Grid_size;
	int element_count = grid_size.x*grid_size.y;
	int  per_vertex_data_lenght =
		sizeof(v4) + //LOC (0)
		sizeof(v3) + //LOC (1)
		sizeof(v3) + //LOC (2)
		sizeof(v3) + //LOC (3)
		sizeof(v3) + //LOC (4)
		sizeof(v4); //LOC (5)

	
	this->Vertices_Count = per_vertex_data_lenght *per_model_vertex*element_count;
	glBufferData(GL_ARRAY_BUFFER, per_vertex_data_lenght *per_model_vertex*element_count, nullptr, GL_DYNAMIC_DRAW);
	int data_buffer_cursor = 0;

	m4 scale_matrix = m4(1.f);
	m4 translate_matrix = m4(1.f);
	for (int grid_index = 0; grid_index< element_count; grid_index++) {
		PGMaterial* current_mat = &grid_data->grid_material_data[grid_index];
		translate_matrix = glm::translate(m4(1.f), v3(grid_data->grid_pos_data[grid_index].x, grid_data->grid_pos_data[grid_index].y, 0.f));
		scale_matrix = glm::scale(m4(1.f), v3(1.f, 1.f, grid_data->grid_height_data[grid_index])); //Z = tile height
		int EBO_index = 0;

		for (int i = 0; i < face_count; i++) {
			//Retrive the 3 surface's point
			v3 point[3] = {};
			point[0] = this->ReadVector3(&hexagone_vertex_data_v3_2[hexagone_indice_data_2[EBO_index] * 3]);
			point[1] = this->ReadVector3(&hexagone_vertex_data_v3_2[hexagone_indice_data_2[EBO_index + 1] * 3]);
			point[2] = this->ReadVector3(&hexagone_vertex_data_v3_2[hexagone_indice_data_2[EBO_index + 2] * 3]);
			v3 vec_U = point[0] - point[1];
			v3 vec_V = point[2] - point[1];
			v3 face_normal = glm::normalize(glm::cross(vec_V, vec_U));
			for (int c = 0; c < vertex_per_face; c++) {
				v4 posstion_world_space = translate_matrix*scale_matrix*v4(point[c], 1.f);
				//Possition world space
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v4), &posstion_world_space);
				data_buffer_cursor += sizeof(v4);
				//Normal
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &face_normal);
				data_buffer_cursor += sizeof(v3);
				//Material info
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->ambient); //Note dont know bender
				data_buffer_cursor += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->diffuse);
				data_buffer_cursor += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->specular);
				data_buffer_cursor += sizeof(v3);
				glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v4), &v4(current_mat->shininess, 1.f, 1.f, 1.f));
				data_buffer_cursor += sizeof(v4);

			}
			EBO_index += vertex_per_face;
		}
	}

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4) + sizeof(v3)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4) + 2 * sizeof(v3)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4) + 3 * sizeof(v3)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4) + 4 * sizeof(v3)));
	glEnableVertexAttribArray(5);
	glBindVertexArray(0);
	BuildableObject::EndBuilding();


}

