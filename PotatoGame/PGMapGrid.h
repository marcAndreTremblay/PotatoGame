#if !defined(PG_MAP_GRID_H)
#define PG_MAP_GRID_H

#include "PGCore.h"
#include "PGBaseRenderer.h"
using namespace PGCore;





class NodeLink {
public:
	int Value;
	void * Next_Node;
	NodeLink() {
		Value = 0;
		Next_Node = nullptr;
	}
	NodeLink(void* next_node, int value) {
		this->Next_Node = next_node;
		this->Value = value;
	}
	~NodeLink() {
	}
};
class MapNode {
public:
	int Index;
	float Height; //Note(Marc) : Maybe we should not keep this in here , instead calculte the node_link value with it
	NodeLink link_array[5]; //Note(Marc): don't know if this should be dynamic , will help if this stay static for speed
	MapNode() {
		Index = -1;
		Height = 0;
	}
	MapNode(int node_index, float node_height) {
		this->Index = node_index;
		this->Height = node_height;
	}
	~MapNode() {

	}
};

class MapPathGraph {
public:
	MapNode * node_array;
	MapPathGraph(int array_size, int stride, r32* height_array) {
		this->node_array = (MapNode*)malloc(sizeof(MapNode)*array_size);
		
		// Step 1  : Build all nodes
		for (int i = 0; i < array_size; i++) {
			node_array[i].Height = height_array[i];
			node_array[i].Index = i;
		}
		// Step 2 : Build all links
		for (int i = 0; i < array_size; i++) {
			if (node_array[i].Index - 1 >= 0) {
				
			}
			if (node_array[i].Index + 1 < array_size) {

			}
		}

	}
	~MapPathGraph() {
		delete(node_array);
	}
};

class PGGridRawData {
public:
	v4* grid_pos_data = nullptr;
	r32* grid_height_data = nullptr;
	PGMaterial* grid_material_data = nullptr;
	bool* selected_indexes = nullptr;

