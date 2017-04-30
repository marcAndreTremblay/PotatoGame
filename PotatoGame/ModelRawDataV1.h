#if !defined(MODEL_RAW_DATA_V1_H)
#define MODEL_RAW_DATA_V1_H

#include "Core.h"
#include "String.h"
#include "PGShaderSources.h"
#include "FileMtlRawDataV2.h"
using namespace PG::Core;

class ModelRawDataV1 {
private:
	Str * file_path;
	Str * forlder_path;

	//Add Materiel file list
	

	int v_count;
	int vn_count;
	int vt_count;
	int face_count;
	//Data arrays
	v3* vertices_array;
	v2* uvs_array;
	v3* normal_array;
	unsigned int* faces_array;
public:
	FileMtlRawDataV2* mtl_file;
	bool UseMaterialFile;
	bool UseTextureMap;
	int GetFaceCount();
	unsigned int* GetFacesArrayPtr();
	v3* GetVertivesArrayPtr();
	v2* GetUVSArrayPtr();
	v3* GetNormalsArrayPtr();

	ModelRawDataV1();
	virtual ~ModelRawDataV1();
	void LoadFromFile(char *file_path);
};
#endif //MODEL_RAW_DATA_V1_H

