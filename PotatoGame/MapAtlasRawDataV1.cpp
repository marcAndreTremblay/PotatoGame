#include "stdafx.h"
#include "MapAtlasRawDataV1.h"




//*************************************************************************
MapAtlasRawDataV1::MapAtlasRawDataV1(char *file_path) {
	Regions = new List<MapAtlasRegion>(true);
	Atlas_File_Path = new Str(file_path);
	regions_file_folder = Str::ExtractFolderPath(Atlas_File_Path);
}

MapAtlasRawDataV1::~MapAtlasRawDataV1() {
	delete(Regions);
	//delete(regions_file_folder); //Todo(Marc): Redo the extract Folder_path from file path
	delete(Atlas_File_Path);
}
void MapAtlasRawDataV1::LoadFromFile() {
	printf("Loading Atlas : %s \n", Atlas_File_Path->CharAt());
	FILE * file = fopen(Atlas_File_Path->CharAt(), "rb");
	if (file != nullptr) {
		char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
		while (1) {
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			if (strcmp(lineHeader, "ModelFile") == 0) {
				char tempo_buffer[254];
				fscanf(file, "%s", tempo_buffer);
				Model_File_Path = new Str(tempo_buffer);
				printf("\tModel file : %s \n", Model_File_Path->CharAt());
			}
			if (strcmp(lineHeader, "MaterialFile") == 0) {
				char tempo_buffer[254];
				fscanf(file, "%s", tempo_buffer);
				Material_File_Path = new Str(tempo_buffer);
				printf("\tMtl file : %s \n", Material_File_Path->CharAt());
				
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
MapAtlasRegion * MapAtlasRawDataV1::GetRegionByRefIndex(int s_index) {
	for (ListNode<MapAtlasRegion> *c_node = Regions->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
		MapAtlasRegion* c_region = c_node->GetData();
		if (c_region->Grid_Index == s_index) {
			return c_region;
		}
	}
	return nullptr;
}
//*************************************************************************
MapAtlasRegion::MapAtlasRegion(int index, Str *name) {
	File_Path = name;
	Grid_Index = index;
	IsLoaded = false;
	ShouldUnload = false;
	file_data = nullptr;
	region_mesh = nullptr;
}

MapAtlasRegion::~MapAtlasRegion() {
	FreeData();
	delete(File_Path);

}

void MapAtlasRegion::LoadFromFile() {
	if (IsLoaded == false) {
		file_data = new GridRawDataV2();
		file_data->LoadFromFile(File_Path->CharAt(0));

		region_mesh = new HexaGridMapMeshV2(file_data);
		region_mesh->Build();
		IsLoaded = true;
	}
	else {
		//Note(Marc): Maybe clear vao apart from
	}
}

void MapAtlasRegion::FreeData() {
	delete(file_data);
	delete(region_mesh);
	this->IsLoaded = false;
}
