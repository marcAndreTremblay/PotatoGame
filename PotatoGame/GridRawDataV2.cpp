#include "stdafx.h"
#include "GridRawDataV2.h"


void GridRawDataV2::SaveToFile(char * file_path) {
	printf("Saving to |%s|\n", file_path);
	FILE * file_2 = fopen(file_path, "wb");
	if (file_2 != nullptr) {
		int result = 0;
		result += fwrite(&Grid_size.x, sizeof(float), 1, file_2);
		result += fwrite(&Grid_size.y, sizeof(float), 1, file_2);
		result += fwrite(&Tile_size, sizeof(float), 1, file_2);
		printf("Header write count |%i|\n", result);

		//Todo(MArc):Refactor to tile raw data
		v4* tempo_p_ptr = grid_pos_data;
		r32* tempo_h_ptr = grid_height_data;		
		int* tempo_tile_top_model_type_ptr = grid_tile_top_model_type_data;
			bool* tempo_tile_top_model_dynamic_status_ptr = grid_tile_top_model_dynamic_status; // 1= dynamic 0 = static
			v3* tempo_tile_top_model_scale_ptr = grid_tile_top_model_scale_data;
			r32 * tempo_tile_top_model_rotation_ptr = grid_tile_top_model_rotation_data;
			r32* tempo_tile_top_model_offset_ptr = grid_tile_top_model_offset_data;
		int* tempo_tile_top_style_ptr = grid_tile_top_style_data;
		int* tempo_top_material_ptr = grid_top_material_data;
		int* tempo_bottom_material_ptr = grid_bottom_material_data;
		

		for (int i = 0; i < Grid_size.x*Grid_size.y; i++) {
			result = fwrite((void*)tempo_p_ptr, sizeof(v4), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error possition saving\n", i); }
			tempo_p_ptr++;
			
			result = fwrite((void*)tempo_h_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error height saving\n", i); }
			tempo_h_ptr++;
			
			result = fwrite((void*)tempo_tile_top_model_type_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model type saving\n", i); }
			tempo_tile_top_model_type_ptr++;

			result = fwrite((void*)tempo_tile_top_model_dynamic_status_ptr, sizeof(bool), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model type saving\n", i); }
			tempo_tile_top_model_dynamic_status_ptr++;

			result = fwrite((void*)tempo_tile_top_model_scale_ptr, sizeof(v3), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model scale saving\n", i); }
			tempo_tile_top_model_scale_ptr++;

			result = fwrite((void*)tempo_tile_top_model_rotation_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model rotation saving\n", i); }
			tempo_tile_top_model_rotation_ptr++;

			result = fwrite((void*)tempo_tile_top_model_offset_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model offset saving\n", i); }
			tempo_tile_top_model_offset_ptr++;

			result = fwrite((void*)tempo_tile_top_style_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style saving\n", i); }
			tempo_tile_top_style_ptr++;

			result = fwrite((void*)tempo_top_material_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style saving\n", i); }
			tempo_top_material_ptr++;

			result = fwrite((void*)tempo_bottom_material_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style saving\n", i); }
			tempo_bottom_material_ptr++;

			
			
		}



		fclose(file_2);
	}
	else {
		printf("Error with file saving\n");
	}
}

v3 GridRawDataV2::CalculateGridOffset() 
{
	r32 x_offset = 2.f*glm::cos(glm::radians(30.f));
	r32 y_offset = 1 + glm::sin(glm::radians(30.f));
	return v3(Grid_size.x*x_offset, Grid_size.y*y_offset,0.f);
}

int * GridRawDataV2::GetTopStyleArrayPtr() {
	return &grid_tile_top_style_data[0];
}

v4 * GridRawDataV2::GetPossitionArrayPtr() {
	return &grid_pos_data[0];
}

r32 * GridRawDataV2::GetHeightArrayPtr() {
	return &grid_height_data[0];
}

int * GridRawDataV2::GetTopMaterialPtr() {
	return &grid_top_material_data[0];
}

int * GridRawDataV2::GetBottomMaterialPtr() {
	return &grid_bottom_material_data[0];
}

void GridRawDataV2::LoadFromFile(char * file_path) {
	if (grid_pos_data != nullptr) delete(grid_pos_data);
	if (grid_height_data != nullptr) delete(grid_height_data);
	if (grid_tile_top_model_type_data != nullptr) delete(grid_tile_top_model_type_data);
	if (grid_tile_top_model_dynamic_status != nullptr) delete(grid_tile_top_model_dynamic_status);
	if (grid_tile_top_model_scale_data != nullptr) delete(grid_tile_top_model_scale_data);
	if (grid_tile_top_model_rotation_data != nullptr) delete(grid_tile_top_model_rotation_data);
	if (grid_tile_top_model_offset_data != nullptr) delete(grid_tile_top_model_offset_data);
	if (grid_tile_top_style_data != nullptr) delete(grid_tile_top_style_data);

	if (grid_top_material_data != nullptr) delete(grid_top_material_data);
	if (grid_bottom_material_data != nullptr) delete(grid_bottom_material_data);
	if (selected_indexes != nullptr) delete(selected_indexes);
	
	model_file = new ModelAtlasFile("Asset/Map_Data/Asset/atlas_model_map.txt");
	model_file->LoadFromFile();

	mtl_file = new  FileMtlRawDataV2();
	mtl_file->LoadFromFile("Asset/Map_Data/Asset/atlas_material_map.mtl");

	bottom = new ModelRawDataV1();
	bottom->LoadFromFile("Asset/Map_Data/Asset/tile_bottom2.obj");
	top = new ModelRawDataV1();
	top->LoadFromFile("Asset/Map_Data/Asset/tile_top_type_1.obj");

	printf("Loading | Region |\n");
	printf("\tFile path : %s\n", file_path);
	FILE * file_2 = fopen(file_path, "rb");
	int loaded_element_count = 0;
	if (file_2 != nullptr) {
		
		float x, y, size;
		int result = 0;
		result += fread(&x, sizeof(float), 1, file_2);
		result += fread(&y, sizeof(float), 1, file_2);
		result += fread(&size, sizeof(float), 1, file_2);
		
		Grid_size = v2(x,y);
		Tile_size = size;

		this->grid_pos_data = (v4*)malloc(sizeof(v4)*Grid_size.x*Grid_size.y);
		this->grid_height_data = (r32*)malloc(sizeof(r32)*Grid_size.x*Grid_size.y);

		this->grid_tile_top_model_type_data = (int*)malloc(sizeof(int)*Grid_size.x*Grid_size.y);
		this->grid_tile_top_model_dynamic_status = (bool*)malloc(sizeof(bool)*Grid_size.x*Grid_size.y);
		this->grid_tile_top_model_scale_data = (v3*)malloc(sizeof(v3)*Grid_size.x*Grid_size.y);
		this->grid_tile_top_model_rotation_data = (r32*)malloc(sizeof(r32)*Grid_size.x*Grid_size.y);
		this->grid_tile_top_model_offset_data = (r32*)malloc(sizeof(r32)*Grid_size.x*Grid_size.y);

		this->grid_tile_top_style_data = (int*)malloc(sizeof(int)*Grid_size.x*Grid_size.y);
		this->grid_top_material_data = (int*)malloc(sizeof(int)*Grid_size.x*Grid_size.y);
		this->grid_bottom_material_data = (int*)malloc(sizeof(int)*Grid_size.x*Grid_size.y);

		this->selected_indexes = (bool*)malloc(sizeof(bool)*Grid_size.x*Grid_size.y);

		

		v4* tempo_p_ptr = grid_pos_data;
		r32* tempo_h_ptr = grid_height_data;
		int* tempo_tile_top_model_type_ptr = grid_tile_top_model_type_data;
		bool* tempo_tile_top_model_dynamic_status_ptr = grid_tile_top_model_dynamic_status; // 1= dynamic 0 = static
		v3* tempo_tile_top_model_scale_ptr = grid_tile_top_model_scale_data;
		r32 * tempo_tile_top_model_rotation_ptr = grid_tile_top_model_rotation_data;
		r32* tempo_tile_top_model_offset_ptr = grid_tile_top_model_offset_data;
		int* tempo_tile_top_style_ptr = grid_tile_top_style_data;
		int* tempo_top_material_ptr = grid_top_material_data;
		int* tempo_bottom_material_ptr = grid_bottom_material_data;
		
		for (int i = 0; i < Grid_size.x*Grid_size.y; i++) {
			result = fread((void*)tempo_p_ptr, sizeof(v4), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf("\t %i -- Error possition Reading\n", i); break; }
			tempo_p_ptr++;
			
			result = fread((void*)tempo_h_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf("\t %i -- Error height Reading\n", i); break; }
			tempo_h_ptr++;
		
			result = fread((void*)tempo_tile_top_model_type_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model type Reading\n", i); }
			tempo_tile_top_model_type_ptr++;

			result = fread((void*)tempo_tile_top_model_dynamic_status_ptr, sizeof(bool), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model type Reading\n", i); }
			tempo_tile_top_model_dynamic_status_ptr++;

			result = fread((void*)tempo_tile_top_model_scale_ptr, sizeof(v3), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model scale Reading\n", i); }
			tempo_tile_top_model_scale_ptr++;

			result = fread((void*)tempo_tile_top_model_rotation_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model rotation Reading\n", i); }
			tempo_tile_top_model_rotation_ptr++;

			result = fread((void*)tempo_tile_top_model_offset_ptr, sizeof(r32), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Model offset Reading\n", i); }
			tempo_tile_top_model_offset_ptr++;

			result = fread((void*)tempo_tile_top_style_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style Reading\n", i); }
			tempo_tile_top_style_ptr++;

			result = fread((void*)tempo_top_material_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style Reading\n", i); }
			tempo_top_material_ptr++;

			result = fread((void*)tempo_bottom_material_ptr, sizeof(int), 1, file_2);
			if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Tile top style Reading\n", i); }
			tempo_bottom_material_ptr++;


			loaded_element_count++;

		}
		fclose(file_2);
	}
	else {
		printf("\tError with file loading\n");
	}
	printf("\tElement read count |%i|\n", loaded_element_count);
	
}

GridRawDataV2::GridRawDataV2(v2 grid_size, r32 grid_tile_size) {
	mtl_file = nullptr;
	model_file = nullptr;
	Grid_size = grid_size;
	Tile_size = grid_tile_size;


	mtl_file = new  FileMtlRawDataV2();
	mtl_file->LoadFromFile("Asset/map/asset/base_material.mtl");
	bottom = new ModelRawDataV1();
	bottom->LoadFromFile("Asset/map/asset/tile_bottom2.obj");
	top = new ModelRawDataV1();
	top->LoadFromFile("Asset/map/asset/tile_top_type_1.obj");
	//			o
	//		o		o
	//	o				o
	//	o				o	
	//	o		o		o	
	//	o				o
	//	o				o
	//		o		o		
	//			o
	//			|		|  
	//Note(Marc): We use the bottom left as the starting point 
	//Note(Marc): We go left to right and bottom to top in the world space starting from 0,0,0

	r32 x_offset = glm::cos(glm::radians(30.f));
	v4 major_row_offset = v4(x_offset , 1 + glm::sin(glm::radians(30.f)), 0.f, 0.f);
	v4 minor_row_offset = v4( -x_offset, 1 + glm::sin(glm::radians(30.f)), 0.f, 0.f);

	v4 starting_offset = v4(0.f, 0, 0.f, 0.f); //Note(Marc): Offset for the starting possition


	this->grid_pos_data = (v4*)malloc(sizeof(v4)*grid_size.x*grid_size.y);
	this->grid_height_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);

	this->grid_tile_top_model_type_data = (int*)malloc(sizeof(int)*grid_size.x*grid_size.y);
		this->grid_tile_top_model_dynamic_status = (bool*)malloc(sizeof(bool)*grid_size.x*grid_size.y);
		this->grid_tile_top_model_scale_data = (v3*)malloc(sizeof(v3)*grid_size.x*grid_size.y);
		this->grid_tile_top_model_rotation_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);
		this->grid_tile_top_model_offset_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);

		this->grid_tile_top_style_data = (int*)malloc(sizeof(int)*grid_size.x*grid_size.y);
	this->grid_top_material_data = (int*)malloc(sizeof(int)*grid_size.x*grid_size.y);
	this->grid_bottom_material_data = (int*)malloc(sizeof(int)*grid_size.x*grid_size.y);

	this->selected_indexes = (bool*)malloc(sizeof(bool)*grid_size.x*grid_size.y);

	int index_cpt = 0;
	for (int y_xpt = 0; y_xpt < grid_size.y; y_xpt++) {
		v4 row_start_tempo = starting_offset;
		for (int x_xpt = 0; x_xpt < grid_size.x; x_xpt++) {


			
			grid_pos_data[index_cpt] = starting_offset;
			grid_height_data[index_cpt] = 2 + 1.3f*sin(y_xpt / 2.5f)*cos(x_xpt / 2.5f);
			
			grid_tile_top_model_type_data[index_cpt] = 0;
				grid_tile_top_model_dynamic_status[index_cpt] = false;
				grid_tile_top_model_scale_data[index_cpt] = v3();
				grid_tile_top_model_rotation_data[index_cpt] = 0.f;
				grid_tile_top_model_offset_data[index_cpt] = 0.f;

				grid_tile_top_style_data[index_cpt] = 1.f;
				grid_top_material_data[index_cpt] = 1;
				grid_bottom_material_data[index_cpt] = 2;
				selected_indexes[index_cpt] = false;
				
				starting_offset.x += x_offset*2.f;
			index_cpt++;
		}
		starting_offset = row_start_tempo;
		if (y_xpt % 2 == 0) {//If pair
			starting_offset += major_row_offset;
		}
		else {
			starting_offset += minor_row_offset;
		}
	}
}

GridRawDataV2::GridRawDataV2() {
	mtl_file = nullptr;
	model_file = nullptr;
}


GridRawDataV2::~GridRawDataV2() {
	delete(bottom);
	delete(top);
	
	delete(this->grid_pos_data);
	delete(this->grid_height_data);

	delete(this->grid_tile_top_model_type_data);
	delete(this->grid_tile_top_model_dynamic_status);
	delete(this->grid_tile_top_model_scale_data);
	delete(this->grid_tile_top_model_rotation_data);
	delete(this->grid_tile_top_model_offset_data);

	delete(this->grid_tile_top_style_data);
	delete(this->grid_top_material_data );
	delete(this->grid_bottom_material_data);

	delete(this->selected_indexes);
	delete(this->mtl_file);
	delete(this->model_file);
}
