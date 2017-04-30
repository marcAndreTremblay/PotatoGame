#if !defined(GRID_RAW_DATA_V2_H)
#define GRID_RAW_DATA_V2_H

#include "Core.h"
#include "PGShaderSources.h"
#include "FileMtlRawDataV2.h"
using namespace PG::Core;

class GridRawDataV2 {
private:
	//Header
	v2 Grid_size;
	r32 Tile_size;

	Str* mtl_file_path;
	
	//File data
	v4* grid_pos_data = nullptr;
	r32* grid_height_data = nullptr;

	int* grid_tile_top_model_type_data = nullptr;  // 0 = no data
		bool* grid_tile_top_model_dynamic_status = nullptr; // 1= dynamic 0 = static
		v3* grid_tile_top_model_scale_data = nullptr;
		r32 * grid_tile_top_model_rotation_data = nullptr;
		r32* grid_tile_top_model_offset_data = nullptr;

	int* grid_tile_top_style_data = nullptr;// 0= no top 1= flat = 2 = smaler hexa offset+z 		
	PGMaterial* grid_top_material_data = nullptr;
	PGMaterial* grid_bottom_material_data = nullptr;
	//other 
	bool* selected_indexes = nullptr;
	FileMtlRawDataV2* mtl_file;
public:
	void LoadFromFile(char *file_path);
	void SaveToFile(char *file_path);
	GridRawDataV2(v2 grid_size, r32 grid_tile_size);
	GridRawDataV2();
	virtual ~GridRawDataV2();
};
#endif //GRID_RAW_DATA_V2_H