	v2 Grid_size;
	r32 Tile_size;
	PGGridRawData() {
		Grid_size = v2(0, 0);
		Tile_size = 0;

	}
	PGGridRawData(v2 grid_size, r32 grid_tile_size) {
		Grid_size = grid_size;
		Tile_size = grid_tile_size;

		//			o
		//		o		o
		//	o				o
		//	o				o	
		//	o		o		o	
		//	o				o
		//	o				o
		//		o		o		
		//			o
		//Note(Marc): We use the bottom left as the starting point 
		//Note(Marc): We go left to right and bottom to top in the world space starting from 0,0,0
		v4 major_row_offset = v4(grid_tile_size, (2 * grid_tile_size) - (grid_tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);
		v4 minor_row_offset = v4(-grid_tile_size, (2 * grid_tile_size) - (grid_tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);

		v4 starting_offset = v4(0.f, 0, 0.f, 0.f); //Note(Marc): Offset for the starting possition

		this->grid_pos_data = (v4*)malloc(sizeof(v4)*grid_size.x*grid_size.y);
		this->grid_height_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);
		this->grid_material_data = (PGMaterial*)malloc(sizeof(PGMaterial)*grid_size.x*grid_size.y);
		this->selected_indexes = (bool*)malloc(sizeof(bool)*grid_size.x*grid_size.y);


		int index_cpt = 0;
		for (int y_xpt = 0; y_xpt < grid_size.y; y_xpt++) {
			v4 row_start_tempo = starting_offset;
			for (int x_xpt = 0; x_xpt < grid_size.x; x_xpt++) {


				starting_offset.x += grid_tile_size*2.f;
				grid_pos_data[index_cpt] = starting_offset;
				grid_height_data[index_cpt] = 2 + 1.3f*sin(y_xpt / 2.5f)*cos(x_xpt / 2.5f);
				grid_material_data[index_cpt] = Material_Brown_1;
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
	~PGGridRawData() {
		delete(grid_pos_data);
		delete(grid_height_data);
		delete(grid_material_data);
		delete(selected_indexes);
	}
	void SaveToFile(char *file_path) {
		printf("Saving to |%s|\n", file_path);
		FILE * file_2 = nullptr;
		fopen_s(&file_2, file_path, "wb");

		if (file_2 != nullptr) {
			int result = 0;
			result += fwrite(&Grid_size.x, sizeof(float), 1, file_2);
			result += fwrite(&Grid_size.y, sizeof(float), 1, file_2);
			result += fwrite(&Tile_size, sizeof(float), 1, file_2);
			printf("Header write count |%i|\n", result);

			v4* tempo_p_ptr = grid_pos_data;
			r32* tempo_h_ptr = grid_height_data;
			PGMaterial* tempo_m_ptr = grid_material_data;
			for (int i = 0; i < Grid_size.x*Grid_size.y; i++) {
				result = fwrite((void*)tempo_p_ptr, sizeof(v4), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error possition saving\n", i); }
				result = fwrite((void*)tempo_h_ptr, sizeof(r32), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error height saving\n", i); }
				result = fwrite((void*)tempo_m_ptr, sizeof(PGMaterial), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error material saving\n", i); }
				tempo_h_ptr++;
				tempo_p_ptr++;
				tempo_m_ptr++;
			}



			fclose(file_2);
		}
		else {
			printf("Error with file saving\n");
		}

	}
	void LoadFromFile(char *file_path) {
		if (grid_pos_data != nullptr) delete(grid_pos_data);
		if (grid_height_data != nullptr) delete(grid_height_data);
		printf("Loading from |%s|\n", file_path);
		FILE * file_2 = fopen(file_path, "rb");
		if (file_2 != nullptr) {
			float x, y, size;
			int result = 0;
			result += fread(&x, sizeof(float), 1, file_2);
			result += fread(&y, sizeof(float), 1, file_2);
			result += fread(&size, sizeof(float), 1, file_2);

			printf("Header read count |%i|\n", result);


			this->Tile_size = size;
			this->Grid_size = v2(x, y);

			this->grid_pos_data = (v4*)malloc(sizeof(v4)*x*y);
			this->grid_height_data = (r32*)malloc(sizeof(r32)*x*y);
			this->grid_material_data = (PGMaterial*)malloc(sizeof(PGMaterial)*x*y);
			this->selected_indexes = (bool*)malloc(sizeof(bool)*x*y);

			int loaded_element_count = 0;

			v4* tempo_p_ptr = grid_pos_data;
			r32* tempo_h_ptr = grid_height_data;
			PGMaterial* tempo_m_ptr = grid_material_data;
			for (int i = 0; i < Grid_size.x*Grid_size.y; i++) {
				result = fread((void*)tempo_p_ptr, sizeof(v4), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error possition reading\n", i); break; }
				result = fread((void*)tempo_h_ptr, sizeof(r32), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error height reading\n", i); break; }
				result = fread((void*)tempo_m_ptr, sizeof(PGMaterial), 1, file_2);
				if (ferror(file_2) != 0 || result != 1) { printf(" %i -- Error material reading\n", i); break; }
				loaded_element_count++;
				tempo_h_ptr++;
				tempo_p_ptr++;
				tempo_m_ptr++;
			}



			printf("Element read count |%i|\n", loaded_element_count);
			fclose(file_2);
		}
		else {
			printf("Error with file loading\n");
		}
	}
	void GenerateGridPossitionData(v3 offset) {
		v4 major_row_offset = v4(this->Tile_size, (2 * this->Tile_size) - (this->Tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);
		v4 minor_row_offset = v4(-this->Tile_size, (2 * this->Tile_size) - (this->Tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);
		v4 starting_offset = v4(offset, 0.f);
		int index_cpt = 0;
		for (int y_xpt = 0; y_xpt < this->Grid_size.y; y_xpt++) {
			v4 row_start_tempo = starting_offset;
			for (int x_xpt = 0; x_xpt < this->Grid_size.x; x_xpt++) {
				grid_pos_data[index_cpt] = starting_offset;
				starting_offset.x += this->Tile_size*2.f;
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
	void GenGraphPath() {
		MapPathGraph* graph = new MapPathGraph(this->Grid_size.x*this->Grid_size.y, this->Grid_size.x, &grid_height_data[0]);

	}
};




#endif