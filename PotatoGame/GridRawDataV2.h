#if !defined(GRID_RAW_DATA_V2_H)
#define GRID_RAW_DATA_V2_H

#include "Core.h"
#include "String.h"
#include "PGShaderSources.h"
#include "FileMtlRawDataV2.h"
#include "ModelAtlasFile.h"
#include "ModelRawDataV1.h"
using namespace PG::Core;


/*
	File Format :
*/
class GridRawDataV2 {
private:
	Str* mtl_file_path;

	//File data	
		bool* grid_tile_top_model_dynamic_status = nullptr; // 1= dynamic 0 = static
		v3* grid_tile_top_model_scale_data = nullptr;
		r32 * grid_tile_top_model_rotation_data = nullptr;
		r32* grid_tile_top_model_offset_data = nullptr;
	

	//other 
	
public:
	int* GetModelTypeArrayPtr();
	int* GetTopStyleArrayPtr();
	v4* GetPossitionArrayPtr();
	r32* GetHeightArrayPtr();
	int* GetTopMaterialPtr();
	int* GetBottomMaterialPtr();
	
	v2 Grid_size;
	r32 Tile_size;
	v4* grid_pos_data = nullptr;
	r32* grid_height_data = nullptr;
	bool* selected_indexes = nullptr;
	int* grid_tile_top_model_type_data = nullptr;  // 0 = no data
	int* grid_tile_top_style_data = nullptr;// 0= no top 1= flat = 2 = smaler hexa offset+z 
	int* grid_top_material_data = nullptr;
	int* grid_bottom_material_data = nullptr;
	//Todo(Marc): Refactor this to a list or a array and load as much as we need
	//Also add model ref to the region data file so we can look up into the other list	
	ModelRawDataV1* bottom;
	ModelRawDataV1* top;
	FileMtlRawDataV2* mtl_file;
	ModelAtlasFile * model_file;
	void LoadFromFile(char *file_path);
	void SaveToFile(char *file_path);
	v3 CalculateGridOffset();
	GridRawDataV2(v2 grid_size, r32 grid_tile_size);
	GridRawDataV2();
	virtual ~GridRawDataV2();
};
#endif //GRID_RAW_DATA_V2_H

