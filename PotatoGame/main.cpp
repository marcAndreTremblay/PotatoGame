#include "stdafx.h"
#include "PGEditorInstance.h"


class PGV3 {
public:
	float x;
	float y;
	float z;
	PGV3(float f1) {
		this->x = f1;
		this->y = f1;
		this->z = f1;
	}
	PGV3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	PGV3() {
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
	}
	~PGV3() {

	}
	PGV3& operator+=(const PGV3& rhs) // compound assignment (does not need to be a member,
	{                           // but often is, to modify the private members)
		/* addition of rhs to *this takes place here */
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		this->z = this->z + rhs.z;
		return *this; // return the result by reference
	}
};


#include "PGAssetManager.h"

int main(int argc, char **argv)
{
	PGLinked2List<PGV3*>* test =  new PGLinked2List<PGV3*>();
	test->Add(new PGV3(1.f));
	
	v3 v_tab[100];
	int v_c_index = 0;

	v3 vn_tab[100];
	int vn_c_index = 0;

	v2 vt_tab[100];
	int vt_c_index = 0;
	
	
	FILE * file = fopen("Asset/RawOBJ/test_cube.obj", "r");
	if (file != nullptr) {
		char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
		while (1) {
			int res = fscanf(file, "%s", lineHeader);
			//	printf("Read String1 |%s|\n", lineHeader);                                                   
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			if (strcmp(lineHeader, "v") == 0) {
				int match_cpt = fscanf_s(file, "%f %f %f\n", &v_tab[v_c_index].x, &v_tab[v_c_index].y, &v_tab[v_c_index].z);
				if (match_cpt != 3) {
					printf("Error reading vertices tangent Num:|%i|\n", v_c_index);
				}
				v_c_index++;
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				int match_cpt = fscanf_s(file, "%f %f %f\n", &vn_tab[vn_c_index].x, &vn_tab[vn_c_index].y, &vn_tab[vn_c_index].z);
				if (match_cpt != 3) {
					printf("Error reading vertices tangent Num:|%i|\n", vn_c_index);
				}
				vn_c_index++;
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				int match_cpt = fscanf_s(file, "%f %f\n", &vt_tab[vt_c_index].x, &vt_tab[vt_c_index].y);
				if (match_cpt != 2) {
					printf("Error reading Tex coords Num:|%i|\n", vt_c_index);
				}
				vt_c_index++;
			}
			else if (strcmp(lineHeader, "f") == 0) {
				unsigned int face_data[9] = {};
				int match_cpt = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",  &face_data[0], &face_data[1], &face_data[2],
															&face_data[3], &face_data[4], &face_data[5], 
															&face_data[6], &face_data[7], &face_data[8]);
				if (match_cpt != 9) {
					printf("Error reading face data\n");
				}
			}
			else if (strcmp(lineHeader, "usemtl") == 0) {
			
			}
			else if (strcmp(lineHeader, "s") == 0) {
			
			}

		}
	}
	while (v_c_index >= 1) {
		printf("Verticles : %f %f %f\n", v_tab[v_c_index].x, v_tab[v_c_index].y, v_tab[v_c_index].z);
		v_c_index--;
	}
	while (vn_c_index >= 1) {
		printf("Normal  : %f %f %f\n", vn_tab[vn_c_index].x, vn_tab[vn_c_index].y, vn_tab[vn_c_index].z);
		vn_c_index--;
	}
	while (vt_c_index >= 1) {
		printf("V tex : %f %f\n", vt_tab[vt_c_index].x, vt_tab[vt_c_index].y);
		vt_c_index--;
	}

	
	

//	PGRawObjFile* test_file = new PGRawObjFile("Test_File\n", "Asset/RawOBJ/test_cube.obj//");
//	test_file->Build();
/*
	v3 *tes2 = new v3(1.f);

	*tes2 += v3(1.f) += v3(2.f);

	PGV3 *test = new PGV3(1.f);
	*test += (PGV3(3.f, 1.f, 2.f));
	*/


	PGEditorInstance* main_instance = new PGEditorInstance();
		main_instance->Build();
		main_instance->Start();
	delete(main_instance);
	return 0;
}

