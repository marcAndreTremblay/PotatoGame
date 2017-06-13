#include "stdafx.h"
#include "ModelAtlasFile.h"


ModelAtlasFile::ModelAtlasFile(char *file_path) {
	Atlas_File_Path = new Str(file_path);
	Model_Folder_Path = Str::ExtractFolderPath(Atlas_File_Path);
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


								bottom_tile_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader, Model_Folder_Path->CharAt(0)));
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
								top_tile_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader, Model_Folder_Path->CharAt(0)));
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
						not_found_path = new AtlasModelData(tempo_read_id, lineHeader, Model_Folder_Path->CharAt(0));
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
								
								tile_model_file_path->Add(new AtlasModelData(tempo_read_id, lineHeader, Model_Folder_Path->CharAt(0)));
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

void ModelAtlasFile::LoadRawData() {
	//Model raw data loading
	ListNode<AtlasModelData> *c_node;
	c_node = this->tile_model_file_path->GetHead();
	for (c_node; c_node != nullptr; c_node = c_node->GetNext()) {
		AtlasModelData* current_element = c_node->GetData();
		Str* full_path = new Str("");
		full_path->Append(current_element->folder_path->CharAt(0));
		full_path->Append(current_element->file_name->CharAt(0));
		current_element->data = new ModelRawDataV1();
		current_element->data->LoadFromFile(full_path->CharAt());
	}
	//Tile top raw data loading
	ListNode<AtlasModelData> *c_node2;
	c_node2 = this->top_tile_file_path->GetHead();
	for (c_node2; c_node2 != nullptr; c_node2 = c_node2->GetNext()) {
		AtlasModelData* current_element = c_node2->GetData();
		Str* full_path = new Str("");
			full_path->Append(current_element->folder_path->CharAt(0));
			full_path->Append(current_element->file_name->CharAt(0));
		current_element->data = new ModelRawDataV1();
		current_element->data->LoadFromFile(full_path->CharAt());
	}
}

void ModelAtlasFile::LoadMesh() {
	ListNode<AtlasModelData> *c_node;
	c_node = this->tile_model_file_path->GetHead();
	for (c_node; c_node != nullptr; c_node = c_node->GetNext()) {
		AtlasModelData* current_element = c_node->GetData();
		current_element->mesh = new ModelMeshV1(current_element->data);
		current_element->mesh->Build();
	}
	ListNode<AtlasModelData> *c_node2;
	c_node2 = this->top_tile_file_path->GetHead();
	for (c_node2; c_node2 != nullptr; c_node2 = c_node2->GetNext()) {
		AtlasModelData* current_element = c_node2->GetData();
		current_element->mesh = new ModelMeshV1(current_element->data);
		current_element->mesh->Build();
	}
}

AtlasModelData * ModelAtlasFile::FetchTileModelFilePath(AtlasCategorie categorie, int id) {
	ListNode<AtlasModelData> *c_node;
	switch (categorie) {
		case Tile_Model: { 
			c_node = this->tile_model_file_path->GetHead();
			break; }
		case Tile_Top: {
			c_node = this->top_tile_file_path->GetHead();
			break; }
		case Tile_Bottom: {
			c_node = this->bottom_tile_file_path->GetHead();
			break; }
	default:
		break;
	}

	for (c_node; c_node != nullptr; c_node = c_node->GetNext()) {
		AtlasModelData* current_element = c_node->GetData();
		if (current_element->id == id) {
			return current_element;
		}
	}
	return nullptr;
}
