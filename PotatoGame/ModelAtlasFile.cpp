#include "stdafx.h"
#include "ModelAtlasFile.h"


ModelAtlasFile::ModelAtlasFile(char *file_path) {
	Atlas_File_Path = new Str(file_path);
	tile_model_file_path = new List<AtlasModelData>(true);
	bottom_tile_file_path = new List<AtlasModelData>(true);
	top_tile_file_path = new List<AtlasModelData>(true);

}


ModelAtlasFile::~ModelAtlasFile() {
	delete(tile_model_file_path);
	delete(bottom_tile_file_path);
	delete(top_tile_file_path);
}

void ModelAtlasFile::LoadFromFile() {
	printf("Loading | Model Atlas file | Start\n");
	FILE * file = fopen(Atlas_File_Path->CharAt(), "rb");
	if (file != nullptr) {
		char lineHeader[128];
		char tempo_file_name_buffer[128];
		int tempo_read_id;
		while (1) {
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			else 
				if (strcmp(lineHeader, "[TILE_BOTTOM]") == 0) {
					int res = fscanf(file, "%s", lineHeader);
					if (strcmp(lineHeader, "Count:") == 0) {
						int tempo_int;
						int match_cpt = fscanf(file, " %i", &tempo_int);
						for (int i = 1; i <= tempo_int; i++) {
							int match_cpt1 = fscanf(file, "%i", &tempo_read_id);
							int match_cpt2 = fscanf(file, "%s", &lineHeader);
							if (match_cpt1 == 1 && match_cpt2 == 1) {
								bottom_tile_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader));
							}
							else {
								//Todo(marc): addd debug model line info format dosn't match id:file_name.obj
							}
						}
					}
					else {
						// File format missing paths count
					}
				}
			else
				if (strcmp(lineHeader, "[TILE_TOP]") == 0) {
					int res = fscanf(file, "%s", lineHeader);
					if (strcmp(lineHeader, "Count:") == 0) {
						int tempo_int;
						int match_cpt = fscanf(file, " %i", &tempo_int);
						for (int i = 1; i <= tempo_int; i++) {
							int match_cpt1 = fscanf(file, "%i", &tempo_read_id);
							int match_cpt2 = fscanf(file, "%s", &lineHeader);
							if (match_cpt1 == 1 && match_cpt2 == 1) {
								top_tile_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader));
							}
							else {
								//Todo(marc): addd debug model line info format dosn't match id:file_name.obj
							}
						}
					}
					else {
						// File format missing paths count
					}
				}
			else
				if (strcmp(lineHeader, "[NOT_FOUND]") == 0) {
					int match_cpt1 = fscanf(file, "%i", &tempo_read_id);
					int match_cpt2 = fscanf(file, "%s", &lineHeader);
					if (match_cpt1 == 1 && match_cpt2 == 1) {
						not_found_path = new AtlasModelData(tempo_read_id, lineHeader);
					}
				}
			else
				if (strcmp(lineHeader, "[TILE_MODEL]") == 0) {
					int res = fscanf(file, "%s", lineHeader);
					if (strcmp(lineHeader, "Count:") == 0) {
						int tempo_int;
						int match_cpt = fscanf(file, " %i", &tempo_int);
						
						for (int i = 1; i <= tempo_int; i++) {
							int match_cpt1 = fscanf(file, "%i", &tempo_read_id);
 							int match_cpt2 = fscanf(file, "%s", &lineHeader);
							if (match_cpt1 == 1 && match_cpt2 == 1) {
								tile_model_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader));
							}
							else {
								//Todo(marc): addd debug model line info format dosn't match id:file_name.obj
							}
							
						}
					}
					else {
						// File format missing paths count
					}
				}
		}
	}
	else {
		/*Add debug stuff*/
	}
	printf("Loading | Model Atlas file | End\n");
}
