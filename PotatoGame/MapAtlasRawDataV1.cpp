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
	delete(regions_file_folder);
	delete(Atlas_File_Path);
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
