#if !defined(PG_MAP_ATLAS_H)
#define PG_MAP_ATLAS_H


#include "stdafx.h"
#include "String.h"
#include "PGMapGrid.h"
#include "List.h"

class PGAtlasRegion {
	int Grid_Index; 
	bool IsLoaded;
	bool ShouldUnload;
	Str *FilePath;
	PGGridRawData *grid;
public:
	PGAtlasRegion(int index, Str *name) {
		FilePath = name;
		Grid_Index = index;
		IsLoaded = false;
		ShouldUnload = false;
		grid = nullptr;
	}
	~PGAtlasRegion() {
		delete(grid);
	}

};
class PGMapAtlas {
public:
	int size_X, size_Y;
	
	List<PGAtlasRegion> *Regions;
	Str *regions_file_folder;
	Str *Atlas_File_Path;

	PGMapAtlas(char *file_path) {	
		Atlas_File_Path = new Str(file_path);
		regions_file_folder = Str::ExtractFolderPath(Atlas_File_Path);

		Regions = new List<PGAtlasRegion>(true);
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
						Regions->Add(new PGAtlasRegion(data1, new Str(lineHeader)));
					}
				}

			}
		
		}
	}
	~PGMapAtlas() {
		delete(Regions);
	}
};

#endif