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

	List<MapAtlasRegion> *Regions;
	Str *regions_file_folder;
	Str *Atlas_File_Path;
public:
	   MapAtlasRawDataV1(char *file_path);
	virtual ~MapAtlasRawDataV1();
	void LoadFromFile() {
		printf("Loading Atlas : %s \n", Atlas_File_Path->CharAt());
		FILE * file = fopen(Atlas_File_Path->CharAt(), "rb");
		if (file != nullptr) {
			char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
			while (1) {
				int res = fscanf(file, "%s", lineHeader);
				if (res == EOF) {
					break; // EOF = End Of File. Quit the loop.
				}
				if (strcmp(lineHeader, "RegionCount") == 0) {
					//Rend int
					int data;
					int res = fscanf(file, "%i", &data);
					if (res != 1) {
						printf("\tAtlas : Error can't read region count\n");
					}
					else {
						printf("\tAtlas : Region count : %i\n", data);
					}
				}
				else if (strcmp(lineHeader, "MapSize") == 0) {
					//Rend 2 int
					int res = fscanf(file, "%i %i", &size_X, &size_Y);
					if (res != 2) {
						printf("\tAtlas : Error can't read map layout size\n");
					}
					else {
						printf("\tAtlas : Map layout size (%i,%i)\n", size_X, size_Y);
					}
				}
				else if (strcmp(lineHeader, "Id") == 0) {
					//Rend 2 int
					int data1;
					int res = fscanf(file, "%i", &data1);
					res += fscanf(file, "%s", lineHeader);

					if (res != 2) {
						printf("\tAtlas : Error can't read map layout size\n");
					}
					else {
						printf("\tAtlas : Id : %i |%s|\n", data1, lineHeader);
						Str *path = new Str("");
						Regions->Add(new MapAtlasRegion(data1, path->Append(regions_file_folder->CharAt())->Append(lineHeader)));
					}
				}

			}

		}
	}
	MapAtlasRegion* GetRegionByRefIndex(int s_index) {
		for (ListNode<MapAtlasRegion> *c_node = Regions->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			MapAtlasRegion* c_region = c_node->GetData();
			if (c_region->Grid_Index == s_index) {
				return c_region;
			}
		}
		return nullptr;
	}
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

