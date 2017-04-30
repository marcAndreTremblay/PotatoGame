#include "stdafx.h"
#include "FileMtlRawDataV2.h"


FileMtlRawDataV2::FileMtlRawDataV2() {
	RawMateriels = new List<MaterielRawData>(true);
	File_Path = nullptr;
}


FileMtlRawDataV2::~FileMtlRawDataV2() {
	delete(RawMateriels);
	delete(File_Path);
}

//Todo(Marc): Add another parameter (ptr List) for when you want to also add the individual of each file when loading from several mtl file
void FileMtlRawDataV2::LoadFromFile(char * _file_path) {
	printf("Loading | Mtl file | Start\n");

	File_Path = new Str(_file_path);
	printf("\tFile path : %s\n", File_Path->CharAt());
	FILE * file = fopen(File_Path->CharAt(), "rb");
	MaterielRawData *last_new_mat;
	int id = 0; if (file != nullptr) {
		char lineHeader[128];
		while (1) {
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			else if (strcmp(lineHeader, "newmtl") == 0) {
				int match_cpt = fscanf(file, "%s", lineHeader);


				char *path = new char[254];
				sprintf(&path[0], "%s\n", lineHeader);

				last_new_mat = nullptr;
				last_new_mat = new MaterielRawData(path, id);
				id = id + 1;
				RawMateriels->Add(last_new_mat);
				if (match_cpt != 1) {
					printf("Error reading mat name |\n");
				}
				else {
					printf("\tMaterial name : %s", last_new_mat->Name->CharAt());
				}
			}
			else if (strcmp(lineHeader, "Count:") == 0) {
				int match_cpt = fscanf_s(file, " %i", &Material_Count);
				if (match_cpt != 1) {
					printf("Error reading mat count |\n");
				}
				else{
					printf("\tFile Contain : %i Individual material\n", Material_Count);
				}
			}
			else if (strcmp(lineHeader, "Ns") == 0) {
				int match_cpt = fscanf_s(file, " %f", &last_new_mat->Shininess);
				if (match_cpt != 1) {
					printf("Error reading alpha |\n");
				}
				else {
					printf("\t\tMaterial Shininess : %f\n", last_new_mat->Shininess);
				}
			}
			else if (strcmp(lineHeader, "Ke") == 0) {
				v3 *c_data = &last_new_mat->Ambient;
				int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);
				if (match_cpt != 3) {
					printf("Error reading ka |\n");
				}
				else {
					printf("\t\tMaterial Ambiant : %f,%f,%f \n", last_new_mat->Ambient.x, last_new_mat->Ambient.y, last_new_mat->Ambient.z);
				}
			}
			else if (strcmp(lineHeader, "Kd") == 0) {
				v3 *c_data = &last_new_mat->Diffuse;
				int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);
				if (match_cpt != 3) {
					printf("Error reading kd |\n");
				}
				else {
					printf("\t\tMaterial Diffuse : %f,%f,%f \n", last_new_mat->Diffuse.x, last_new_mat->Diffuse.y, last_new_mat->Diffuse.z);
				}
			}
			else if (strcmp(lineHeader, "Ks") == 0) {
				v3 *c_data = &last_new_mat->Specular;
				int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);
				if (match_cpt != 3) {
					printf("Error reading k |\n");
				}
				else {
					printf("\t\tMaterial Specular : %f,%f,%f \n", last_new_mat->Specular.x, last_new_mat->Specular.y, last_new_mat->Specular.z);
				}
			}


		}
	}
	fclose(file);
	printf("Loading | Mtl file | End\n");
}

MaterielRawData * FileMtlRawDataV2::FindByNameRef(char * name) {
	for (ListNode<MaterielRawData> *c_node = this->RawMateriels->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
		MaterielRawData* current_element = c_node->GetData();
		if (current_element->Name->Compare(new Str(name)) == true) {
			return current_element;
		}
	}
	return nullptr;
}

MaterielRawData * FileMtlRawDataV2::FindByNameId(int target_id) {
	for (ListNode<MaterielRawData> *c_node = this->RawMateriels->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
		MaterielRawData* current_element = c_node->GetData();
		if (current_element->Id == target_id) {
			return current_element;
		}
	}
	return nullptr;
}
