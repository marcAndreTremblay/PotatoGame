#include "stdafx.h"
#include "ModelRawDataV1.h"


int ModelRawDataV1::GetFaceCount() {
	return face_count;
}

unsigned int * ModelRawDataV1::GetFacesArrayPtr() {
	return &faces_array[0];
}

v3 * ModelRawDataV1::GetVertivesArrayPtr() {
	return &vertices_array[0];
}

v2 * ModelRawDataV1::GetUVSArrayPtr() {
	return &uvs_array[0];
}

v3 * ModelRawDataV1::GetNormalsArrayPtr() {
	return &normal_array[0];
}

ModelRawDataV1::ModelRawDataV1() {
	v_count = 0;
	vn_count = 0;
	vt_count = 0;
	face_count = 0;
	vertices_array = nullptr;
	uvs_array = nullptr;
	normal_array = nullptr;
	faces_array = nullptr;
	UseMaterialFile = false;
	file_path = nullptr;
	forlder_path = nullptr;
	mtl_file = nullptr;
	UseTextureMap = false;
}


ModelRawDataV1::~ModelRawDataV1() {
	delete(vertices_array);
	delete(uvs_array);
	delete(normal_array);
	delete(faces_array);
	
	delete(file_path);
	delete(mtl_file);
//	delete(forlder_path);
}

void ModelRawDataV1::LoadFromFile(char * _file_path) {
	file_path = new Str(_file_path);
	forlder_path = Str::ExtractFolderPath(file_path);
	FILE * file1 = fopen(file_path->CharAt(), "rb");
	printf("Loading | Model | :\n");
	printf("\tFile path %s \n", file_path->CharAt());
	printf("\tFolder path %s \n", forlder_path->CharAt());

	//First file pass for counting and checking data

	if (file1 != nullptr) {
		char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
		while (1) {
			int res = fscanf(file1, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			if (strcmp(lineHeader, "v") == 0) {
				v_count++;
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				vn_count++;
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				vt_count++;
			}
			else if (strcmp(lineHeader, "f") == 0) {
				face_count++;
			}
			else if (strcmp(lineHeader, "mtllib") == 0) {
				UseMaterialFile = true;
				int res = fscanf(file1, "%s", lineHeader);
				int name_l = strlen(lineHeader);
				char *path = new char[254];

				sprintf(&path[0], "%s%s", forlder_path->CharAt(), lineHeader);
				//Todo(Marc): Refactor those material
				mtl_file = new FileMtlRawDataV2();
				mtl_file->LoadFromFile(path);
			}
			else if (strcmp(lineHeader, "usemtl") == 0) {
				int res = fscanf(file1, "%s", lineHeader);
			}
			else if (strcmp(lineHeader, "s") == 0) {

			}

		}
	}
	fclose(file1);

	vertices_array = new v3[v_count];
	uvs_array = new v2[vt_count];
	normal_array = new v3[vn_count];
	if (UseMaterialFile == true) {
		faces_array = new unsigned int[face_count * 9];
	}
	else {
		faces_array = new unsigned int[face_count * 6];
	}

	int v_c_index = 0;
	int vn_c_index = 0;
	int vt_c_index = 0;
	int f_c_index = 0;


	MaterielRawData *current_material_data;
	FILE * file = fopen(file_path->CharAt(), "rb");
	if (file != nullptr) {
		char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
		while (1) {
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			if (strcmp(lineHeader, "v") == 0) {
				v3 *c_v_data = &vertices_array[v_c_index];
				int match_cpt = fscanf_s(file, " %f %f %f \n", &c_v_data->x, &c_v_data->y, &c_v_data->z);
				if (match_cpt != 3) {
					printf("Error reading vertices Num:|%i|\n", v_c_index);
				}
				printf("- Vertices  #:|%i|: %f %f %f\n", vn_c_index, c_v_data->x, c_v_data->y, c_v_data->z);
				v_c_index++;
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				v3 *c_vn_data = &normal_array[vn_c_index];
				int match_cpt = fscanf_s(file, " %f %f %f \n", &c_vn_data->x, &c_vn_data->y, &c_vn_data->z);
				if (match_cpt != 3) {
					printf("Error reading vertices normal #:|%i|:\n", vn_c_index);
				}
				printf("- Normal  #:|%i|: %f %f %f\n", vn_c_index, c_vn_data->x, c_vn_data->y, c_vn_data->z);
				vn_c_index++;
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				v2 *c_vt_data = &uvs_array[vt_c_index];
				int match_cpt = fscanf_s(file, "%f %f\n", &c_vt_data->x, &c_vt_data->y);
				if (match_cpt != 2) {
					printf("Error reading Tex coords Num:|%i|\n", vt_c_index);
				}
				vt_c_index++;
			}
			else if (strcmp(lineHeader, "f") == 0) {
				unsigned int *face_data = &faces_array[f_c_index];

				if (this->UseMaterialFile == true) {
					int match_cpt = fscanf(file, "%d//%d %d//%d %d//%d\n", &face_data[0], &face_data[1], &face_data[3],
						&face_data[4], &face_data[6], &face_data[7]);
					if (match_cpt != 6) {
						printf("Error reading face data\n");
					}
					if (current_material_data != nullptr) {
						face_data[2] = current_material_data->Id;
						face_data[5] = current_material_data->Id;
						face_data[8] = current_material_data->Id;
					}
					else {
						printf("Error reading mat index\n");
					}
					f_c_index = f_c_index + 9;
				}
				if (UseMaterialFile == false) {
					int match_cpt = fscanf(file, "%d//%d %d//%d %d//%d", &face_data[0], &face_data[1], &face_data[2],
						&face_data[3], &face_data[4], &face_data[5]);
					if (match_cpt != 6) {
						printf("Error reading face data\n");
					}
					f_c_index = f_c_index + 6;
				}

			}
			else if (strcmp(lineHeader, "usemtl") == 0) {
				int res = fscanf(file, "%s", lineHeader);
				char ref_name[128];
				sprintf(&ref_name[0], "%s\n", lineHeader);
				current_material_data = mtl_file->FindByNameRef(ref_name);
			}
			else if (strcmp(lineHeader, "s") == 0) {

			}

		}
	}
	fclose(file);
	printf("Loading | Model | Completed:\n");
}


