#if !defined(MAP_ATLAS_RAW_DATA_V1_H)
#define MAP_ATLAS_RAW_DATA_V1_H


#include "stdafx.h"
#include "String.h"
#include "List.h"
using namespace PG::Core;

#include "GridRawDataV2.h"
#include "HexaGridMapMeshV2.h"

class MapAtlasRegion {
private :
	bool IsLoaded;
	bool ShouldUnload;
public:
	Str *File_Path;
	int Grid_Index;
	GridRawDataV2* file_data;
	HexaGridMapMeshV2* region_mesh;
	MapAtlasRegion(int index, Str *name);
	virtual ~MapAtlasRegion();
	void LoadFromFile();
	void FreeData();
};
class MapAtlasRawDataV1 {
	int size_X, size_Y;
	
	Str *Material_File_Path;
	FileMtlRawDataV2* Material_file;
	
	Str *Model_File_Path;
	Str *Atlas_File_Path;
	List<MapAtlasRegion> *Regions;
	Str *regions_file_folder;
	
public:
	   MapAtlasRawDataV1(char *file_path);
	virtual ~MapAtlasRawDataV1();
	void LoadFromFile();
	MapAtlasRegion* GetRegionByRefIndex(int s_index);
	void LoadRegionsAndFillDisplayTemplate(int world_index, MapAtlasRegion** out_regions_array) {
		int index[9];
		index[0] = { world_index - size_X - 1 }; //Bottom left
		index[1] = { world_index - size_X };
		index[2] = { world_index - size_X + 1 };
		index[3] = { world_index - 1 };
		index[4] = { world_index };
		index[5] = { world_index + 1 };
		index[6] = { world_index + size_X - 1 };
		index[7] = { world_index + size_X };
		index[8] = { world_index + size_X + 1 };
		for (int i = 0; i < 9; i++) {
			out_regions_array[i] = GetRegionByRefIndex(index[i]);
			if (out_regions_array[i] != nullptr) {
				out_regions_array[i]->LoadFromFile();
			}
		}
	}
};
#endif //MAP_ATLAS_RAW_DATA_V1_H

